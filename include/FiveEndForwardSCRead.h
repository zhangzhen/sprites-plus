#ifndef FIVEENDFORWARDSCREAD_H
#define FIVEENDFORWARDSCREAD_H

#include "softclippedread.h"

class FiveEndForwardSCRead : public ISoftClippedRead
{
public:
    FiveEndForwardSCRead(const std::string &name,
                         int referenceId,
                         const std::string &referenceName,
                         int clipPosition,
                         const std::string &sequence,
                         int mapQuality,
                         int clippedLength,
                         int smallDelSize,
                         int smallInsSize);

    std::string GetType();

    IVariant *FindCall(int refStartPos, AlignmentResult alnResult, bool heterozygous);
};

#endif // FIVEENDFORWARDSCREAD_H
