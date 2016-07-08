#ifndef DELETIONCALLER_H
#define DELETIONCALLER_H

#include "variantcaller.h"
#include "targetregionfinder.h"
#include "sequencefetcher.h"
#include "readrealigner.h"

class DeletionCaller : public IVariantCaller
{
public:
    DeletionCaller(ISoftClippedRead *pRead,
                   ITargetRegionFinder *pRegionFinder,
                   ISequenceFetcher *pSeqFetcher,
                   IReadRealigner *pReadRealigner);
    TargetRegion *FindTargetRegion();
    IVariant *FindCall(const CallParams& cParams);

private:
    ITargetRegionFinder *pRegionFinder;
    ISequenceFetcher *pSeqFetcher;
    IReadRealigner *pReadRealigner;
};

#endif // DELETIONCALLER_H
