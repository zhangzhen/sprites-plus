#ifndef FIVEENDREVERSESCREAD_H
#define FIVEENDREVERSESCREAD_H

#include "softclippedread.h"

class FiveEndReverseSCRead : public ISoftClippedRead
{
public:
    FiveEndReverseSCRead(const std::string &name,
                         int referenceId, const std::string &referenceName,
                         int clipPosition,
                         const std::string &sequence,
                         int mapQuality,
                         int clippedLength,
                         int smallDelSize,
                         int smallInsSize);

    std::string GetType();
};

#endif // FIVEENDREVERSESCREAD_H
