#include "PerChromDeletionFinder.h"
#include "EndPoint.h"
#include "VariantMerger.h"

#include <iterator>
#include <algorithm>
#include <queue>
#include <set>


using namespace std;

PerChromDeletionFinder::PerChromDeletionFinder(ITargetRegionFinder *pRegionToLeftFinder,
//                                                 ITargetRegionFinder *pRegionToRightFinder)
                                               ITargetRegionFinder *pRegionToRightFinder,
                                               ISequenceFetcher *pSeqFetcher,
                                               IRealignmentCaller *pPrefixCaller,
                                               IRealignmentCaller *pSuffixCaller)
    : pRegionToLeftFinder(pRegionToLeftFinder),
//      pRegionToRightFinder(pRegionToRightFinder)
      pRegionToRightFinder(pRegionToRightFinder),
      pSeqFetcher(pSeqFetcher),
      pPrefixCaller(pPrefixCaller),
      pSuffixCaller(pSuffixCaller)
{
}

void PerChromDeletionFinder::AddRead(ISoftClippedRead *pRead)
{
    int pos = pRead->GetClipPosition().GetPosition();
    if (finderMap.count(pos))
    {
        if (pRead->GetType() == finderMap[pos]->GetReadType())
        {
            finderMap[pos]->AddRead(pRead);
        }
        else
        {
            conflictSet.insert(pos);
        }
    }
    else
    {
        if (pRead->GetType() == "5F")
        {
            finderMap[pos] = new DeletionFinder(pRead, pRegionToRightFinder, pPrefixCaller);
//            callerMap[pos] = new DeletionCaller(pRead, pRegionToRightFinder);
        }
        else if (pRead->GetType() == "5R")
        {
            finderMap[pos] = new DeletionFinder(pRead, pRegionToLeftFinder, pSuffixCaller);
//            callerMap[pos] = new DeletionCaller(pRead, pRegionToLeftFinder);
        }
    }
}

void PerChromDeletionFinder::Clear()
{
    finderMap.clear();
    conflictSet.clear();
}

void PerChromDeletionFinder::FindTargetRegions(std::vector<TargetRegion *> &regions)
{
    TargetRegion *pReg;
//    copy(begin(conflictSet), end(conflictSet), ostream_iterator<int>(cout, " "));
//    cout << callerMap.size() << endl;

    for (auto &elt : finderMap)
    {
        if (conflictSet.count(elt.first))
        {
            continue;
        }
        if((pReg = elt.second->FindTargetRegion()))
        {
            regions.push_back(pReg);
        }
    }
}

void PerChromDeletionFinder::FindCalls(const CallParams &cParams, std::vector<IVariant *> &variants)
{
    IVariant *pVariant;
    for (auto &elt : finderMap)
    {
        if (conflictSet.count(elt.first))
        {
            continue;
        }
        if((pVariant = elt.second->FindVariant(cParams)))
        {
            variants.push_back(pVariant);
        }
    }

}

std::vector<IVariant *> PerChromDeletionFinder::MergeCalls(const std::vector<IVariant *> &variants)
{
    std::vector<Interval> intervals;
    intervals.reserve(variants.size());
    for (auto pVar: variants)
    {
        intervals.push_back(pVar->GetChromoRegion().GetInterval());
    }

    std::vector<IndexCluster> iClusters = ClusterIntervalsByIndex(intervals);

//    std::cout << iClusters.size() << std::endl;

    vector<IVariant*> result;

    for (size_t i = 0; i < iClusters.size(); ++i)
    {
        VariantMerger vMerger(variants[iClusters[i][0]]);
        for (size_t j = 1; j < iClusters[i].size(); ++j)
        {
            vMerger.AddVariant(variants[iClusters[i][j]]);
        }
        result.push_back(vMerger.merge());
    }

//    if (variants.empty()) return result;

//    size_t current = 0;
//    result.push_back(variants[current]);
//    int s = variants[current]->GetNumOfReads();

//    for (size_t i = 1; i < variants.size(); ++i)
//    {
//        if (variants[current]->QuasiEquals(*variants[i]))
//        {
//            s += variants[i]->GetNumOfReads();
//        }
//        else
//        {
//            current = i;
//            result.push_back(variants[current]);
//            s = variants[current]->GetNumOfReads();
//        }
//    }

    return result;
}


std::vector<IndexCluster> ClusterIntervalsByIndex(const std::vector<Interval> &intervals)
{
    vector<IndexCluster> result;

    vector<EndPoint> points;
    points.reserve(intervals.size()*2);

    for (size_t i = 0; i < intervals.size(); ++i)
    {
        points.push_back(EndPoint(intervals[i].GetStart(), i, true));
        points.push_back(EndPoint(intervals[i].GetEnd(), i, false));
    }

    sort(points.begin(), points.end());

    set<size_t> usedIndice;
    queue<size_t> buffer;

    for (auto p: points)
    {
        if (p.IsLeft()) buffer.push(p.GetOwnerIndex());
        else
        {
            if (usedIndice.count(p.GetOwnerIndex())) continue;
            IndexCluster clu;
            while (!buffer.empty())
            {
                clu.push_back(buffer.front());
                usedIndice.insert(buffer.front());
                buffer.pop();
            }
            if (!clu.empty()) result.push_back(clu);
        }
    }
    IndexCluster clu;
    while (!buffer.empty()) {
        clu.push_back(buffer.front());
        usedIndice.insert(buffer.front());
        buffer.pop();
    }
    if (!clu.empty()) result.push_back(clu);

    return result;
}
