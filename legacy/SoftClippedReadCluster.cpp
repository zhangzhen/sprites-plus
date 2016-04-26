#include "SoftClippedReadCluster.h"
#include <algorithm>

SoftClippedReadCluster::SoftClippedReadCluster(AbstractClip *read) : reads({read})
{
}

void SoftClippedReadCluster::add(AbstractClip *read)
{
    reads.push_back(read);
}

Deletion SoftClippedReadCluster::call(BamTools::BamReader &reader, FaidxWrapper &faidx, int insLength, int minOverlap, double minIdentity, int minMapQual)
{
    auto max_elt = *max_element(
        reads.begin(),
        reads.end(),
        [](AbstractClip *p1, AbstractClip *p2) {
            return p1->lengthOfSoftclippedPart() < p2->lengthOfSoftclippedPart();
        }
    );
    return max_elt->call(reader, faidx, insLength, minOverlap, minIdentity, minMapQual);
}
