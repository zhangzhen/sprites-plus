#include "BamToolsLibInsertSizeEstimator.h"
#include "globals.h"
#include "statistics.h"

using namespace std;
using namespace BamTools;

BamToolsLibInsertSizeEstimator::BamToolsLibInsertSizeEstimator(BamTools::BamReader *pBamReader)
    : pBamReader(pBamReader)
{
}


bool BamToolsLibInsertSizeEstimator::estimate(Library *pLib)
{
    BamAlignment al;
    size_t cnt = 0;
    vector<int> insertSizes;

    while (pBamReader->GetNextAlignmentCore(al) && cnt < 10000)
    {
        string rg;
        if (!al.GetTag("RG", rg))
        {
            rg = NORGTAGREADGROUPNAME;
        }

        if (al.IsProperPair() && al.MatePosition > al.Position
            && pLib->InLibrary(rg) && al.InsertSize < 10000)
        {
            insertSizes.push_back(al.InsertSize);
            cnt++;
        }
    }

    double meanInsertSize = GetMean(begin(insertSizes), end(insertSizes));
    double insertSizeSd = GetStandardDeviation(begin(insertSizes), end(insertSizes));

    pLib->SetMeanInsertSize((int)round(meanInsertSize));
    pLib->SetInsertSizeSd((int)round(insertSizeSd));
}
