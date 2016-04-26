#include "FiveEndForwardSCRead.h"

FiveEndForwardSCRead::FiveEndForwardSCRead(const std::string &name,
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


std::string FiveEndForwardSCRead::GetType()
{
    return "5F";
}
