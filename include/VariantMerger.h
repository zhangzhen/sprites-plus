#ifndef VARIANTMERGER
#define VARIANTMERGER

#include "variant.h"

#include <vector>


class VariantMerger
{
public:
    VariantMerger(IVariant *pVariant)
        : variants({pVariant})
    {}

    void AddVariant(IVariant *pVariant);

    IVariant *merge();

private:
    std::vector<IVariant *> variants;
};

#endif // VARIANTMERGER

