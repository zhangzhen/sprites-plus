#include "CompositeTargetRegionFinder.h"

CompositeTargetRegionFinder::CompositeTargetRegionFinder(IChromosomeRegionMerger *pRegionMerger)
    : pRegionMerger(pRegionMerger)
{
}

ChromosomeRegion *CompositeTargetRegionFinder::FindRegion()
{
    std::vector<ChromosomeRegion*> regions;
    for (auto &finder : children)
    {
        ChromosomeRegion *pRegion = finder->FindRegion();
        if (pRegion)
        {
            regions.push_back(pRegion);
        }
    }
}
