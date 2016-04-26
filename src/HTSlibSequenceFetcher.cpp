#include "HTSlibSequenceFetcher.h"
#include "error.h"

HTSlibSequenceFetcher::HTSlibSequenceFetcher(faidx_t *faidx)
    : faidx(faidx)
{
}

std::string HTSlibSequenceFetcher::Fetch(const ChromosomeRegion &region)
{
    int len;
    char *s = faidx_fetch_seq(
                faidx,
                (char *)region.GetReferenceName().c_str(),
                region.GetStartPosition() - 1,
                region.GetEndPosition() - 1,
                &len);
    if (s == NULL) error("cannot fetch the reference sequence");
    string str(s);
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}
