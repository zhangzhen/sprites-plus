#ifndef HTSLIBSEQUENCEFETCHER_H
#define HTSLIBSEQUENCEFETCHER_H

#include "sequencefetcher.h"
#include "htslib/faidx.h"

class HTSlibSequenceFetcher : ISequenceFetcher
{
public:
    HTSlibSequenceFetcher(faidx_t *faidx);
    std::string Fetch(const ChromosomeRegion& region);

private:
    faidx_t *faidx;
};

#endif // HTSLIBSEQUENCEFETCHER_H
