#include "ChromosomeRegion.h"

ChromosomeRegion::ChromosomeRegion(int referenceId,
                                   const std::string &referenceName,
                                   int startPos,
                                   int endPos,
                                   int numOfPairs,
                                   bool heterozygous)
    : start(GenomePosition(referenceId, referenceName, startPos)),
      end(GenomePosition(referenceId, referenceName, endPos)),
      numOfPairs(numOfPairs),
      heterozygous(heterozygous)
{
}
