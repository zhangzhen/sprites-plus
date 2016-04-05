#ifndef DELETIONCALLER_H
#define DELETIONCALLER_H

#include "variantcaller.h"
#include "sequencefetcher.h"
#include "sequencealigner.h"

class DeletionCaller : public IVariantCaller
{
public:
    DeletionCaller(ISoftClippedRead *pRead,
                   ITargetRegionFinder *pRegionFinder,
                   ISequenceFetcher *pSeqFetcher,
                   ISequenceAligner *pSeqAligner);
    ChromosomeRegion* FindTargetRegion();
    IVariant *FindCall();

private:
    ITargetRegionFinder *pRegionFinder;
    ISequenceFetcher *pSeqFetcher;
    ISequenceAligner *pSeqAligner;
};

#endif // DELETIONCALLER_H
