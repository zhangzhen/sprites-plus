#ifndef READREALIGNER
#define READREALIGNER

#include "softclippedread.h"
#include "sequencealigner.h"

class IReadRealigner
{
public:
    IReadRealigner(ISequenceAligner *pSeqAligner)
        : pSeqAligner(pSeqAligner)
    {}

    virtual ~IReadRealigner() { delete pSeqAligner; }
    AlignmentResult Realign(const ChromoFragment& cFragment, ISoftClippedRead *pRead, const ScoreParam &sParam);

protected:
    virtual ChromoFragment PreprocessFragment(const ChromoFragment& cFragment, ISoftClippedRead *pRead) = 0;
    virtual std::string GetSeqFromRead(ISoftClippedRead *pRead) = 0;

private:
    ISequenceAligner *pSeqAligner;
};

#endif // READREALIGNER

