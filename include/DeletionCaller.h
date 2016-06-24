#ifndef DELETIONCALLER_H
#define DELETIONCALLER_H

#include "variantcaller.h"
#include "targetregionfinder.h"
#include "sequencefetcher.h"
#include "sequencealigner.h"

class DeletionCaller : public IVariantCaller
{
public:
    DeletionCaller(ISoftClippedRead *pRead,
//                   ITargetRegionFinder *pRegionFinder);
                   ITargetRegionFinder *pRegionFinder,
                   ISequenceFetcher *pSeqFetcher,
                   ISequenceAligner *pSeqAligner);
    TargetRegion *FindTargetRegion();
    IVariant *FindCall();

private:
    ITargetRegionFinder *pRegionFinder;
    ISequenceFetcher *pSeqFetcher;
    ISequenceAligner *pSeqAligner;
};

#endif // DELETIONCALLER_H
