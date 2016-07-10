#include "FiveEndReverseSCRead.h"


FiveEndReverseSCRead::FiveEndReverseSCRead(const std::string &name,
                                           const ChromosomeRegion &alignedRegion,
                                           const std::string &sequence,
                                           const std::string &refSeqPart,
                                           int mapQuality,
                                           int clippedLength,
                                           int smallDelSize,
                                           int smallInsSize)
    : ISoftClippedRead(name,
                       alignedRegion,
                       sequence,
                       refSeqPart,
                       mapQuality,
                       clippedLength,
                       smallDelSize,
                       smallInsSize)
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

ChromoFragment FiveEndReverseSCRead::CutFragment(const ChromoFragment &cFragment)
{
    if (GetReferenceId() != cFragment.GetReferenceId())
    {
        error("This fragment cannot be cut because the fragment and the read are not on the same chromosome.");
    }

    int pos1 = cFragment.GetStartPos();

    int pos2 = GetClipPosition().GetPosition();

    if (pos1 <= pos2)
    {
        return ChromoFragment(GenomePosition(GetReferenceId(), GetReferenceName(), pos2),
                              cFragment.GetSequence().substr(pos2 - pos1 + 1));
    }

    return cFragment;
}

ChromoFragment FiveEndReverseSCRead::ExtendFragment(const ChromoFragment &cFragment)
{
    if (GetReferenceId() != cFragment.GetReferenceId())
    {
        error("This fragment cannot be cut because the fragment and the read are not on the same chromosome.");
    }

    int s1 = cFragment.GetStartPos();
    if (s1 <= alignedRegion.GetStartPosition())
    {
        return cFragment;
    }

    ChromoFragment newFrag = cFragment;

    std::string newSeq = refSeqPart;

    int n = refSeqPart.length();

    int e2 = alignedRegion.GetEndPosition();
    if (s1 <= e2)
    {
        n = alignedRegion.GetLength() - e2 + s1 - 1;
        newSeq = refSeqPart.substr(0, n);
    }

    newFrag.SetStart(newFrag.GetStart() - n);
    newFrag.SetSequence(newSeq + newFrag.GetSequence());

    return newFrag;
}

ChromosomeRegionWithCi FiveEndReverseSCRead::ToRegionWithCi(const AlignmentResult &aResult, int refStartPos)
{
    int s1 = aResult.GetAlignmentFragment1().GetMatch1().GetStart() + refStartPos;
    int s2 = aResult.GetAlignmentFragment1().GetMatch2().GetStart();

    if (!aResult.HasSingleFragment())
    {
        s1 = aResult.GetAlignmentFragment2().GetMatch1().GetStart() + refStartPos;
        s2 = aResult.GetAlignmentFragment2().GetMatch2().GetStart();
    }

    int delta = s2 - GetSequence().length() + clippedLength;

    int startPos = GetClipPosition().GetPosition();

    int endPos = s1;

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

bool FiveEndReverseSCRead::IsQualified(const AlignmentResult &aResult, const CallParams &cParams)
{
    if (aResult.HasSingleFragment())
    {
        return aResult.GetAlignmentFragment1().GetMatch2Length() >= cParams.GetMinClip() &&
                aResult.GetAlignmentFragment1().GetPercentageIdentity() >= (1 - cParams.GetMaxErrorRate()) * 100;
    }

    return aResult.GetAlignmentFragment2().GetMatch2Length() >= cParams.GetMinClip() &&
            aResult.GetAlignmentFragment2().GetPercentageIdentity() >= (1 - cParams.GetMaxErrorRate()) * 100;

}
