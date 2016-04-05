#include "ChromosomeRegion.h"

ChromosomeRegion::ChromosomeRegion(int referenceId,
                                   int startPos,
                                   int endPos,
                                   int numOfPairs,
                                   bool heterozygous)
    : start(GenomePosition(referenceId, startPos)),
      end(GenomePosition(referenceId, endPos)),
      numOfPairs(numOfPairs),
      heterozygous(heterozygous)
{
}
