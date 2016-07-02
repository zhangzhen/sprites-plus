#ifndef CHROMOSOMEREGIONWITHCI
#define CHROMOSOMEREGIONWITHCI

#include "GenomePosition.h"
#include "Interval.h"

class ChromosomeRegionWithCi
{
public:
    ChromosomeRegionWithCi(const GenomePosition& start,
                           const Interval& startInterval,
                           const GenomePosition& end,
                           const Interval& endInterval)
        : start(start),
          startInterval(startInterval),
          end(end),
          endInterval(endInterval)
    {}

    int GetReferenceId() const { return start.GetReferenceId(); }
    std::string GetReferenceName() const { return start.GetReferenceName(); }
    int GetStartPosition() const { return start.GetPosition(); }
    int GetEndPosition() const { return end.GetPosition(); }

    Interval GetStartInterval() const { return startInterval; }
    Interval GetEndInterval() const { return endInterval; }
    int GetLength() const { return end.GetPosition() - start.GetPosition() + 1; }

private:
    GenomePosition start;
    Interval startInterval;
    GenomePosition end;
    Interval endInterval;
};

#endif // CHROMOSOMEREGIONWITHCI

