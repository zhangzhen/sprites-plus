#include "LeafTargetRegionFinder.h"
#include "statistics.h"
#include <algorithm>

LeafTargetRegionFinder::LeafTargetRegionFinder(ISpanningPairsReader *pPairsReader,
                                               IBiPartitioner *pPartitioner,
                                               IBiPartitionQualifier *pQualifier,
                                               IPositionPicker *pPosPicker)
    : pPairsReader(pPairsReader),
      pPartitioner(pPartitioner),
      pQualifier(pQualifier),
      pPosPicker(pPosPicker),
      heterozygous(false)
{
}

TargetRegion *LeafTargetRegionFinder::FindRegion(const GenomePosition &gPos)
{
    Clear();

    pPairsReader->Init(gPos);
    SpanningPair *pPair;
    while (pPair = pPairsReader->NextPair())
    {
        pairs.push_back(pPair);
    }

    std::vector<int> insertSizes(pairs.size());
    transform(begin(pairs), end(pairs), begin(insertSizes), [](SpanningPair *p){ return p->GetInsertSize(); });

    labels = pPartitioner->Partition(insertSizes);
    heterozygous = pQualifier->IsQualified(insertSizes, labels);

    std::vector<int> qualifiedInsertSizes;
    if (heterozygous)
    {
        for (size_t i = 0; i < labels.size(); i++)
        {
            if (labels[i] == 1) qualifiedInsertSizes.push_back(insertSizes[i]);
        }
    }
    else
    {
        qualifiedInsertSizes = insertSizes;
    }
    if (IsInsertSizeAnormalous(qualifiedInsertSizes, pPairsReader->GetMeanInsertSize(), 100))
    {
        return GetFinalRegion(gPos);
    }
    return NULL;
}
