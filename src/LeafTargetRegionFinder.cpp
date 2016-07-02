#include "LeafTargetRegionFinder.h"
#include "statistics.h"
#include <algorithm>

using namespace std;

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

//    cout << gPos << endl;

    pPairsReader->Init(gPos);
    SpanningPair *pPair;
    while ((pPair = pPairsReader->NextPair()))
    {
        pairs.push_back(pPair);
    }

    if (pairs.size() == 0)
    {
        return NULL;
    }

    std::vector<int> insertSizes(pairs.size());
    transform(begin(pairs), end(pairs), begin(insertSizes), [](SpanningPair *p){ return p->GetInsertSize(); });

    if (gPos.GetPosition() == 61608090)
    {
        for (auto p : pairs)
        {
            cout << *p << endl;
        }
    }

    labels = pPartitioner->Partition(insertSizes);
    heterozygous = pQualifier->IsQualified(insertSizes, labels);

//    cout << heterozygous << endl;

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
