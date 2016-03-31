#ifndef LEAFTARGETREGIONFINDER_H
#define LEAFTARGETREGIONFINDER_H

#include "targetregionfinder.h"

class LeafTargetRegionFinder : ITargetRegionFinder
{
public:
    LeafTargetRegionFinder(ISpanningPairsReader* pPairsReader,
                           IBiPartitioner* pPartitioner,
                           IBiPartitionQualifier* pQualifier,
                           IPositionPicker* pPosPicker);
    ChromosomeRegion* FindRegion();

protected:
    virtual ChromosomeRegion* GetFinalRegion() = 0;

    std::vector<SpanningPair*> pairs;
    ISpanningPairsReader* pPairsReader;
    IBiPartitioner* pPartitioner;
    IBiPartitionQualifier* pQualifier;
    IPositionPicker* pPosPicker;

};

#endif // LEAFTARGETREGIONFINDER_H
