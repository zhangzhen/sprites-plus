#ifndef BAMTOOLSPAIRSTORIGHTREADER_H
#define BAMTOOLSPAIRSTORIGHTREADER_H

#include "spanningpairsreader.h"
#include "api/BamReader.h"

class BamToolsPairsToRightReader : public ISpanningPairsReader
{
public:
    BamToolsPairsToRightReader(const GenomePosition &gPos, Library *pLib, BamTools::BamReader *pReader);
    SpanningPair *NextPair();

private:
    BamTools::BamReader *pReader;
};

#endif // BAMTOOLSPAIRSTORIGHTREADER_H
