#ifndef TARGETREGIONTORIGHTFINDER_H
#define TARGETREGIONTORIGHTFINDER_H

#include "LeafTargetRegionFinder.h"

class TargetRegionToRightFinder : public LeafTargetRegionFinder
{
public:
    TargetRegionToRightFinder(ISpanningPairsReader* pPairsReader,
                              IBiPartitioner* pPartitioner,
                              IBiPartitionQualifier* pQualifier,
                              IPositionPicker* pPosPicker);

protected:
    ChromosomeRegion *GetFinalRegion();
};

#endif // TARGETREGIONTORIGHTFINDER_H
