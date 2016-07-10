#ifndef BAMTOOLSSCREADSREADER_H
#define BAMTOOLSSCREADSREADER_H

#include "softclippedreadsreader.h"
#include "api/BamReader.h"
#include "sequencefetcher.h"

class BamToolsSCReadsReader : public ISoftClippedReadsReader
{
public:
    BamToolsSCReadsReader(BamTools::BamReader *pBamReader,
                          int sigClipSize,
                          int ignoredNum,
                          ISequenceFetcher *pSeqFetcher);

    ISoftClippedRead *NextRead();

private:
    BamTools::BamReader *pBamReader;
    int sigClipSize;
    int ignoredNum;
    ISequenceFetcher *pSeqFetcher;
};

#endif // BAMTOOLSSCREADSREADER_H
