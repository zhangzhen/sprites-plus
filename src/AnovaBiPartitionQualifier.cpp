#include "AnovaBiPartitionQualifier.h"

AnovaBiPartitionQualifier::AnovaBiPartitionQualifier(double threshold)
    : threshold(threshold)
{
}

bool AnovaBiPartitionQualifier::IsQualified(const std::vector<int> &insertSizes, const std::vector<int> &labels)
{
    double pValue;
    return pValue < threshold;
}
