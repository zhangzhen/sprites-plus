#include "PerChromDeletionFinder.h"
#include <iterator>
#include <algorithm>

using namespace std;

PerChromDeletionFinder::PerChromDeletionFinder(ITargetRegionFinder *pRegionToLeftFinder,
//                                                 ITargetRegionFinder *pRegionToRightFinder)
                                               ITargetRegionFinder *pRegionToRightFinder,
                                               ISequenceFetcher *pSeqFetcher,
                                               IRealignmentCaller *pPrefixCaller,
                                               IRealignmentCaller *pSuffixCaller)
    : pRegionToLeftFinder(pRegionToLeftFinder),
//      pRegionToRightFinder(pRegionToRightFinder)
      pRegionToRightFinder(pRegionToRightFinder),
      pSeqFetcher(pSeqFetcher),
      pPrefixCaller(pPrefixCaller),
      pSuffixCaller(pSuffixCaller)
{
}

void PerChromDeletionFinder::AddRead(ISoftClippedRead *pRead)
{
    int pos = pRead->GetClipPosition().GetPosition();
    if (finderMap.count(pos))
    {
        if (pRead->GetType() == finderMap[pos]->GetReadType())
        {
            finderMap[pos]->AddRead(pRead);
        }
        else
        {
            conflictSet.insert(pos);
        }
    }
    else
    {
        if (pRead->GetType() == "5F")
        {
            finderMap[pos] = new DeletionFinder(pRead, pRegionToRightFinder, pPrefixCaller);
//            callerMap[pos] = new DeletionCaller(pRead, pRegionToRightFinder);
        }
        else if (pRead->GetType() == "5R")
        {
            finderMap[pos] = new DeletionFinder(pRead, pRegionToLeftFinder, pSuffixCaller);
//            callerMap[pos] = new DeletionCaller(pRead, pRegionToLeftFinder);
        }
    }
}

void PerChromDeletionFinder::Clear()
{
    finderMap.clear();
    conflictSet.clear();
}

void PerChromDeletionFinder::FindTargetRegions(std::vector<TargetRegion *> &regions)
{
    TargetRegion *pReg;
//    copy(begin(conflictSet), end(conflictSet), ostream_iterator<int>(cout, " "));
//    cout << callerMap.size() << endl;

    for (auto &elt : finderMap)
    {
        if (conflictSet.count(elt.first))
        {
            continue;
        }
        if((pReg = elt.second->FindTargetRegion()))
        {
            regions.push_back(pReg);
        }
    }
}

void PerChromDeletionFinder::FindCalls(const CallParams &cParams, std::vector<IVariant *> &variants)
{
    IVariant *pVariant;
    for (auto &elt : finderMap)
    {
        if (conflictSet.count(elt.first))
        {
            continue;
        }
        if((pVariant = elt.second->FindVariant(cParams)))
        {
            variants.push_back(pVariant);
        }
    }

}

std::vector<IVariant *> PerChromDeletionFinder::MergeCalls(const std::vector<IVariant *> &variants)
{
    vector<IVariant*> result;

    if (variants.empty()) return result;

    size_t current = 0;
    result.push_back(variants[current]);
    int s = variants[current]->GetNumOfReads();

    for (size_t i = 1; i < variants.size(); ++i)
    {
        if (variants[current]->QuasiEquals(*variants[i]))
        {
            s += variants[i]->GetNumOfReads();
        }
        else
        {
            current = i;
            result.push_back(variants[current]);
            s = variants[current]->GetNumOfReads();
        }
    }

    return result;
}

void PerChromDeletionFinder::DetermineMicroHom(std::vector<IVariant *> &variants)
{
    const int WINDOW_SIZE = 50;

    for (auto pVar: variants)
    {
        ChromosomeRegion cRegion = pVar->GetChromoRegion();
        int s0 = cRegion.GetStartPosition();
        int e0 = cRegion.GetEndPosition();
        std::string v = pSeqFetcher->Fetch(ChromosomeRegion(cRegion.GetReferenceId(), cRegion.GetReferenceName(), s0 + 1, s0 + WINDOW_SIZE)).GetSequence();
        std::string w = pSeqFetcher->Fetch(ChromosomeRegion(cRegion.GetReferenceId(), cRegion.GetReferenceName(), e0, e0 + WINDOW_SIZE - 1)).GetSequence();
        int n_r = NumOfLongestCommonPrefix(v, w);
        std::string micro_hom_r =  v.substr(0, n_r);

        v = pSeqFetcher->Fetch(ChromosomeRegion(cRegion.GetReferenceId(), cRegion.GetReferenceName(), s0 + 1 - WINDOW_SIZE, s0)).GetSequence();
        w = pSeqFetcher->Fetch(ChromosomeRegion(cRegion.GetReferenceId(), cRegion.GetReferenceName(), e0 - WINDOW_SIZE, e0 - 1)).GetSequence();
        int n_l = NumOfLongestCommonSuffix(v, w);
        std::string micro_hom_l = v.substr(0, n_l);
    }
}


int NumOfLongestCommonPrefix(const std::string &v, const std::string &w)
{

    int n = std::min(v.length(), w.length());
    int i = 0;

    while (i < n && v[i] == w[i])
    {
        i++;
    }

    return i;
}

int NumOfLongestCommonSuffix(const std::string &v, const std::string &w)
{
    std::string v1;
    std::reverse_copy(v.begin(), v.end(), v1.begin());
    std::string w1;
    std::reverse_copy(w.begin(), w.end(), w1.begin());

    return NumOfLongestCommonPrefix(v, w);
}
