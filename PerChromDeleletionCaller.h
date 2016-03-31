#ifndef PERCHROMDELELETIONCALLER_H
#define PERCHROMDELELETIONCALLER_H

#include "DeletionCaller.h"
#include "api/BamReader.h"

class PerChromDeleletionCaller
{
public:
    PerChromDeleletionCaller(ITargetRegionFinder *pRegionFinder,
                             ISequenceFetcher pSeqFetcher,
                             ISequenceAligner pSeqAligner);
    void AddRead(ISoftClippedRead *pRead);
    bool Call(std::vector<IVariant*> &variants);

private:
    std::map<int, IVariantCaller*> callerMap;
};

#endif // PERCHROMDELELETIONCALLER_H
