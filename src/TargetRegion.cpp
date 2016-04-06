#include "TargetRegion.h"

TargetRegion::TargetRegion(int referenceId,
                           int startPos,
                           int endPos,
                           int fromClipPosition,
                           int numOfPairs,
                           bool heterozygous)
    : cRegion(referenceId, startPos, endPos),
      fromClipPosition(fromClipPosition),
      numOfPairs(numOfPairs),
      heterozygous(heterozygous)
{
}
