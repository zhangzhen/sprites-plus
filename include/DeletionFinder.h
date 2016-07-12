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
                   ISequenceFetcher *pSeqFetcher,
                   IRealignmentCaller *pRealnCaller);
    TargetRegion *FindTargetRegion();
    IVariant *FindVariant(const CallParams& cParams);

private:
    ITargetRegionFinder *pRegionFinder;
    ISequenceFetcher *pSeqFetcher;
    IRealignmentCaller *pRealnCaller;
};

int NumOfLongestCommonPrefix(const std::string& v, const std::string& w);

int NumOfLongestCommonSuffix(const std::string& v, const std::string& w);

#endif // DELETIONFINDER_H
