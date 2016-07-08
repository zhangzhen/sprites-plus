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

ChromoFragment FiveEndForwardSCRead::CutFragment(const ChromoFragment &cFragment)
{
    if (GetReferenceId() != cFragment.GetReferenceId())
    {
        error("This fragment cannot be cut because the fragment and the read are not on the same chromosome.");
    }

    int pos1 = cFragment.GetEndPos();

    int pos2 = GetClipPosition().GetPosition();

    if (pos2 <= pos1)
    {
        int removedLen = pos1 - pos2 + 1;

        return ChromoFragment(cFragment.GetStart(), cFragment.GetSequence().substr(0, cFragment.GetLength() - removedLen));
    }

    return cFragment;
}

ChromoFragment FiveEndForwardSCRead::ExtendFragment(const ChromoFragment &cFragment)
{
    return cFragment;
}

ChromosomeRegionWithCi FiveEndForwardSCRead::ToRegionWithCi(const AlignmentResult &aResult)
{
    GenomePosition clipPosition = GetClipPosition();

    int delta = clippedLength - aResult.GetAlignmentFragment1().GetMatch2().GetEnd() - 1;

    int endPos = clipPosition.GetPosition();

    int startPos = aResult.GetAlignmentFragment1().GetMatch1().GetEnd();

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

bool FiveEndForwardSCRead::IsQualified(const AlignmentResult &aResult, const CallParams &cParams)
{
    return aResult.GetAlignmentFragment1().GetMatch2Length() >= cParams.GetMinClip() &&
            aResult.GetAlignmentFragment1().GetPercentageIdentity() >= (1 - cParams.GetMaxErrorRate()) * 100;

}
