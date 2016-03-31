#ifndef BAMTOOLSRGTOLIBMAPREADER_H
#define BAMTOOLSRGTOLIBMAPREADER_H

#include "readgrouptolibrarymapreader.h"
#include "api/BamReader.h"

class BamToolsRGToLIbMapReader : public IReadGroupToLibraryMapReader
{
public:
    BamToolsRGToLIbMapReader(BamTools::BamReader *pBamReader);

    bool GetMap(std::map<std::string, std::string> &readGroupToLibMap);

private:
    BamTools::BamReader *pBamReader;
};

#endif // BAMTOOLSRGTOLIBMAPREADER_H
