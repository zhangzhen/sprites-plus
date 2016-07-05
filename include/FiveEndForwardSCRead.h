#ifndef FIVEENDFORWARDSCREAD_H
#define FIVEENDFORWARDSCREAD_H

#include "softclippedread.h"

class FiveEndForwardSCRead : public ISoftClippedRead
{
public:
    FiveEndForwardSCRead(const std::string &name,
                         const ChromosomeRegion& alignedRegion,
                         const std::string &sequence,
                         int mapQuality,
                         int clippedLength,
                         int smallDelSize,
                         int smallInsSize);

    GenomePosition GetClipPosition();

    std::string GetType();

    std::string GetClippedPart();

    ChromosomeRegionWithCi ToRegionWithCi(int refStartPos, AlignmentResult alnResult);
};

#endif // FIVEENDFORWARDSCREAD_H
