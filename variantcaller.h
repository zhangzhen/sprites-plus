#ifndef VARIANTCALLER_H
#define VARIANTCALLER_H

#include "softclippedread.h"
#include "GenomePosition.h"
#include "targetregionfinder.h"
#include <vector>

class IVariantCaller
{
public:
    IVariantCaller(ISoftClippedRead *pRead);
    void AddRead(ISoftClippedRead *pRead);
    GenomePosition GetClippingPosition() { return reads[0]->GetClippingPosition(); }
    virtual ~IVariantCaller() {}
    virtual IVariant* FindCall() = 0;

private:
    std::vector<ISoftClippedRead *> reads;
};

#endif // VARIANTCALLER_H
