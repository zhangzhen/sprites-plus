#include "DeletionCaller.h"

#include "Deletion.h"

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
    return pRegionFinder->FindRegion(GetClipPosition());
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
            ChromosomeRegionWithCi cRegionWithCi = reads[0]->ToRegionWithCi(pTargetReg->GetStartPosition(), alignmentResult);
            return new Deletion(cRegionWithCi, pTargetReg->IsHeterozygous(), GetClipPosition(), GetReadType(), reads.size());
        }
    }
    return NULL;
}
