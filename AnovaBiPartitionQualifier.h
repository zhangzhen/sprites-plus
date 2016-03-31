#ifndef ANOVABIPARTITIONQUALIFIER_H
#define ANOVABIPARTITIONQUALIFIER_H

#include "bipartitionqualifier.h"

class AnovaBiPartitionQualifier : public IBiPartitionQualifier
{
public:
    AnovaBiPartitionQualifier();

    bool IsQualified(const std::vector<int> &insertSizes, const std::vector<int> &labels);
};

#endif // ANOVABIPARTITIONQUALIFIER_H
