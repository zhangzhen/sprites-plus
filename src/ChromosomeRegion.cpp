#include "ChromosomeRegion.h"

using namespace std;

ChromosomeRegion::ChromosomeRegion(int referenceId,
                                   const string& referenceName,
                                   int startPos,
                                   int endPos)
    : referenceId(referenceId),
      referenceName(referenceName),
      interval(startPos,endPos)
{
}

bool operator ==(const ChromosomeRegion &one, const ChromosomeRegion &two)
{
    return one.referenceId == two.referenceId && one.interval == two.interval;
}

ostream &operator <<(ostream &stream, const ChromosomeRegion &cRegion)
{
    stream << cRegion.referenceName
           << "\t" << cRegion.GetStartPosition()
           << "\t" << cRegion.GetEndPosition();
    return stream;
}
