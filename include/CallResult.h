#ifndef CALLRESULT
#define CALLRESULT

#include "ChromosomeRegion.h"
#include "sequencefetcher.h"


class CallResult
{
public:
    CallResult(const ChromosomeRegion& cRegion,
               const Interval& startInterval,
               const Interval& endInterval,
               const std::string& microIns,
               const std::string& microHom)
        : cRegion(cRegion),
          startInterval(startInterval),
          endInterval(endInterval),
          microIns(microIns),
          microHom(microHom)
    {}

    ChromosomeRegion GetChromoRegion() const
    {
        return cRegion;
    }

    std::string GetMicroIns() const { return microIns; }

    std::string GetMicroHom() const { return microHom; }

    friend std::ostream& operator <<(std::ostream& stream, const CallResult& cResult);

private:
    ChromosomeRegion cRegion;
    Interval startInterval;
    Interval endInterval;
    std::string microIns;
    std::string microHom;
};

#endif // CALLRESULT
