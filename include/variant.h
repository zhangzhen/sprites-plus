#ifndef VARIANT_H
#define VARIANT_H

#include "GenomePosition.h"
#include "Interval.h"

#include <string>
#include <sstream>

class IVariant
{
public:
    IVariant(const GenomePosition& start,
             const Interval& startInterval,
             const GenomePosition& end,
             const Interval& endInterval,
             bool heterozygous,
             const GenomePosition& fromClipPosition,
             const std::string& fromReadType)
        : start(start),
          startInterval(startInterval),
          end(end),
          endInterval(endInterval),
          heterozygous(heterozygous),
          fromClipPosition(fromClipPosition),
          fromReadType(fromReadType)
    {}

    virtual ~IVariant() {}

    int GetLength() const
    {
        return end.GetPosition() - start.GetPosition() - 1;
    }

    std::string CallName()
    {
        std::stringstream ss;
        ss << GetType() << fromClipPosition.GetReferenceName() << ":" << fromClipPosition.GetPosition() << "." << fromReadType;

        return ss.str();
    }

    virtual std::string GetType() = 0;

    virtual std::string ToBedpe() = 0;

protected:
    GenomePosition start;
    Interval startInterval;
    GenomePosition end;
    Interval endInterval;
    bool heterozygous;
    GenomePosition fromClipPosition;
    std::string fromReadType;

};

#endif // VARIANT_H
