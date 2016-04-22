#include "FiveEndReverseSCRead.h"

FiveEndReverseSCRead::FiveEndReverseSCRead(const std::string &name,
                                           int referenceId,
                                           int clipPosition,
                                           const std::string &sequence,
                                           int mapQuality,
                                           int clippedLength,
                                           int smallDelSize,
                                           int smallInsSize)
    : ISoftClippedRead(name, referenceId, clipPosition, sequence, mapQuality, clippedLength, smallDelSize, smallInsSize)
{
}


std::string FiveEndReverseSCRead::GetType()
{
    return "5R";
}
