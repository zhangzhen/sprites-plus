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

//ChromosomeRegionWithCi FiveEndReverseSCRead::ToRegionWithCi(const AlignmentResult &aResult, int refStartPos)
//{
//    int s1 = aResult.GetAlignmentFragment1().GetMatch1().GetStart() + refStartPos;
//    int s2 = aResult.GetAlignmentFragment1().GetMatch2().GetStart();

//    if (!aResult.HasSingleFragment())
//    {
//        s1 = aResult.GetAlignmentFragment2().GetMatch1().GetStart() + refStartPos;
//        s2 = aResult.GetAlignmentFragment2().GetMatch2().GetStart();
//    }

//    int delta = s2 - GetSequence().length() + clippedLength;

//    int startPos = GetClipPosition().GetPosition();

//    int endPos = s1;

//    Interval cInterval;

//    if (delta < 0)
//    {
//        startPos += delta;
//        cInterval = Interval(0, abs(delta));
//    }

//    return ChromosomeRegionWithCi(GetReferenceId(),
//                                  GetReferenceName(),
//                                  startPos,
//                                  cInterval,
//                                  endPos,
//                                  cInterval);
//}

bool FiveEndReverseSCRead::IsAlnResultQualified(DoubleFragsAlnResult *pAlnResult, const CallParams &cParams)
{
    return IsQualified(pAlnResult->GetAlnFrag2LengthW(), pAlnResult->GetAlnFrag2PercentIdentity(), cParams);
}

CallResult *FiveEndReverseSCRead::ToCallResult(int refStartPos, DoubleFragsAlnResult *pAlnResult, ISequenceFetcher *pSeqFetcher)
{

    int startPos = GetClipPosition().GetPosition();
    int endPos = refStartPos + pAlnResult->GetAlnFrag2StartV();

    int f1_l1 = pAlnResult->GetAlnFrag1LengthV();

    int f1_d = refSeqPart.length() - f1_l1;

    if (f1_d > 0)
    {
        startPos -= f1_d;
    }
    else
    {
        endPos += f1_d;
    }

    std::string microIns = "";

    int n_bases = pAlnResult->NumOfWBasesBetweenTwoFrags();
    if (f1_d <= 0 && n_bases > 0)
    {
        int len = n_bases - f1_d;

        int s = alignedRegion.GetEndPosition() + 1;
        int e = s + len - 1;

        std::string t1_l = pSeqFetcher->Fetch(ChromosomeRegion(GetReferenceId(), GetReferenceName(), s, e)).GetSequence();
        std::string t2 = pAlnResult->WBasesBetweenTwoFragsExtLeft(-f1_d);

        int n_mismatch1 = len - NumOfIdenticalChars(t1_l, t2);

        std::string t1_r = pAlnResult->GetV().substr(pAlnResult->GetAlnFrag2StartV() - len, len);

        int n_mismatch2 = len - NumOfIdenticalChars(t1_r, t2);

//        if (GetClipPosition().GetPosition() == 34905297)
//        {
//            std::cout << t1_r << std::endl;
//            std::cout << t2 << std::endl;
//        }

        if (n_mismatch1 <= 1)
        {
            startPos += n_bases;
        }
        else if (n_mismatch2 <= 1)
        {
            endPos -= n_bases;
        }
        else
        {
            microIns = t2;
        }
    }

    return new CallResult(ChromosomeRegion(GetReferenceId(),
                                       GetReferenceName(),
                                       startPos,
                                       endPos),
                      microIns);
}
