#ifndef SOFTCLIPPPEDREADCLUSTER_H
#define SOFTCLIPPPEDREADCLUSTER_H

#include "clip.h"
#include <vector>

class SoftClippedReadCluster
{
public:
    SoftClippedReadCluster(AbstractClip *read);
    void add(AbstractClip *read);
    Deletion call(BamTools::BamReader& reader, FaidxWrapper &faidx, int insLength, int minOverlap, double minIdentity, int minMapQual);

private:
    std::vector<AbstractClip *> reads;
};

#endif // SOFTCLIPPPEDREADCLUSTER_H
