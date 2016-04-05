#include "BamToolsRGToLIbMapReader.h"
#include "BamToolsLibInsertSizeEstimator.h"
#include "BamToolsSCReadsReader.h"
#include "PerChromDeleletionCaller.h"
#include "MaxDistDiffBiPartitioner.h"
#include "AnovaBiPartitionQualifier.h"
#include "MedianPositionPicker.h"
#include "TargetRegionToLeftFinder.h"
#include "TargetRegionToRightFinder.h"
#include "BamToolsPairsToLeftReader.h"
#include "BamToolsPairsToRightReader.h"
#include "globals.h"

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

    libaries[NORGTAGLIBNAME] = new Library(NORGTAGLIBNAME, NORGTAGREADGROUPNAME);
}

void EstimateInsertSizeForLibrarys(ILibraryInsertSizeEstimator *pEstimator, std::map<std::string, Library*> &libraries)
{
    for (auto &p : libraries)
    {
        pEstimator->estimate(p.second);
    }
}

void FindVariantCalls(PerChromDeleletionCaller &caller, IVariantsWriter *pVarsWriter)
{
    std::vector<IVariant*> variants;
    caller.call(variants);
    caller.Clear();
    if (!variants.empty()) pVarsWriter->write(variants);
}


int main(int argc, char *argv[])
{
    BamTools::BamReader *pBamReader = new BamTools::BamReader();
    pBamReader->Open("filename");

    IReadGroupToLibraryMapReader *pMapReader = new BamToolsRGToLIbMapReader(pBamReader);
    std::map<std::string, Library*> libraries;
    MakeLibraries(pMapReader, libraries);
    ILibraryInsertSizeEstimator *pEstimator = new BamToolsLibInsertSizeEstimator(pBamReader);
    EstimateInsertSizeForLibrarys(pEstimator, libraries);

    ISoftClippedReadsReader *pReadsReader = new BamToolsSCReadsReader(pBamReader);

    int prevId = -1;
    int currentId;

    ISpanningPairsReader *pPairsToLeftReader = new BamToolsPairsToLeftReader(libraries[NORGTAGLIBNAME], pBamReader);
    ISpanningPairsReader *pPairsToRightReader = new BamToolsPairsToRightReader(libraries[NORGTAGLIBNAME], pBamReader);
    IBiPartitioner* pPartitioner = new MaxDistDiffBiPartitioner();
    IBiPartitionQualifier* pQualifier = new AnovaBiPartitionQualifier(0.000001);
    IPositionPicker* pPosPicker = new MedianPositionPicker();
    ITargetRegionFinder *pRegionToLeftFinder = new TargetRegionToLeftFinder(pPairsToRightReader,
                                                                            pPartitioner,
                                                                            pQualifier,
                                                                            pPosPicker);
    ITargetRegionFinder *pRegionToRightFinder = new TargetRegionToRightFinder(pPairsToLeftReader,
                                                                            pPartitioner,
                                                                            pQualifier,
                                                                            pPosPicker);

    ISoftClippedRead *pRead;
    PerChromDeleletionCaller caller(pRegionToLeftFinder, pRegionToRightFinder);
    while (pRead = pReadsReader->NextRead())
    {
        currentId = pRead->GetReferenceId();
        if (prevId != currentId)
        {
            FindVariantCalls(caller, pVarsWriter);
        }
        caller.AddRead(pRead);
        prevId = currentId;
    }
    FindVariantCalls(caller,pVarsWriter);

    return 0;
}
