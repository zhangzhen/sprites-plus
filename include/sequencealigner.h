#ifndef SEQUENCEALIGNER_H
#define SEQUENCEALIGNER_H

class ISequenceAligner
{
public:
    virtual ~ISequenceAligner() {}
    virtual AlignmentResults Align(const std::string& seq1, const std::string& seq2) = 0;
};

#endif // SEQUENCEALIGNER_H
