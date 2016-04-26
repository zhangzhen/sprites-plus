#include "BamToolsRGToLibMapReader.h"
#include "BamToolsLibInsertSizeEstimator.h"
#include "BamToolsSCReadsReader.h"
#include "PerChromDeletionCaller.h"
#include "MaxDistDiffBiPartitioner.h"
#include "AnovaBiPartitionQualifier.h"
#include "MedianPositionPicker.h"
#include "TargetRegionToLeftFinder.h"
#include "TargetRegionToRightFinder.h"
#include "BamToolsPairsToLeftReader.h"
#include "BamToolsPairsToRightReader.h"
#include "globals.h"
#include "error.h"

using namespace std;

void MakeLibraries(IReadGroupToLibraryMapReader *pMapReader, std::map<std::string, Library*> &libraries)
{
    std::map<std::string, std::string> readGroupToLibMap;
    if(pMapReader->GetMap(readGroupToLibMap))
    {
        for (auto &elt : readGroupToLibMap)
        {
            if (libraries.count(elt.second))
            {
                libraries[elt.second]->AddReadGroup(elt.first);
            }
            else
            {
                libraries[elt.second] = new Library(elt.second, elt.first);
            }
        }
        return;
    }

    libraries[NORGTAGLIBNAME] = new Library(NORGTAGLIBNAME, NORGTAGREADGROUPNAME);
}

void EstimateInsertSizeForLibrarys(ILibraryInsertSizeEstimator *pEstimator, std::map<std::string, Library*> &libraries)
{
    for (auto &p : libraries)
    {
        pEstimator->estimate(p.second);
    }
}

//void FindVariantCalls(PerChromDeletionCaller &caller, IVariantsWriter *pVarsWriter)
//{
//    std::vector<IVariant*> variants;
//    caller.Call(variants);
//    caller.Clear();
//    if (!variants.empty()) pVarsWriter->write(variants);
//}

void FindTargetRegions(PerChromDeletionCaller &caller)
{
    std::vector<TargetRegion *> regions;
    caller.FindTargetRegions(regions);
    for (auto &pRegion : regions)
    {
        cout << *pRegion << endl;
    }
    caller.Clear();
}

int main(int argc, char *argv[])
{
    BamTools::BamReader *pBamReader = new BamTools::BamReader();
    if (!pBamReader->Open("/home/zhangz/data/HET.10x.0.05/aln.11.sort.bam"))
    {
        error("Could not open the input BAM file.");
    }
    if (!pBamReader->LocateIndex())
    {
        error("Could not locate the index file");
    }

    IReadGroupToLibraryMapReader *pMapReader = new BamToolsRGToLibMapReader(pBamReader);
    std::map<std::string, Library*> libraries;
    MakeLibraries(pMapReader, libraries);
    ILibraryInsertSizeEstimator *pEstimator = new BamToolsLibInsertSizeEstimator(pBamReader);
    EstimateInsertSizeForLibrarys(pEstimator, libraries);

    ISoftClippedReadsReader *pReadsReader = new BamToolsSCReadsReader(pBamReader, 5, 20);

    int prevId = -1;
    int currentId;

    ISpanningPairsReader *pPairsToLeftReader;
    ISpanningPairsReader *pPairsToRightReader;

    if (libraries.size() == 1)
    {
        pPairsToLeftReader = new BamToolsPairsToLeftReader(libraries.begin()->second, pBamReader);
        pPairsToRightReader = new BamToolsPairsToRightReader(libraries.begin()->second, pBamReader);
    }
    IBiPartitioner* pPartitioner = new MaxDistDiffBiPartitioner();
    IBiPartitionQualifier* pQualifier = new AnovaBiPartitionQualifier(0.00001);
    IPositionPicker* pPosPicker = new MedianPositionPicker();
    ITargetRegionFinder *pRegionToLeftFinder = new TargetRegionToLeftFinder(pPairsToLeftReader,
                                                                            pPartitioner,
                                                                            pQualifier,
                                                                            pPosPicker);
    ITargetRegionFinder *pRegionToRightFinder = new TargetRegionToRightFinder(pPairsToRightReader,
                                                                            pPartitioner,
                                                                            pQualifier,
                                                                            pPosPicker);

    ISoftClippedRead *pRead;
    PerChromDeletionCaller caller(pRegionToLeftFinder, pRegionToRightFinder);
    while ((pRead = pReadsReader->NextRead()))
    {
        currentId = pRead->GetReferenceId();
        if (prevId != -1 && prevId != currentId)
        {
            FindTargetRegions(caller);
//            FindVariantCalls(caller, pVarsWriter);
        }
        caller.AddRead(pRead);
        prevId = currentId;
    }
    FindTargetRegions(caller);
//    FindVariantCalls(caller,pVarsWriter);

    return 0;
}
