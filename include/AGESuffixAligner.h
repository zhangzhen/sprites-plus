#include "sequencealigner.h"


class AGESuffixAligner : public ISequenceAligner
{
public:
    AGESuffixAligner() {}

    AlignmentResult Align(const std::string& v, const std::string& w, const ScoreParam &sParam);
};
