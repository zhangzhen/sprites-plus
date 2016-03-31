#include "BamToolsPairsToLeftReader.h"

BamToolsPairsToLeftReader::BamToolsPairsToLeftReader(const GenomePosition &gPos, Library *pLib, BamTools::BamReader *pReader)
    : ISpanningPairsReader(gPos, pLib),
      pReader(pReader)
{
}

SpanningPair *BamToolsPairsToLeftReader::NextPair()
{

}
