#ifndef WHOLEREADREALIGNER
#define WHOLEREADREALIGNER

#include "readrealigner.h"

class WholeReadRealigner : public IReadRealigner
{
public:
    WholeReadRealigner(ISequenceAligner *pSeqAligner)
        : IReadRealigner(pSeqAligner)
    {}

private:
    ChromoFragment PreprocessFragment(const ChromoFragment &cFragment, ISoftClippedRead *pRead)
    {
        return pRead->CutFragment(cFragment);
    }

    std::string GetSeqFromRead(ISoftClippedRead *pRead)
    {
        return pRead->GetSequence();
    }
};

#endif // WHOLEREADREALIGNER

