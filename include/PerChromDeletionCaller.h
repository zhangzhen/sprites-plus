#ifndef PERCHROMDELETIONCALLER_H
#define PERCHROMDELETIONCALLER_H

#include "DeletionCaller.h"
#include "api/BamReader.h"

class PerChromDeletionCaller
{
public:
    PerChromDeletionCaller(ITargetRegionFinder *pRegionToLeftFinder,
                             ITargetRegionFinder *pRegionToRightFinder);
//                             ITargetRegionFinder *pRegionToRightFinder,
//                             ISequenceFetcher *pSeqFetcher,
//                             ISequenceAligner *pSeqAligner);
    void AddRead(ISoftClippedRead *pRead);
    void Clear();
    void FindTargetRegions(std::vector<TargetRegion *> &regions);
    bool Call(std::vector<IVariant*> &variants);

private:
    std::map<int, DeletionCaller*> callerMap;
    std::set<int> conflictSet;
    ITargetRegionFinder *pRegionToLeftFinder;
    ITargetRegionFinder *pRegionToRightFinder;
//    ISequenceFetcher *pSeqFetcher;
//    ISequenceAligner pSeqAligner;
};

#endif // PERCHROMDELETIONCALLER_H