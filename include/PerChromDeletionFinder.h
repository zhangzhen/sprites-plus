#ifndef PERCHROMDELETIONFINDER_H
#define PERCHROMDELETIONFINDER_H

#include "DeletionFinder.h"
#include "api/BamReader.h"

class PerChromDeletionFinder
{
public:
    PerChromDeletionFinder(ITargetRegionFinder *pRegionToLeftFinder,
                           ITargetRegionFinder *pRegionToRightFinder,
                           ISequenceFetcher *pSeqFetcher,
                           IRealignmentCaller *pPrefixCaller,
                           IRealignmentCaller *pSuffixCaller);
    void AddRead(ISoftClippedRead *pRead);
    void Clear();
    void FindTargetRegions(std::vector<TargetRegion *> &regions);
    void FindCalls(const CallParams& cParams, std::vector<IVariant *> &variants);
    std::vector<IVariant*> MergeCalls(const std::vector<IVariant *>& variants);
//    void DetermineMicroHom(std::vector<IVariant *> &variants);

private:
    std::map<int, DeletionFinder*> finderMap;
    std::set<int> conflictSet;
    ITargetRegionFinder *pRegionToLeftFinder;
    ITargetRegionFinder *pRegionToRightFinder;
    ISequenceFetcher *pSeqFetcher;
    IRealignmentCaller *pPrefixCaller;
    IRealignmentCaller *pSuffixCaller;
};

typedef std::vector<std::size_t> IndexCluster;

std::vector<IndexCluster> ClusterIntervalsByIndex(const std::vector<Interval> &intervals);

#endif // PERCHROMDELETIONFINDER_H
