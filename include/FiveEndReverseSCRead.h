#ifndef FIVEENDREVERSESCREAD_H
#define FIVEENDREVERSESCREAD_H

#include "softclippedread.h"

class FiveEndReverseSCRead : public ISoftClippedRead
{
public:
    FiveEndReverseSCRead(const std::string &name,
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

#endif // FIVEENDREVERSESCREAD_H
