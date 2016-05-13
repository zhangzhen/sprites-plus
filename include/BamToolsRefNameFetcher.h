#ifndef BAMTOOLSREFNAMEFETCHER_H
#define BAMTOOLSREFNAMEFETCHER_H

#include "referencenamefetcher.h"
#include "api/BamReader.h"

class BamToolsRefNameFetcher : public IReferenceNameFetcher
{
public:
    BamToolsRefNameFetcher(BamTools::BamReader *pBamReader);

    std::string Fetch(int referenceId);

private:
    BamTools::BamReader *pBamReader;
};

#endif // BAMTOOLSREFNAMEFETCHER_H
