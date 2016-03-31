#include "GenomePosition.h"

GenomePosition::GenomePosition(int referenceId, const std::string &referenceName, int position)
    : reference(referenceId, referenceName),
      position(position)
{
}
