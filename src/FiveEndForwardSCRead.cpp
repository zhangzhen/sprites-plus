#include "FiveEndForwardSCRead.h"
#include "Deletion.h"


FiveEndForwardSCRead::FiveEndForwardSCRead(const std::string &name,
                                           const ChromosomeRegion &alignedRegion,
                                           const std::string &sequence,
                                           int mapQuality,
                                           int clippedLength,
                                           int smallDelSize,
                                           int smallInsSize)
    : ISoftClippedRead(name,
                       alignedRegion,
                       sequence,
                       mapQuality,
                       clippedLength,
                       smallDelSize,
                       smallInsSize)
{
}

GenomePosition FiveEndForwardSCRead::GetClipPosition()
{
    return alignedRegion.GetStart();
}

std::string FiveEndForwardSCRead::GetType()
{
    return "5F";
}

std::string FiveEndForwardSCRead::GetClippedPart()
{
    return sequence.substr(0, clippedLength);
}

ChromosomeRegionWithCi FiveEndForwardSCRead::ToRegionWithCi(int refStartPos, AlignmentResult alnResult)
{
    GenomePosition clipPosition = GetClipPosition();

    int delta = clippedLength - alnResult.GetMatch2().GetEnd() - 1;

    int endPos = clipPosition.GetPosition();

    int startPos = refStartPos + alnResult.GetMatch1().GetEnd();

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
