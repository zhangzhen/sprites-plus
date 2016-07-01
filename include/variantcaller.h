#ifndef VARIANTCALLER_H
#define VARIANTCALLER_H

#include "softclippedread.h"
#include "GenomePosition.h"
#include "CallParams.h"

#include <vector>

class IVariantCaller
{
public:
    IVariantCaller(ISoftClippedRead *pRead);
    void AddRead(ISoftClippedRead *pRead);
    GenomePosition GetClipPosition() { return reads[0]->GetClipPosition(); }
    virtual ~IVariantCaller() {}
    virtual IVariant* FindCall(const CallParams& cParams) = 0;
    std::string GetReadType() { return reads[0]->GetType(); }

protected:
    std::vector<ISoftClippedRead *> reads;
};

#endif // VARIANTCALLER_H
