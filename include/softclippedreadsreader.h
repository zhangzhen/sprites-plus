#ifndef SOFTCLIPPEDREADSREADER_H
#define SOFTCLIPPEDREADSREADER_H

#include "softclippedread.h"

class ISoftClippedReadsReader
{
public:
    virtual ISoftClippedRead* NextRead() = 0;
};

#endif // SOFTCLIPPEDREADSREADER_H
