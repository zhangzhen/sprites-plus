#ifndef SEQUENCEALIGNER_H
#define SEQUENCEALIGNER_H

#include "AlignmentResult.h"
#include "ScoreParam.h"

class ISequenceAligner
{
public:
    virtual ~ISequenceAligner() {}
    virtual AlignmentResult Align(const std::string& v, const std::string& w, const ScoreParam &sParam) = 0;
};

#endif // SEQUENCEALIGNER_H
