#include "variantcaller.h"


IVariantCaller::IVariantCaller(ISoftClippedRead *pRead)
    : reads({pRead})
{

}

void IVariantCaller::AddRead(ISoftClippedRead *pRead)
{
    if (pRead->GetType() == reads[0]->GetType()
        && pRead->GetClipPosition() == reads[0]->GetClipPosition())
    {
        reads.push_back(pRead);
    }
}
