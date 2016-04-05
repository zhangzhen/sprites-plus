#ifndef PERCHROMDELELETIONCALLER_H
#define PERCHROMDELELETIONCALLER_H

#include "DeletionCaller.h"
#include "api/BamReader.h"

class PerChromDeleletionCaller
{
public:
    PerChromDeleletionCaller(ITargetRegionFinder *pRegionToLeftFinder,
                             ITargetRegionFinder *pRegionToRightFinder,
                             ISequenceFetcher *pSeqFetcher,
                             ISequenceAligner *pSeqAligner);
    void AddRead(ISoftClippedRead *pRead);
    void Clear();
    void FindTargetRegions(std::vector<ChromosomeRegion*>& regions);
    bool Call(std::vector<IVariant*> &variants);

private:
    std::map<int, IVariantCaller*> callerMap;
    std::set<int> conflictSet;
    ITargetRegionFinder *pRegionToLeftFinder;
    ITargetRegionFinder *pRegionToRightFinder;
    ISequenceFetcher *pSeqFetcher;
    ISequenceAligner pSeqAligner;
};

#endif // PERCHROMDELELETIONCALLER_H
