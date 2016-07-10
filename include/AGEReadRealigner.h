#ifndef AGEREADREALIGNER
#define AGEREADREALIGNER

#include "readrealigner.h"


class AGEReadRealigner : public IReadRealigner
{
public:
    AGEReadRealigner(ISequenceAligner *pSeqAligner)
        : IReadRealigner(pSeqAligner)
    {}

    ChromoFragment PreprocessFragment(const ChromoFragment &cFragment, ISoftClippedRead *pRead)
    {
        return pRead->ExtendFragment(cFragment);
    }

    std::string GetSeqFromRead(ISoftClippedRead *pRead)
    {
        return pRead->GetSequence();
    }

};

#endif // AGEREADREALIGNER

