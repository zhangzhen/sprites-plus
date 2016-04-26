#ifndef CHROMOSOMEREGIONMERGE_H
#define CHROMOSOMEREGIONMERGE_H

#include "ChromosomeRegion.h"

class IChromosomeRegionMerger
{
public:
    virtual ChromosomeRegion *Merge(std::vector<ChromosomeRegion*> &regions) = 0;
};

#endif // CHROMOSOMEREGIONMERGE_H
