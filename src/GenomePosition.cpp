#include "GenomePosition.h"

using namespace std;

GenomePosition::GenomePosition(int referenceId, int position)
    : referenceId(referenceId),
      position(position)
{
}

ostream &operator <<(ostream &stream, const GenomePosition &gPos)
{
    stream << gPos.GetReferenceId()
           << "\t" << gPos.GetPosition();
    return stream;
}
