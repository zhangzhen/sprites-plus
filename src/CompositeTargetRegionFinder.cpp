#include "CompositeTargetRegionFinder.h"

CompositeTargetRegionFinder::CompositeTargetRegionFinder(IChromosomeRegionMerger *pRegionMerger)
    : pRegionMerger(pRegionMerger)
{
}

ChromosomeRegion *CompositeTargetRegionFinder::FindRegion(const GenomePosition &gPos)
{
    std::vector<ChromosomeRegion*> regions;
    for (auto &finder : children)
    {
        ChromosomeRegion *pRegion = finder->FindRegion(gPos);
        if (pRegion)
        {
            regions.push_back(pRegion);
        }
    }
    return pRegionMerger->Merge(regions);
}
