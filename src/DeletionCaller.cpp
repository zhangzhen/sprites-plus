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


IVariant *DeletionCaller::FindCall(const CallParams &cParams)
{
    TargetRegion *pTargetReg;
    if((pTargetReg = FindTargetRegion()))
    {
        std::string targetSeq = pSeqFetcher->Fetch(pTargetReg->GetChromosomeRegion());
        ScoreParam sParam(2, -3, -10000);
        AlignmentResult alignmentResult = pSeqAligner->Align(targetSeq, reads[0]->GetSequence(), sParam);
        if (alignmentResult.IsQualified(cParams.GetMinClip(), cParams.GetMaxErrorRate()))
        {
            return reads[0]->FindCall(pTargetReg->GetStartPosition(), alignmentResult, pTargetReg->IsHeterozygous());
        }
    }
    return NULL;
}
