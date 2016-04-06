#include "TargetRegionToRightFinder.h"
#include <algorithm>

TargetRegionToRightFinder::TargetRegionToRightFinder(ISpanningPairsReader *pPairsReader,
                                                     IBiPartitioner *pPartitioner,
                                                     IBiPartitionQualifier *pQualifier,
                                                     IPositionPicker *pPosPicker)
    : LeafTargetRegionFinder(pPairsReader, pPartitioner, pQualifier, pPosPicker)
{
}

TargetRegion *TargetRegionToRightFinder::GetFinalRegion(const GenomePosition &gPos)
{
    std::vector<int> positions;
    if (heterozygous)
    {
        for (size_t i = 0; i < labels.size(); i++)
        {
            if (labels[i] == 1) positions.push_back(pairs[i]->GetLeftReadPosition());
        }
    }
    else
    {
        transform(begin(pairs), end(pairs), back_inserter(positions),
                  [](SpanningPair *p){ return p->GetLeftReadPosition(); });
    }

    int finalPos = pPosPicker->Pick(positions);
    int start = finalPos;
    int end = start + pPairsReader->GetMaxInsertSize();

    return new TargetRegion(pairs[0]->GetReferenceId(),
            start,
            end,
            positions.size(),
            heterozygous);

}
