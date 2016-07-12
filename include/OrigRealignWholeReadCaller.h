#ifndef ORIGREALIGNWHOLEREADCALLER
#define ORIGREALIGNWHOLEREADCALLER

#include "realignmentcaller.h"


class OrigRealignWholeReadCaller : public IRealignmentCaller
{
public:
    OrigRealignWholeReadCaller(ISequenceAligner *pSeqAligner)
        : IRealignmentCaller(pSeqAligner)
    {}

    // IRealignmentCaller interface
private:
    ChromoFragment PreprocessFragment(ISoftClippedRead *pRead, const ChromoFragment &cFragment)
    {
        return pRead->CutFragment(cFragment);
    }

    std::string GetSeqFromRead(ISoftClippedRead *pRead)
    {
        return pRead->GetSequence();
    }

    ScoreParam MakeScoreParam()
    {
        return ScoreParam(2, -3, -10000);
    }

    bool IsAlnResultQualified(ISoftClippedRead *pRead, IAlignmentResult *pAlnResult, const CallParams &cParams)
    {
        return pRead->IsAlnResultQualified(dynamic_cast<SingleFragAlnResult *>(pAlnResult), cParams);
    }

    CallResult *MakeCallResult(ISoftClippedRead *pRead, int refStartPos, IAlignmentResult *pAlnResult)
    {
        return pRead->ToCallResult(refStartPos, dynamic_cast<SingleFragAlnResult *>(pAlnResult));
    }
};

#endif // ORIGREALIGNWHOLEREADCALLER

