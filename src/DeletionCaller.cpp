#include "DeletionCaller.h"

DeletionCaller::DeletionCaller(ISoftClippedRead *pRead,
                               ITargetRegionFinder *pRegionFinder)
//                               ITargetRegionFinder *pRegionFinder,
//                               ISequenceFetcher *pSeqFetcher,
//                               ISequenceAligner *pSeqAligner)
    : IVariantCaller(pRead),
      pRegionFinder(pRegionFinder)
//      pRegionFinder(pRegionFinder),
//      pSeqFetcher(pSeqFetcher),
//      pSeqAligner(pSeqAligner)
{
}

TargetRegion *DeletionCaller::FindTargetRegion()
{
    return pRegionFinder->FindRegion(reads[0]->GetClipPosition());
}


IVariant *DeletionCaller::FindCall()
{
    return NULL;
//    ChromosomeRegion *pTargetReg = pRegionFinder->FindRegion(positions);
//    string targetSeq = pSeqFetcher->Fetch(*pTargetReg);
//    AlignmentResult alignmentResult = pSeqAligner->Align(targetSeq, reads[0]->GetSequence());
//    return reads[0]->FindCall(alignmentResult);
}
