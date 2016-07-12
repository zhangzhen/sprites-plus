#ifndef CALLRESULT
#define CALLRESULT

#include "ChromosomeRegion.h"
#include "sequencefetcher.h"


class CallResult
{
public:
    CallResult(const ChromosomeRegion& cRegion, const std::string& microIns)
        : cRegion(cRegion),
          microIns(microIns)
    {}

    ChromosomeRegion GetChromoRegion() const
    {
        return cRegion;
    }

    std::string GetMicroIns() const { return microIns; }

    std::string GetMicroHom(ISequenceFetcher *pSeqFetcher) const;

private:
    ChromosomeRegion cRegion;
    std::string microIns;
};

#endif // CALLRESULT

