#include "AnovaBiPartitionQualifier.h"
#include "statistics.h"
#include <boost/math/distributions/fisher_f.hpp>

#include <map>
#include <cassert>

using namespace std;
using namespace boost::math;

AnovaBiPartitionQualifier::AnovaBiPartitionQualifier(double threshold)
    : threshold(threshold)
{
}

bool AnovaBiPartitionQualifier::IsQualified(const std::vector<int> &insertSizes, const std::vector<int> &labels)
{
    map<int, vector<int>> groupMap;
    assert(insertSizes.size() == labels.size());
    for (size_t i = 0; i < labels.size(); i++)
    {
        groupMap[labels[i]].push_back(insertSizes[i]);
    }

    double totalMean = GetMean(begin(insertSizes), end(insertSizes));

    double ssb = GetSSB(begin(groupMap), end(groupMap), totalMean);
    int df1 = groupMap.size() - 1;
    double msb = ssb / df1;

    double sse = GetSSE(begin(groupMap), end(groupMap), totalMean);
    int df2 = insertSizes.size() - groupMap.size();
    double mse = sse / df2;

    double fValue = msb / mse;

    fisher_f dist(df1, df2);
    double pValue = cdf(dist, fValue);

    return pValue < threshold;
}
