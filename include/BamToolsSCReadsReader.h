#ifndef BAMTOOLSSCREADSREADER_H
#define BAMTOOLSSCREADSREADER_H

#include "softclippedreadsreader.h"
#include "api/BamReader.h"

class BamToolsSCReadsReader : public ISoftClippedReadsReader
{
public:
    BamToolsSCReadsReader(BamTools::BamReader *pBamReader, int sigClipSize, int ignoredNum);

    ISoftClippedRead *NextRead();

private:
    BamTools::BamReader *pBamReader;
    int sigClipSize;
    int ignoredNum;
};

#endif // BAMTOOLSSCREADSREADER_H
