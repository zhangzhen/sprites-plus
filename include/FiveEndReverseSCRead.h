#ifndef FIVEENDREVERSESCREAD_H
#define FIVEENDREVERSESCREAD_H

#include "softclippedread.h"

class FiveEndReverseSCRead : public ISoftClippedRead
{
public:
    FiveEndReverseSCRead(const std::string &name,
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

#endif // FIVEENDREVERSESCREAD_H
