#include "DeletionFinder.h"
#include "Deletion.h"

#include <algorithm>


DeletionFinder::DeletionFinder(ISoftClippedRead *pRead,
                               ITargetRegionFinder *pRegionFinder,
                               IRealignmentCaller *pRealnCaller)
    : IVariantFinder(pRead),
      pRegionFinder(pRegionFinder),
      pRealnCaller(pRealnCaller)
{
}

TargetRegion *DeletionFinder::FindTargetRegion()
{
    return pRegionFinder->FindRegion(GetClipPosition());
}


IVariant *DeletionFinder::FindVariant(const CallParams &cParams)
{
    TargetRegion *pTargetReg;
    if((pTargetReg = FindTargetRegion()))
    {

        ChromosomeRegion cRegion = pTargetReg->GetChromosomeRegion();

        CallResult *pCallRes;

        if((pCallRes = pRealnCaller->Call(reads[0], cRegion, cParams)))
        {
            return new Deletion(pCallRes->GetChromoRegion(), Interval(), Interval(), pTargetReg->IsHeterozygous(), GetClipPosition(), GetReadType(), reads.size());
        }

    }
    return NULL;
}


int NumOfLongestCommonPrefix(const std::string &v, const std::string &w)
{

    int n = std::min(v.length(), w.length());
    int i = 0;

    while (i < n && v[i] == w[i])
    {
        i++;
    }

    return i;
}

int NumOfLongestCommonSuffix(const std::string &v, const std::string &w)
{
    std::string v1;
    std::reverse_copy(v.begin(), v.end(), v1.begin());
    std::string w1;
    std::reverse_copy(w.begin(), w.end(), w1.begin());

    return NumOfLongestCommonPrefix(v, w);
}
