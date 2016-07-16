#ifndef VARIANT_H
#define VARIANT_H

#include "ChromosomeRegion.h"
#include "GenomePosition.h"
#include "Interval.h"

#include <string>
#include <sstream>

class IVariant
{
public:
    IVariant(const ChromosomeRegion& cRegion,
             const Interval& startInterval,
             const Interval& endInterval,
             bool heterozygous,
             const GenomePosition& fromClipPosition,
             const std::string& fromReadType,
             int numOfReads)
        : cRegion(cRegion),
          startInterval(startInterval),
          endInterval(endInterval),
          heterozygous(heterozygous),
          fromClipPosition(fromClipPosition),
          fromReadType(fromReadType),
          numOfReads(numOfReads)
    {}

    virtual ~IVariant() {}

    int GetLength() const
    {
        return cRegion.GetLength() - 2;
    }

    std::string CallName()
    {
        std::stringstream ss;
        ss << GetType() << "." << fromClipPosition.GetReferenceName() << ":" << fromClipPosition.GetPosition() << "." << fromReadType;

        return ss.str();
    }

    bool QuasiEquals(IVariant& other)
    {
        return GetType() == other.GetType() && cRegion == other.cRegion;
    }

    int GetNumOfReads() const { return numOfReads; }

    ChromosomeRegion GetChromoRegion() const { return cRegion; }

    virtual std::string GetType() = 0;

    virtual std::string ToBedpe() = 0;

    virtual std::string ToBed() = 0;

protected:
    ChromosomeRegion cRegion;
    Interval startInterval;
    Interval endInterval;
    bool heterozygous;
    GenomePosition fromClipPosition;
    std::string fromReadType;
    int numOfReads;

};

#endif // VARIANT_H
