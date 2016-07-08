#include "AlignmentResult.h"

#include <sstream>
#include <algorithm>


void AlignmentResult::Flip()
{
    std::reverse(seq1.begin(), seq1.end());
    std::reverse(seq2.begin(), seq2.end());

    aFragment1.Flip(seq1.length(), seq2.length());

    if (!single)
    {
        aFragment2.Flip(seq1.length(), seq2.length());
    }
}

void AlignmentResult::ShiftMatch1(int val)
{
    aFragment1.ShiftMatch1(val);

    if (!single) {
        aFragment2.ShiftMatch1(val);
    }

}
