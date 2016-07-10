#ifndef PARTIALREADREALIGNER
#define PARTIALREADREALIGNER

#include "readrealigner.h"

class PartialReadRealigner : public IReadRealigner
{
public:
    PartialReadRealigner(ISequenceAligner *pSeqAligner)
        : IReadRealigner(pSeqAligner)
    {}

    ChromoFragment PreprocessFragment(const ChromoFragment &cFragment, ISoftClippedRead *pRead)
    {
        return cFragment;
    }

    std::string GetSeqFromRead(ISoftClippedRead *pRead)
    {
        return pRead->GetClippedPart();
    }
};

#endif // PARTIALREADREALIGNER

