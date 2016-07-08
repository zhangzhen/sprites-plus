#include "Interval.h"

std::ostream& operator <<(std::ostream& stream, const Interval& interval)
{
    stream << "[" << interval.start << "," << interval.end << "]";
    return stream;
}

const Interval operator + (const Interval& one, int x)
{
    Interval result = one;
    result += x;
    return result;
}

void Interval::Flip(int origLength)
{
    int tmp = origLength - start - 1;
    start = origLength - end - 1;
    end = tmp;
    CheckRep();
}
