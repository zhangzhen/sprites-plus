#ifndef CHROMOSOMEREGIONWITHCI
#define CHROMOSOMEREGIONWITHCI

#include "ChromosomeRegion.h"
#include "Interval.h"

class ChromosomeRegionWithCi
{
public:
    ChromosomeRegionWithCi(int referenceId,
                           const std::string referenceName,
                           int startPos,
                           const Interval& startCi,
                           int endPos,
                           const Interval& endCi)
        : cRegion(referenceId, referenceName, startPos, endPos),
          startCi(startCi),
          endCi(endCi)
    {}

    int GetReferenceId() const { return cRegion.GetReferenceId(); }
    std::string GetReferenceName() const { return cRegion.GetReferenceName(); }
    int GetStartPosition() const { return cRegion.GetStartPosition(); }
    int GetEndPosition() const { return cRegion.GetEndPosition(); }

    Interval GetStartCi() const { return startCi; }
    Interval GetEndCi() const { return endCi; }

    int GetLength() const { return cRegion.GetLength(); }

    bool QuasiEquals(const ChromosomeRegionWithCi& other) const
    {
        return cRegion == other.cRegion;
    }

private:
    ChromosomeRegion cRegion;
    Interval startCi;
    Interval endCi;
};

#endif // CHROMOSOMEREGIONWITHCI

