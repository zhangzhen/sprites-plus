#include "Interval.h"

std::ostream& operator <<(std::ostream& stream, const Interval& interval)
{
    stream << "[" << interval.start << "," << interval.end << "]";
    return stream;
}
