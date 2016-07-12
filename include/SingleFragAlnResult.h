#ifndef SINGLEFRAGALNRESULT
#define SINGLEFRAGALNRESULT

#include "alignmentresult.h"
#include "AlignmentFragment.h"


class SingleFragAlnResult : public IAlignmentResult
{
public:
    SingleFragAlnResult(const std::string& v,
                        const std::string& w,
                        int score,
                        const AlignmentFragment& alnFrag)
        : IAlignmentResult(v, w, score),
          alnFrag(alnFrag)
    {}

    int GetAlnFragStartV() const
    {
        return alnFrag.GetMatch1().GetStart();
    }

    int GetAlnFragEndV() const
    {
        return alnFrag.GetMatch1().GetEnd();
    }

    Interval GetAlnFragMatchV() const
    {
        return alnFrag.GetMatch1();
    }

    Interval GetAlnFragMatchW() const
    {
        return alnFrag.GetMatch2();
    }

private:
    AlignmentFragment alnFrag;

    // IAlignmentResult interface
public:
    void PrintAlignment()
    {
        alnFrag.PrintAlignment();
    }

    double GetPercentIdentity()
    {
        return alnFrag.GetPercentageIdentity();
    }

    std::string GetMicroIns()
    {
        return "";
    }

    void Flip();
};

#endif // SINGLEFRAGALNRESULT

