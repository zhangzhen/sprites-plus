#include "MaxDistDiffBiPartitioner.h"

#include <numeric>
#include <algorithm>

using namespace std;

MaxDistDiffBiPartitioner::MaxDistDiffBiPartitioner()
{
}

std::vector<int> MaxDistDiffBiPartitioner::Partition(const std::vector<int> &insertSizes)
{
    vector<int> indices(insertSizes.size());
    iota(begin(indices), end(indices), 0);
    sort(begin(indices), end(indices),
              [&](int x, int y) { return insertSizes[x] < insertSizes[y]; });

    vector<int> result(insertSizes.size());
    adjacent_difference(begin(indices), end(indices), begin(result),
                             [&](int x, int y) { return insertSizes[x] - insertSizes[y]; });
    int indexOfIndices = distance(begin(result),
                              max_element(begin(result)+1, end(result)));
}
