#ifndef VARIANT_H
#define VARIANT_H

#include "ChromosomeRegionWithCi.h"
#include "GenomePosition.h"
#include "Interval.h"

#include <string>
#include <sstream>

class IVariant
{
public:
    IVariant(const ChromosomeRegionWithCi& cRegionWithCi,
             bool heterozygous,
             const GenomePosition& fromClipPosition,
             const std::string& fromReadType,
             int numOfReads)
        : cRegionWithCi(cRegionWithCi),
          heterozygous(heterozygous),
          fromClipPosition(fromClipPosition),
          fromReadType(fromReadType),
          numOfReads(numOfReads)
    {}

    virtual ~IVariant() {}

    int GetLength() const
    {
        return cRegionWithCi.GetLength() - 2;
    }

    std::string CallName()
    {
        std::stringstream ss;
        ss << GetType() << "." << fromClipPosition.GetReferenceName() << ":" << fromClipPosition.GetPosition() << "." << fromReadType;

        return ss.str();
    }

    bool QuasiEquals(IVariant& other)
    {
        return GetType() == other.GetType() && cRegionWithCi.QuasiEquals(other.cRegionWithCi);
    }

    int GetNumOfReads() const { return numOfReads; }

    virtual std::string GetType() = 0;

    virtual std::string ToBedpe() = 0;

protected:
    ChromosomeRegionWithCi cRegionWithCi;
    bool heterozygous;
    GenomePosition fromClipPosition;
    std::string fromReadType;
    int numOfReads;

};

#endif // VARIANT_H
