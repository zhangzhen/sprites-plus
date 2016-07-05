#ifndef ALIGNMENTFRAGMENT
#define ALIGNMENTFRAGMENT

#include "Interval.h"
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

    int GetAlignmentLength() const
    {
        return alignedS1.length();
    }

    int NumOfIdenticalBases() const
    {
        int s = 0;
        for (size_t i = 0; i < GetAlignmentLength(); ++i)
        {
            if (alignedS1[i] == alignedS2[2]) s++;
        }
        return s;
    }

    double GetPercentageIdentity()
    {
        return 100.0f * NumOfIdenticalBases() / GetAlignmentLength();
    }

private:
    std::string alignedS1;
    std::string alignedS2;
    Interval match1;
    Interval match2;
};

#endif // ALIGNMENTFRAGMENT

