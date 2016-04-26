#include "ChromosomeRegion.h"

using namespace std;

ChromosomeRegion::ChromosomeRegion(int referenceId,
                                   int startPos,
                                   int endPos)
    : start(GenomePosition(referenceId, startPos)),
      end(GenomePosition(referenceId, endPos))
{
}

ostream &operator <<(ostream &stream, const ChromosomeRegion &cRegion)
{
    stream << cRegion.GetReferenceId()
           << "\t" << cRegion.GetStartPosition()
           << "\t" << cRegion.GetEndPosition();
    return stream;
}
