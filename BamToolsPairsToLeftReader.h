#ifndef BAMTOOLSPAIRSTOLEFTREADER_H
#define BAMTOOLSPAIRSTOLEFTREADER_H

#include "spanningpairsreader.h"
#include "api/BamReader.h"

class BamToolsPairsToLeftReader : ISpanningPairsReader
{
public:
    BamToolsPairsToLeftReader(const GenomePosition &gPos, Library *pLib, BamTools::BamReader *pReader);
    SpanningPair *NextPair();

private:
    BamTools::BamReader *pReader;
};

#endif // BAMTOOLSPAIRSTOLEFTREADER_H
