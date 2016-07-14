#ifndef REALIGNCLIPPEDPARTCALLER
#define REALIGNCLIPPEDPARTCALLER

#include "realignmentcaller.h"


class RealignClippedPartCaller : public IRealignmentCaller
{
public:
    RealignClippedPartCaller() (ISequenceAligner *pSeqAligner, ISequenceFetcher *pSeqFetcher)
        : IRealignmentCaller(pSeqAligner, pSeqFetcher)
    {}


    // IRealignmentCaller interface
private:
    ChromoFragment PreprocessFragment(ISoftClippedRead *pRead, const ChromoFragment &cFragment);
    std::string GetSeqFromRead(ISoftClippedRead *pRead);
    ScoreParam MakeScoreParam();
    bool IsAlnResultQualified(ISoftClippedRead *pRead, IAlignmentResult *pAlnResult, const CallParams &cParams);
    CallResult *MakeCallResult(ISoftClippedRead *pRead, int refStartPos, IAlignmentResult *pAlnResult);
};

#endif // REALIGNCLIPPEDPARTCALLER

