#include "variantfinder.h"


IVariantFinder::IVariantFinder(ISoftClippedRead *pRead)
    : reads({pRead})
{

}

void IVariantFinder::AddRead(ISoftClippedRead *pRead)
{
    if (pRead->GetType() == reads[0]->GetType()
        && pRead->GetClipPosition() == reads[0]->GetClipPosition())
    {
        reads.push_back(pRead);
    }
}
