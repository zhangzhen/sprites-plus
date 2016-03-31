#ifndef BAMTOOLSSCREADSREADER_H
#define BAMTOOLSSCREADSREADER_H

#include "softclippedreadsreader.h"
#include "api/BamReader.h"

class BamToolsSCReadsReader : ISoftClippedReadsReader
{
public:
    BamToolsSCReadsReader(BamTools::BamReader *pBamReader);

    ISoftClippedRead *NextRead();

private:
    BamTools::BamReader *pBamReader;
};

#endif // BAMTOOLSSCREADSREADER_H
