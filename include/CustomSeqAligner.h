#ifndef CUSTOMSEQALIGNER_H
#define CUSTOMSEQALIGNER_H

#include "sequencealigner.h"


std::string InsertIndel(std::string s, size_t pos);

class CustomSeqAligner : public ISequenceAligner
{
public:
    CustomSeqAligner() {}

    AlignmentResult Align(const std::string& v, const std::string& w, const ScoreParam &sParam);

};

#endif // CUSTOMSEQALIGNER_H
