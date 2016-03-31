#include "DeletionCaller.h"

DeletionCaller::DeletionCaller(ISoftClippedRead *pRead,
                               ITargetRegionFinder *pRegionFinder,
                               ISequenceFetcher pSeqFetcher,
                               ISequenceAligner pSeqAligner)
    : IVariantCaller(pRead),
      pRegionFinder(pRegionFinder),
      pSeqFetcher(pSeqFetcher),
      pSeqAligner(pSeqAligner)
{
}


IVariant *DeletionCaller::FindCall()
{
    ChromosomeRegion chromoReg = pRegionFinder->FindRegion(positions);
    string targetSeq = pSeqFetcher->Fetch(chromoReg);
    AlignmentResults alignmentResults = pSeqAligner->Align(targetSeq, reads[0]->GetSequence());
    return reads[0]->FindCall(alignmentResults);
}
