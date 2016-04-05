#include "PerChromDeleletionCaller.h"

PerChromDeleletionCaller::PerChromDeleletionCaller(ITargetRegionFinder *pRegionToLeftFinder,
                                                   ITargetRegionFinder *pRegionToRightFinder,
                                                   ISequenceFetcher *pSeqFetcher,
                                                   ISequenceAligner *pSeqAligner)
    : pRegionToLeftFinder(pRegionToLeftFinder),
      pRegionToRightFinder(pRegionToRightFinder),
      pSeqFetcher(pSeqFetcher),
      pSeqAligner(pSeqAligner)
{
}

void PerChromDeleletionCaller::AddRead(ISoftClippedRead *pRead)
{
    int pos = pRead->GetClippingPosition().GetPosition();
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
            callerMap[pos] = new DeletionCaller(pRead, pRegionToRightFinder, pSeqFetcher, pSeqAligner);
        }
        else if (pRead->GetType() == "5R")
        {
            callerMap[pos] = new DeletionCaller(pRead, pRegionToLeftFinder, pSeqFetcher, pSeqAligner);
        }
    }
}

void PerChromDeleletionCaller::Clear()
{
    callerMap.clear();
    conflictSet.clear();
}

void PerChromDeleletionCaller::FindTargetRegions(std::vector<ChromosomeRegion *> &regions)
{

}

bool PerChromDeleletionCaller::Call(std::vector<IVariant *> &variants)
{
    return false;
}
