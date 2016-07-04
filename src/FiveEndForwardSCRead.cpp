#include "FiveEndForwardSCRead.h"
#include "Deletion.h"


FiveEndForwardSCRead::FiveEndForwardSCRead(const std::string &name,
                                           int referenceId,
                                           const std::string& referenceName,
                                           int clipPosition,
                                           const std::string &sequence,
                                           int mapQuality,
                                           int clippedLength,
                                           int smallDelSize,
                                           int smallInsSize)
    : ISoftClippedRead(name,
                       referenceId,
                       referenceName,
                       clipPosition,
                       sequence,
                       mapQuality,
                       clippedLength,
                       smallDelSize,
                       smallInsSize)
{
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
    int delta = clippedLength - alnResult.GetMatch2().GetEnd() - 1;

    int endPos = clipPosition.GetPosition();

    int startPos = refStartPos + alnResult.GetMatch1().GetEnd();

    Interval interval;

    if (delta < 0)
    {
        startPos += delta;
        interval = Interval(0, abs(delta));
    }

    return ChromosomeRegionWithCi(GenomePosition(clipPosition.GetReferenceId(), clipPosition.GetReferenceName(), startPos),
                                  interval,
                                  GenomePosition(clipPosition.GetReferenceId(), clipPosition.GetReferenceName(), endPos),
                                  interval);
}
