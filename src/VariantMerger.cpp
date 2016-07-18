#include "VariantMerger.h"
#include <algorithm>


void VariantMerger::AddVariant(IVariant *pVariant)
{
    if (pVariant->GetType() == variants[0]->GetType() &&
            pVariant->GetReferenceId() == variants[0]->GetReferenceId())
    {
        variants.push_back(pVariant);
    }
}

IVariant *VariantMerger::merge()
{
    if (variants.size() == 1)
    {
        return variants[0];
    }

    IVariant *pFinalVar = *std::max_element(variants.begin(),
                                      variants.end(),
                                      [](IVariant *p1, IVariant *p2) { return p1->GetNumOfReads() < p2->GetNumOfReads(); });

    for (auto pVar: variants)
    {
        if (pVar != pFinalVar)
        {
            pFinalVar->AddOtherPosition(pVar->GetFromClipPosition());
        }
    }

    int n = 0;
    for (auto pVar: variants)
    {
        n += pVar->GetNumOfReads();
    }

    pFinalVar->SetNumOfReads(n);

    return pFinalVar;
}
