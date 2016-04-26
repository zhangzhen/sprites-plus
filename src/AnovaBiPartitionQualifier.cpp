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

    vector<vector<int>> groups;
    for (auto &elt : groupMap)
    {
        groups.push_back(elt.second);
    }

    double totalMean = GetMean(begin(insertSizes), end(insertSizes));

    double ssb = GetSSB(begin(groups), end(groups), totalMean);
    int df1 = groups.size() - 1;
    double msb = ssb / df1;

    double sse = GetSSE(begin(groups), end(groups), totalMean);
    int df2 = insertSizes.size() - groups.size();
    double mse = sse / df2;

    double fValue = msb / mse;

    fisher_f dist(df1, df2);
    double pValue = 1- cdf(dist, fValue);

    return pValue < threshold;
}
