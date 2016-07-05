#include "sequencealigner.h"


class AGESuffixAligner : public ISequenceAligner
{
public:
    AGESuffixAligner() {}

    AligmentFragment Align(const std::string& s1, const std::string& s2, const ScoreParam &sParam);
};
