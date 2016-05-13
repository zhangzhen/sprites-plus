#include "BamToolsRefNameFetcher.h"

BamToolsRefNameFetcher::BamToolsRefNameFetcher(BamTools::BamReader *pBamReader)
    : pBamReader(pBamReader)
{

}

std::string BamToolsRefNameFetcher::Fetch(int referenceId)
{
    assert(referenceId >= 0 && referenceId < pBamReader->GetReferenceCount());
    return pBamReader->GetReferenceData()[referenceId].RefName;
}
