#include "ChromosomeRegion.h"

using namespace std;

ChromosomeRegion::ChromosomeRegion(int referenceId,
                                   const string& referenceName,
                                   int startPos,
                                   int endPos)
    : start(GenomePosition(referenceId, referenceName, startPos)),
      end(GenomePosition(referenceId, referenceName, endPos))
{
}

ostream &operator <<(ostream &stream, const ChromosomeRegion &cRegion)
{
    stream << cRegion.GetReferenceName()
           << "\t" << cRegion.GetStartPosition()
           << "\t" << cRegion.GetEndPosition();
    return stream;
}
