#include "FiveEndReverseSCRead.h"


FiveEndReverseSCRead::FiveEndReverseSCRead(const std::string &name,
                                           const ChromosomeRegion &alignedRegion,
                                           const std::string &sequence,
                                           int mapQuality,
                                           int clippedLength,
                                           int smallDelSize,
                                           int smallInsSize)
    : ISoftClippedRead(name, alignedRegion, sequence, mapQuality, clippedLength, smallDelSize, smallInsSize)
{
}

GenomePosition FiveEndReverseSCRead::GetClipPosition()
{
    return alignedRegion.GetEnd();
}


std::string FiveEndReverseSCRead::GetType()
{
    return "5R";
}

std::string FiveEndReverseSCRead::GetClippedPart()
{
    return sequence.substr(sequence.length() - clippedLength);
}

ChromosomeRegionWithCi FiveEndReverseSCRead::ToRegionWithCi(int refStartPos, AlignmentResult alnResult)
{
    int delta = alnResult.GetMatch2().GetStart() - GetSequence().length() + clippedLength;

    int startPos = GetClipPosition().GetPosition();

    int endPos = refStartPos + alnResult.GetMatch1().GetStart();

    Interval cInterval;

    if (delta < 0)
    {
        startPos += delta;
        cInterval = Interval(0, abs(delta));
    }

    return ChromosomeRegionWithCi(GetReferenceId(),
                                  GetReferenceName(),
                                  startPos,
                                  cInterval,
                                  endPos,
                                  cInterval);
}
