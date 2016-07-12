#ifndef DOUBLEFRAGSALNRESULT
#define DOUBLEFRAGSALNRESULT

#include "alignmentresult.h"
#include "AlignmentFragment.h"


class DoubleFragsAlnResult : public IAlignmentResult
{
public:
    DoubleFragsAlnResult(const std::string& v,
                         const std::string& w,
                         int score,
                         const AlignmentFragment& alnFrag1,
                         const AlignmentFragment& alnFrag2)
        : IAlignmentResult(v, w, score),
          alnFrag1(alnFrag1),
          alnFrag2(alnFrag2)
    {}

    int GetAlnFrag1EndV() const
    {
        return alnFrag1.GetMatch1().GetEnd();
    }

    int GetAlnFrag2StartV() const
    {
        return alnFrag2.GetMatch1().GetStart();
    }

    int GetAlnFrag1LengthV() const
    {
        return alnFrag1.GetMatch1().Length();
    }

    int GetAlnFrag1LengthW() const
    {
        return alnFrag1.GetMatch2().Length();
    }

    int GetAlnFrag2LengthV() const
    {
        return alnFrag2.GetMatch1().Length();
    }

    int GetAlnFrag2LengthW() const
    {
        return alnFrag2.GetMatch2().Length();
    }

    double GetAlnFrag1PercentIdentity() const
    {
        return alnFrag1.GetPercentageIdentity();
    }

    double GetAlnFrag2PercentIdentity() const
    {
        return alnFrag2.GetPercentageIdentity();
    }

    AlignmentFragment GetAlnFrag1() const { return alnFrag1; }
    AlignmentFragment GetAlnFrag2() const { return alnFrag2; }

private:
    AlignmentFragment alnFrag1;
    AlignmentFragment alnFrag2;

    // IAlignmentResult interface
public:
    void PrintAlignment();
    double GetPercentIdentity();
    std::string GetMicroIns();

    void Flip();
};

#endif // DOUBLEFRAGSALNRESULT

