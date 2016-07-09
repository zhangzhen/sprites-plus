#include "readrealigner.h"

AlignmentResult IReadRealigner::Realign(const ChromoFragment &cFragment, ISoftClippedRead *pRead, const ScoreParam &sParam)
{
//    if (pRead->GetClipPosition().GetPosition() == 42056489)
//    {
//        std::cout << cFragment.GetSequence() << std::endl;
//    }

    ChromoFragment modifiedFrag = PreprocessFragment(cFragment, pRead);

//    if (pRead->GetClipPosition().GetPosition() == 100683541)
//    {
//        std::cout << modifiedFrag.GetStartPos() << ", " << modifiedFrag.GetEndPos() << std::endl;
//        std::cout << modifiedFrag.GetSequence() << std::endl;
//    }

    AlignmentResult aResult = pSeqAligner->Align(modifiedFrag.GetSequence(), GetSeqFromRead(pRead), sParam);

    aResult.ShiftMatch1(modifiedFrag.GetStartPos());

    return aResult;
}
