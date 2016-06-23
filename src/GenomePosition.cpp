#include "GenomePosition.h"

using namespace std;

GenomePosition::GenomePosition(int referenceId, const string &referenceName, int position)
    : referenceId(referenceId),
      referenceName(referenceName),
      position(position)
{
}

ostream &operator <<(ostream &stream, const GenomePosition &gPos)
{
    stream << gPos.referenceName
           << "\t" << gPos.position;
    return stream;
}
