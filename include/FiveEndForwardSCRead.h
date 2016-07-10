#ifndef FIVEENDFORWARDSCREAD_H
#define FIVEENDFORWARDSCREAD_H

#include "softclippedread.h"

class FiveEndForwardSCRead : public ISoftClippedRead
{
public:
    FiveEndForwardSCRead(const std::string &name,
                         const ChromosomeRegion& alignedRegion,
                         const std::string &sequence,
                         const std::string &refSeqPart,
                         int mapQuality,
                         int clippedLength,
                         int smallDelSize,
                         int smallInsSize);

    GenomePosition GetClipPosition();

    std::string GetType();

    std::string GetClippedPart();

    ChromoFragment CutFragment(const ChromoFragment &cFragment);

    ChromoFragment ExtendFragment(const ChromoFragment &cFragment);

    ChromosomeRegionWithCi ToRegionWithCi(const AlignmentResult& aResult);

    bool IsQualified(const AlignmentResult &aResult, const CallParams &cParams);
};

#endif // FIVEENDFORWARDSCREAD_H
