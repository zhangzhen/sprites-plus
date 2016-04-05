#include "DeletionCaller.h"

DeletionCaller::DeletionCaller(ISoftClippedRead *pRead,
                               ITargetRegionFinder *pRegionFinder,
                               ISequenceFetcher *pSeqFetcher,
                               ISequenceAligner *pSeqAligner)
    : IVariantCaller(pRead),
      pRegionFinder(pRegionFinder),
      pSeqFetcher(pSeqFetcher),
      pSeqAligner(pSeqAligner)
{
}

ChromosomeRegion *DeletionCaller::FindTargetRegion()
{
    return pRegionFinder->FindRegion();
}


IVariant *DeletionCaller::FindCall()
{
    return NULL;
//    ChromosomeRegion *pTargetReg = pRegionFinder->FindRegion(positions);
//    string targetSeq = pSeqFetcher->Fetch(*pTargetReg);
//    AlignmentResults alignmentResults = pSeqAligner->Align(targetSeq, reads[0]->GetSequence());
//    return reads[0]->FindCall(alignmentResults);
}
