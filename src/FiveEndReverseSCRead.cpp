#include "FiveEndReverseSCRead.h"

#include "Deletion.h"


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

IVariant *FiveEndReverseSCRead::FindCall(int refStartPos, AlignmentResult alnResult, bool heterozygous)
{
    int delta = alnResult.GetMatch2().GetStart() - GetSequence().length() + clippedLength;

    int startPos = clipPosition.GetPosition();

    int endPos = refStartPos + alnResult.GetMatch1().GetStart();

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
