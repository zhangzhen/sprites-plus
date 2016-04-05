#include "variantcaller.h"


IVariantCaller::IVariantCaller(ISoftClippedRead *pRead)
    : reads({pRead})
{

}

void IVariantCaller::AddRead(ISoftClippedRead *pRead)
{
    if (pRead->GetType() == reads[0]->GetType()
        && pRead->GetClippingPosition() == reads[0]->GetClippingPosition())
    {
        reads.push_back(pRead);
    }
}
