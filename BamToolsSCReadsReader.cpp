#include "BamToolsSCReadsReader.h"

BamToolsSCReadsReader::BamToolsSCReadsReader(BamTools::BamReader *pBamReader)
    : pBamReader(pBamReader)
{
}


ISoftClippedRead *BamToolsSCReadsReader::NextRead()
{
}
