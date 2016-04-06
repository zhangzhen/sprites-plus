#include "ChromosomeRegion.h"

ChromosomeRegion::ChromosomeRegion(int referenceId,
                                   int startPos,
                                   int endPos)
    : start(GenomePosition(referenceId, startPos)),
      end(GenomePosition(referenceId, endPos))
{
}
