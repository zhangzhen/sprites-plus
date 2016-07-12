#ifndef SEQALIGNERDECORATOR_H
#define SEQALIGNERDECORATOR_H

#include "sequencealigner.h"

class SeqAlignerDecorator : public ISequenceAligner
{
public:
    SeqAlignerDecorator(ISequenceAligner *pSeqAligner)
        : pSeqAligner(pSeqAligner)
    {}

    ~SeqAlignerDecorator()
    {
        delete pSeqAligner;
    }

    IAlignmentResult *Align(const std::string &seq1, const std::string &seq2, const ScoreParam &sParam)
    {
        return pSeqAligner->Align(seq1, seq2, sParam);
    }

private:
    ISequenceAligner *pSeqAligner;
};

#endif // SEQALIGNERDECORATOR_H
