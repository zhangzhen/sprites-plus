#include "AGESuffixAligner.h"
#include "age/AGEaligner.hh"
#include "error.h"


AligmentFragment AGESuffixAligner::Align(const std::string &s1, const std::string &s2, const ScoreParam &sParam)
{

    int flag = AGEaligner::INDEL_FLAG;


    Scorer scr(sParam.GetMatch(), sParam.GetMismatch(), sParam.GetGapStart(), sParam.GetGap());

    Sequence seq1(s1.c_str());
    Sequence seq2(s2.c_str());

    AGEaligner aligner(seq1, seq2);

    if(aligner.align(scr,flag)) error("AGE alignment error");

    AliFragment *frags = aligner.GetAliFragments();
    AliFragment *f = frags;

    while (f->next())
    {
        f = f->next();
    }

    return AlignmentFragment(f->ali1(),
                             f->ali2(),
                             aligner.score(),
                             Interval(f->start1(), f->end1()),
                             Interval(f->start2(), f->end2()));
}
