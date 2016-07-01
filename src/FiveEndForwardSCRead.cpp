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

IVariant *FiveEndForwardSCRead::FindCall(int refStartPos, AlignmentResult alnResult, bool heterozygous)
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

    return new Deletion(GenomePosition(clipPosition.GetReferenceId(), clipPosition.GetReferenceName(), startPos),
                        interval,
                        GenomePosition(clipPosition.GetReferenceId(), clipPosition.GetReferenceName(), endPos),
                        interval,
                        heterozygous,
                        clipPosition,
                        GetType());
}
