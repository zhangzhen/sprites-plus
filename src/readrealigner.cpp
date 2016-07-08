#include "readrealigner.h"

AlignmentResult IReadRealigner::Realign(const ChromoFragment &cFragment, ISoftClippedRead *pRead, const ScoreParam &sParam)
{
    ChromoFragment modifiedFrag = PreprocessFragment(cFragment, pRead);

    AlignmentResult aResult = pSeqAligner->Align(modifiedFrag.GetSequence(), GetSeqFromRead(pRead), sParam);

    aResult.ShiftMatch1(modifiedFrag.GetStartPos());

    return aResult;
}
