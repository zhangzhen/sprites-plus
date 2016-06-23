#ifndef REVERSECUSTOMSEQALIGNER_H
#define REVERSECUSTOMSEQALIGNER_H

#include "SeqAlignerDecorator.h"
#include <algorithm>

class ReverseCustomSeqAligner : public SeqAlignerDecorator
{
public:
    ReverseCustomSeqAligner(ISequenceAligner* pSeqAligner)
        : SeqAlignerDecorator(pSeqAligner)
    {}

    AlignmentResult Align(const std::string &seq1, const std::string &seq2, const ScoreParam &sParam)
    {
        std::string s1 = seq1;
        reverse(s1.begin(), s1.end());
        std::string s2 = seq2;
        reverse(s2.begin(), s2.end());

        AlignmentResult res = SeqAlignerDecorator::Align(s1, s2, sParam);

        res.SetSeq1(seq1);
        res.SetSeq2(seq2);
        res.FlipMatch1(seq1.length());
        res.FlipMatch2(seq2.length());

        return res;

    }
};

#endif // REVERSECUSTOMSEQALIGNER_H
