#include "FiveEndReverseSCRead.h"

FiveEndReverseSCRead::FiveEndReverseSCRead(const std::string &name,
                                           int referenceId,
                                           const std::string& referenceName,
                                           int clipPosition,
                                           const std::string &sequence,
                                           int mapQuality,
                                           int clippedLength,
                                           int smallDelSize,
                                           int smallInsSize)
    : ISoftClippedRead(name, referenceId, referenceName, clipPosition, sequence, mapQuality, clippedLength, smallDelSize, smallInsSize)
{
}


std::string FiveEndReverseSCRead::GetType()
{
    return "5R";
}
