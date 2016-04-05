#include "BamToolsLibInsertSizeEstimator.h"

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
        std::string rg = al.HasTag("RG") ? al.GetTag("RG") : NORGTAGREADGROUPNAME;

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
