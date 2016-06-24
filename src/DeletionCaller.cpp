#include "DeletionCaller.h"

DeletionCaller::DeletionCaller(ISoftClippedRead *pRead,
//                               ITargetRegionFinder *pRegionFinder)
                               ITargetRegionFinder *pRegionFinder,
                               ISequenceFetcher *pSeqFetcher,
                               ISequenceAligner *pSeqAligner)
    : IVariantCaller(pRead),
//      pRegionFinder(pRegionFinder)
      pRegionFinder(pRegionFinder),
      pSeqFetcher(pSeqFetcher),
      pSeqAligner(pSeqAligner)
{
}

TargetRegion *DeletionCaller::FindTargetRegion()
{
    return pRegionFinder->FindRegion(reads[0]->GetClipPosition());
}


IVariant *DeletionCaller::FindCall()
{
//    return NULL;
    TargetRegion *pTargetReg = FindTargetRegion();
    std::string targetSeq = pSeqFetcher->Fetch(pTargetReg->GetChromosomeRegion());
    ScoreParam sParam(2, -3, -10000);
    AlignmentResult alignmentResult = pSeqAligner->Align(targetSeq, reads[0]->GetSequence(), sParam);
    return reads[0]->FindCall(pTargetReg->GetStartPosition(), alignmentResult);
}
