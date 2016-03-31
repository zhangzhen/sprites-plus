#include "BamToolsRGToLIbMapReader.h"
#include "Library.h"
#include "libraryinsertsizeestimator.h"

BamToolsRGToLIbMapReader::BamToolsRGToLIbMapReader(BamTools::BamReader pBamReader)
    : pBamReader(pBamReader)
{
}

const std::string NORGTAGLIBNAME = "NoRGTagLib";
const std::string NORGTAGREADGROUPNAME = "NoRGTagGroup";

bool BamToolsRGToLIbMapReader::GetMap(std::map<std::string, std::string> &readGroupToLibMap)
{
    BamTools::SamHeader header = pBamReader->GetHeader();
    if (!header.HasReadGroups())
    {
        return false;
    }

    for (auto it = header.ReadGroups.Begin(); it != header.ReadGroups.End(); ++it)
    {
        readGroupToLibMap[it->first] = it->second.Library;
    }
    return true;
}
