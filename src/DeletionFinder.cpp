#include "DeletionFinder.h"
#include "Deletion.h"

#include <algorithm>


DeletionFinder::DeletionFinder(ISoftClippedRead *pRead,
                               ITargetRegionFinder *pRegionFinder,
                               IRealignmentCaller *pRealnCaller)
    : IVariantFinder(pRead),
      pRegionFinder(pRegionFinder),
      pRealnCaller(pRealnCaller)
{
}

TargetRegion *DeletionFinder::FindTargetRegion()
{
    return pRegionFinder->FindRegion(GetClipPosition());
}


IVariant *DeletionFinder::FindVariant(const CallParams &cParams)
{
    TargetRegion *pTargetReg;
    if((pTargetReg = FindTargetRegion()))
    {

        ChromosomeRegion cRegion = pTargetReg->GetChromosomeRegion();

        CallResult *pCallRes;

        if((pCallRes = pRealnCaller->Call(reads[0], cRegion, cParams)))
        {
//            if (GetClipPosition().GetPosition() == 10111162)
//            {
//                std::cout << *pCallRes << std::endl;
//            }
            return new Deletion(pCallRes->GetChromoRegion(), Interval(), Interval(), pTargetReg->IsHeterozygous(), GetClipPosition(), GetReadType(), reads.size());
        }

    }
    return NULL;
}
