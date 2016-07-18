#ifndef VARIANTFINDER_H
#define VARIANTFINDER_H

#include "variant.h"
#include "softclippedread.h"
#include "GenomePosition.h"
#include "CallParams.h"

#include <vector>

class IVariantFinder
{
public:
    IVariantFinder(ISoftClippedRead *pRead);
    void AddRead(ISoftClippedRead *pRead);
    GenomePosition GetClipPosition() { return reads[0]->GetClipPosition(); }
    virtual ~IVariantFinder() {}
    virtual IVariant* FindVariant(const CallParams& cParams) = 0;
    std::string GetReadType() { return reads[0]->GetType(); }

protected:
    std::vector<ISoftClippedRead *> reads;
};

#endif // VARIANTFINDER_H
