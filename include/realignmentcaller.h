#ifndef REALIGNMENTCALLER
#define REALIGNMENTCALLER

#include "sequencealigner.h"
#include "CallResult.h"
#include "softclippedread.h"
#include "ChromoFragment.h"
#include "CallParams.h"


class IRealignmentCaller
{
public:
    IRealignmentCaller(ISequenceAligner *pSeqAligner)
        : pSeqAligner(pSeqAligner)
    {}
    virtual ~IRealignmentCaller() {}

    CallResult *Call(ISoftClippedRead *pRead, const ChromoFragment& cFragment, const CallParams& cParams)
    {
        ChromoFragment modifiedFrag = PreprocessFragment(pRead, cFragment);

        std::string v = modifiedFrag.GetSequence();
        std::string w = GetSeqFromRead(pRead);

        IAlignmentResult *pAlnResult = pSeqAligner->Align(v, w, MakeScoreParam());

//        if (pRead->GetClipPosition().GetPosition() == 98353306)
//        {
//            std::cout << cFragment.GetSequence() << std::endl;
//            std::cout << modifiedFrag.GetStartPos() << std::endl;
//            std::cout << modifiedFrag.GetSequence() << std::endl;
//            std::cout << pRead->GetAlignedRegion() << std::endl;
//            std::cout << v << std::endl;
//            std::cout << "#####################" << std::endl;
//            pAlnResult->PrintAlignment();
//        }

        if (!IsAlnResultQualified(pRead, pAlnResult, cParams))
        {
            return NULL;
        }

        return MakeCallResult(pRead, modifiedFrag.GetStartPos(), pAlnResult);
    }

private:
    ISequenceAligner *pSeqAligner;

    virtual ChromoFragment PreprocessFragment(ISoftClippedRead *pRead, const ChromoFragment& cFragment) = 0;
    virtual std::string GetSeqFromRead(ISoftClippedRead *pRead) = 0;
    virtual ScoreParam MakeScoreParam() = 0;
    virtual bool IsAlnResultQualified(ISoftClippedRead *pRead, IAlignmentResult *pAlnResult, const CallParams& cParams) = 0;
    virtual CallResult *MakeCallResult(ISoftClippedRead *pRead, int refStartPos, IAlignmentResult *pAlnResult) = 0;
};

#endif // REALIGNMENTCALLER

