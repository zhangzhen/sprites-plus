#include "PerChromDeletionCaller.h"
#include <iterator>

using namespace std;

PerChromDeletionCaller::PerChromDeletionCaller(ITargetRegionFinder *pRegionToLeftFinder,
                                                 ITargetRegionFinder *pRegionToRightFinder)
//                                                   ITargetRegionFinder *pRegionToRightFinder,
//                                                   ISequenceFetcher *pSeqFetcher,
//                                                   ISequenceAligner *pSeqAligner)
    : pRegionToLeftFinder(pRegionToLeftFinder),
      pRegionToRightFinder(pRegionToRightFinder)
//      pRegionToRightFinder(pRegionToRightFinder),
//      pSeqFetcher(pSeqFetcher),
//      pSeqAligner(pSeqAligner)
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
//            callerMap[pos] = new DeletionCaller(pRead, pRegionToRightFinder, pSeqFetcher, pSeqAligner);
            callerMap[pos] = new DeletionCaller(pRead, pRegionToRightFinder);
        }
        else if (pRead->GetType() == "5R")
        {
//            callerMap[pos] = new DeletionCaller(pRead, pRegionToLeftFinder, pSeqFetcher, pSeqAligner);
            callerMap[pos] = new DeletionCaller(pRead, pRegionToLeftFinder);
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

bool PerChromDeletionCaller::Call(std::vector<IVariant *> &variants)
{
    return false;
}
