#ifndef SEQUENCEFETCHER_H
#define SEQUENCEFETCHER_H

#include "ChromosomeRegion.h"

class ISequenceFetcher
{
public:
    virtual ~ISequenceFetcher() {}
    virtual std::string Fetch(const ChromosomeRegion& region) = 0;
};

#endif // SEQUENCEFETCHER_H
