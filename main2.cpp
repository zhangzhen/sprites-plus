#include "BamToolsRGToLIbMapReader.h"
#include "BamToolsLibInsertSizeEstimator.h"
#include "BamToolsSCReadsReader.h"
#include "PerChromDeleletionCaller.h"

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

    ISoftClippedRead *pRead;
    PerChromDeleletionCaller caller;
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
