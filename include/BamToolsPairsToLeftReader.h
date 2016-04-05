#ifndef BAMTOOLSPAIRSTOLEFTREADER_H
#define BAMTOOLSPAIRSTOLEFTREADER_H

#include "spanningpairsreader.h"
#include "api/BamReader.h"

class BamToolsPairsToLeftReader : ISpanningPairsReader
{
public:
    BamToolsPairsToLeftReader(Library *pLib, BamTools::BamReader *pReader);
    void Init(const GenomePosition &gPos);
    SpanningPair *NextPair();

private:
    BamTools::BamReader *pReader;
};

#endif // BAMTOOLSPAIRSTOLEFTREADER_H
