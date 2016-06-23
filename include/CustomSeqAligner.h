#ifndef CUSTOMSEQALIGNER_H
#define CUSTOMSEQALIGNER_H

#include "sequencealigner.h"

class CustomSeqAligner : public ISequenceAligner
{
public:
    CustomSeqAligner() {}

    AlignmentResult Align(const std::string& seq1, const std::string& seq2, const ScoreParam &sParam);

};

// Compact an expanded CIGAR string into a regular cigar string
std::string compactCigar(const std::string& ecigar);

#endif // CUSTOMSEQALIGNER_H
