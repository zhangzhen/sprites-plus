#ifndef ALIGNMENTFRAGMENT
#define ALIGNMENTFRAGMENT

#include "Interval.h"
#include "error.h"

#include <string>

class AlignmentFragment
{
public:
    AlignmentFragment(const std::string& alignedS1,
                      const std::string& alignedS2,
                      const Interval& match1,
                      const Interval& match2)
        : alignedS1(alignedS1),
          alignedS2(alignedS2),
          match1(match1),
          match2(match2)
    {}

    AlignmentFragment()
        : AlignmentFragment("NA", "NA", Interval(), Interval())
    {}

    int GetAlignmentLength() const
    {
        return alignedS1.length();
    }

    Interval GetMatch1() const { return match1; }
    Interval GetMatch2() const { return match2; }

    int NumOfIdenticalBases() const;

    void PrintAlignment() const;

    double GetPercentageIdentity()
    {
        if (GetAlignmentLength() == 0) error("Divided by zero.");

        return 100.0f * NumOfIdenticalBases() / GetAlignmentLength();
    }

    void Flip(int origLength1, int origLength2);

    void ShiftMatch1(int val)
    {
        match1 += val;
    }

    int GetMatch2Length() const
    {
        return match2.Length();
    }

private:
    std::string alignedS1;
    std::string alignedS2;
    Interval match1;
    Interval match2;
};

#endif // ALIGNMENTFRAGMENT

