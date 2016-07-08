#include "DeletionCaller.h"

#include "Deletion.h"

DeletionCaller::DeletionCaller(ISoftClippedRead *pRead,
//                               ITargetRegionFinder *pRegionFinder)
                               ITargetRegionFinder *pRegionFinder,
                               ISequenceFetcher *pSeqFetcher,
                               IReadRealigner *pReadRealigner)
    : IVariantCaller(pRead),
//      pRegionFinder(pRegionFinder)
      pRegionFinder(pRegionFinder),
      pSeqFetcher(pSeqFetcher),
      pReadRealigner(pReadRealigner)
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
        ChromoFragment cFragment = pSeqFetcher->Fetch(pTargetReg->GetChromosomeRegion());
        ScoreParam sParam(2, -3, -10000);
        AlignmentResult alnResult = pReadRealigner->Realign(cFragment, reads[0], sParam);
        if (GetClipPosition().GetPosition() == 42056489)
        {
            std::cout << cFragment.GetSequence() << std::endl;
            std::cout << reads[0]->GetSequence() << std::endl;
        }
        if (reads[0]->IsQualified(alnResult, cParams))
        {
            ChromosomeRegionWithCi cRegionWithCi = reads[0]->ToRegionWithCi(alnResult);
            return new Deletion(cRegionWithCi, pTargetReg->IsHeterozygous(), GetClipPosition(), GetReadType(), reads.size());
        }
    }
    return NULL;
}
