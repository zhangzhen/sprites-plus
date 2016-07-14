#include "PerChromDeletionFinder.h"
#include <iterator>

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
    vector<IVariant*> result;

    if (variants.empty()) return result;

    size_t current = 0;
    result.push_back(variants[current]);
    int s = variants[current]->GetNumOfReads();

    for (size_t i = 1; i < variants.size(); ++i)
    {
        if (variants[current]->QuasiEquals(*variants[i]))
        {
            s += variants[i]->GetNumOfReads();
        }
        else
        {
            current = i;
            result.push_back(variants[current]);
            s = variants[current]->GetNumOfReads();
        }
    }

    return result;
}
