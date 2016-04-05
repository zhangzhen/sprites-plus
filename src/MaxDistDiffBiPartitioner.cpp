#include "MaxDistDiffBiPartitioner.h"

MaxDistDiffBiPartitioner::MaxDistDiffBiPartitioner()
{
}

std::vector<int> MaxDistDiffBiPartitioner::Partition(const std::vector<int> &insertSizes)
{
    std::vector<int> indices(insertSizes.size());
    std::itoa(std::begin(indices), std::end(indices), 0);
    std::sort(std::begin(indices), std::end(indices),
              [&](int x, int y) { return insertSizes[x] < insertSizes[y]; });

    std::vector<int> result[insertSizes.size()];
    std::adjacent_difference(std::begin(indices), std::end(indices), std::begin(result),
                             [&](int x, int y) { return insertSizes[x] - insertSizes[y]; });
    int indexOfIndices = std::distance(std::begin(result),
                              std::max_element(std::begin(result)+1, std::end(result)));
}
