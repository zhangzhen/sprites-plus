#include "FiveEndForwardSCRead.h"
#include "Deletion.h"


FiveEndForwardSCRead::FiveEndForwardSCRead(const std::string &name,
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
    int e1 = cFragment.GetEndPos();

    if (e1 >= alignedRegion.GetEndPosition())
    {
        return cFragment;
    }

    ChromoFragment newFrag = cFragment;

    std::string newSeq = refSeqPart;

    int s2 = alignedRegion.GetStartPosition();

    if (s2 <= e1)
    {
        newSeq = newSeq.substr(e1 - s2 + 1);
    }

    newFrag.SetSequence(newFrag.GetSequence() + newSeq);

    return newFrag;
}

//ChromosomeRegionWithCi FiveEndForwardSCRead::ToRegionWithCi(const AlignmentResult &aResult, int refStartPos)
//{
//    GenomePosition clipPosition = GetClipPosition();

//    int nHom = aResult.NumOfHomToRight();

//    int delta = clippedLength - aResult.GetAlignmentFragment1().GetMatch2().GetEnd() -nHom - 1;

//    int endPos = clipPosition.GetPosition();

//    int startPos = aResult.GetAlignmentFragment1().GetMatch1().GetEnd() + nHom + refStartPos;

//    Interval cInterval;

//    if (delta < 0)
//    {
//        startPos += delta;
//        cInterval = Interval(0, abs(delta));
//    }

//    if (!aResult.HasSingleFragment())
//    {
//        int f2_l1 = aResult.GetAlignmentFragment2().GetMatch1().Length();
//        int f2_d = refSeqPart.length() - f2_l1;
//        if (f2_d > 0)
//            endPos += f2_d;
//    }

//    return ChromosomeRegionWithCi(GetReferenceId(),
//                                  GetReferenceName(),
//                                  startPos,
//                                  cInterval,
//                                  endPos,
//                                  cInterval);
//}

bool FiveEndForwardSCRead::IsAlnResultQualified(DoubleFragsAlnResult *pAlnResult, const CallParams &cParams)
{
    return IsQualified(pAlnResult->GetAlnFrag1LengthW(), pAlnResult->GetAlnFrag1PercentIdentity(), cParams);
}

CallResult *FiveEndForwardSCRead::ToCallResult(int refStartPos, DoubleFragsAlnResult *pAlnResult, ISequenceFetcher *pSeqFetcher)
{
    int startPos = refStartPos + pAlnResult->GetAlnFrag1EndV();
    int endPos = GetClipPosition().GetPosition();

    int f2_l1 = pAlnResult->GetAlnFrag2LengthV();
    int f2_d = refSeqPart.length() - f2_l1;
    if (f2_d > 0)
    {
        endPos += f2_d;
    }
    else
    {
        startPos -= f2_d;
    }

    int n_bases = pAlnResult->NumOfWBasesBetweenTwoFrags();

//    if (GetClipPosition().GetPosition() == 145580076)
//    {
//        pAlnResult->PrintAlignment();
//        std::cout << f2_d << " " << n_bases << std::endl;
//    }

    if (f2_d == 0 && n_bases > 0)
    {
        int e = alignedRegion.GetStartPosition() - 1;
        int s = e - n_bases + 1;
        std::string v = pSeqFetcher->Fetch(ChromosomeRegion(GetReferenceId(), GetReferenceName(), s, e)).GetSequence();
        std::string w = pAlnResult->WBasesBetweenTwoFrags();
        int n_id = NumOfIdenticalChars(v, w) + pAlnResult->GetAlnFrag2().NumOfIdenticalBases();
        int aln_len = n_bases + pAlnResult->GetAlnFrag2().GetAlignmentLength();
        double percentId = 100.0f * n_id / aln_len;
        if (percentId >= 90)
        {
            endPos -= n_bases;
        }
    }

    return new CallResult(ChromosomeRegion(GetReferenceId(),
                                       GetReferenceName(),
                                       startPos,
                                       endPos),
                      "");
}
