#include "TargetRegionToLeftFinder.h"
#include <algorithm>

TargetRegionToLeftFinder::TargetRegionToLeftFinder(ISpanningPairsReader* pPairsReader,
                                                   IBiPartitioner* pPartitioner,
                                                   IBiPartitionQualifier* pQualifier,
                                                   IPositionPicker* pPosPicker)
    : LeafTargetRegionFinder(pPairsReader, pPartitioner, pQualifier, pPosPicker)
{
}


TargetRegion *TargetRegionToLeftFinder::GetFinalRegion(const GenomePosition &gPos)
{
    std::vector<int> positions;
    if (heterozygous)
    {
        for (size_t i = 0; i < labels.size(); i++)
        {
            if (labels[i] == 1) positions.push_back(pairs[i]->GetRightReadPosition());
        }
    }
    else
    {
        transform(begin(pairs), end(pairs), back_inserter(positions),
                  [](SpanningPair *p){ return p->GetRightReadPosition(); });
    }

    int finalPos = pPosPicker->Pick(positions);
    int end = finalPos + pairs[0]->GetReadLength();
    int start = end - pPairsReader->GetMaxInsertSize();

    return new TargetRegion(pairs[0]->GetReferenceId(),
            start,
            end,
            gPos.GetPosition(),
            positions.size(),
            heterozygous);

}
