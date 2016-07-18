#ifndef DELETIONFINDER_H
#define DELETIONFINDER_H

#include "variantfinder.h"
#include "targetregionfinder.h"
#include "sequencefetcher.h"
#include "realignmentcaller.h"

class DeletionFinder : public IVariantFinder
{
public:
    DeletionFinder(ISoftClippedRead *pRead,
                   ITargetRegionFinder *pRegionFinder,
                   IRealignmentCaller *pRealnCaller);
    TargetRegion *FindTargetRegion();
    IVariant *FindVariant(const CallParams& cParams);

private:
    ITargetRegionFinder *pRegionFinder;
    IRealignmentCaller *pRealnCaller;
};

#endif // DELETIONFINDER_H
