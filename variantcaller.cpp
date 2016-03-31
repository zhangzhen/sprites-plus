#include "variantcaller.h"


IVariantCaller::IVariantCaller(ISoftClippedRead *pRead)
    : pReads({pRead})
{

}

void IVariantCaller::AddRead(ISoftClippedRead *pRead)
{
    pReads.push_back(pRead);
}
