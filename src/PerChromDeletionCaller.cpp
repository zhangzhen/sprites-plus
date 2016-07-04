#include "PerChromDeletionCaller.h"
#include <iterator>

using namespace std;

PerChromDeletionCaller::PerChromDeletionCaller(ITargetRegionFinder *pRegionToLeftFinder,
//                                                 ITargetRegionFinder *pRegionToRightFinder)
                                               ITargetRegionFinder *pRegionToRightFinder,
                                               ISequenceFetcher *pSeqFetcher,
                                               ISequenceAligner *pPrefixAligner,
                                               ISequenceAligner *pSuffixAligner)
    : pRegionToLeftFinder(pRegionToLeftFinder),
//      pRegionToRightFinder(pRegionToRightFinder)
      pRegionToRightFinder(pRegionToRightFinder),
      pSeqFetcher(pSeqFetcher),
      pPrefixAligner(pPrefixAligner),
      pSuffixAligner(pSuffixAligner)
{
}

void PerChromDeletionCaller::AddRead(ISoftClippedRead *pRead)
{
    int pos = pRead->GetClipPosition().GetPosition();
    if (callerMap.count(pos))
    {
        if (pRead->GetType() == callerMap[pos]->GetReadType())
        {
            callerMap[pos]->AddRead(pRead);
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
            callerMap[pos] = new DeletionCaller(pRead, pRegionToRightFinder, pSeqFetcher, pPrefixAligner);
//            callerMap[pos] = new DeletionCaller(pRead, pRegionToRightFinder);
        }
        else if (pRead->GetType() == "5R")
        {
            callerMap[pos] = new DeletionCaller(pRead, pRegionToLeftFinder, pSeqFetcher, pSuffixAligner);
//            callerMap[pos] = new DeletionCaller(pRead, pRegionToLeftFinder);
        }
    }
}

void PerChromDeletionCaller::Clear()
{
    callerMap.clear();
    conflictSet.clear();
}

void PerChromDeletionCaller::FindTargetRegions(std::vector<TargetRegion *> &regions)
{
    TargetRegion *pReg;
//    copy(begin(conflictSet), end(conflictSet), ostream_iterator<int>(cout, " "));
//    cout << callerMap.size() << endl;

    for (auto &elt : callerMap)
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

void PerChromDeletionCaller::FindCalls(const CallParams &cParams, std::vector<IVariant *> &variants)
{
    IVariant *pVariant;
    for (auto &elt : callerMap)
    {
        if (conflictSet.count(elt.first))
        {
            continue;
        }
        if((pVariant = elt.second->FindCall(cParams)))
        {
            variants.push_back(pVariant);
        }
    }

}

std::vector<IVariant *> PerChromDeletionCaller::MergeCalls(const std::vector<IVariant *> &variants)
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
