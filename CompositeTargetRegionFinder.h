#ifndef COMPOSITETARGETREGIONFINDER_H
#define COMPOSITETARGETREGIONFINDER_H

#include "targetregionfinder.h"
#include "chromosomeregionmerge.h"

class CompositeTargetRegionFinder : public ITargetRegionFinder
{
public:
    CompositeTargetRegionFinder(IChromosomeRegionMerger *pRegionMerger);
    void Add(ITargetRegionFinder *pRegionFinder)
    {
        children.push_back(pRegionFinder);
    }
    ChromosomeRegion *FindRegion();

private:
    std::vector<ITargetRegionFinder*> children;
    IChromosomeRegionMerger *pRegionMerger;
};

#endif // COMPOSITETARGETREGIONFINDER_H
