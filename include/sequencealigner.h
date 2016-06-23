#ifndef SEQUENCEALIGNER_H
#define SEQUENCEALIGNER_H

#include "AlignmentResult.h"
#include "ScoreParam.h"

class ISequenceAligner
{
public:
    virtual ~ISequenceAligner() {}
    virtual AlignmentResult Align(const std::string& seq1, const std::string& seq2, const ScoreParam &sParam) = 0;
};

#endif // SEQUENCEALIGNER_H
