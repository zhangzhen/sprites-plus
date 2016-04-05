#ifndef BAMTOOLSLIBINSERTSIZEESTIMATOR_H
#define BAMTOOLSLIBINSERTSIZEESTIMATOR_H

#include "libraryinsertsizeestimator.h"
#include "api/BamReader.h"

class BamToolsLibInsertSizeEstimator : ILibraryInsertSizeEstimator
{
public:
    BamToolsLibInsertSizeEstimator(BamTools::BamReader *pBamReader);
    bool estimate(Library *pLib);

private:
    BamTools::BamReader *pBamReader;
};

#endif // BAMTOOLSLIBINSERTSIZEESTIMATOR_H
