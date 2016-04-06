#ifndef CHROMOSOMEREGION_H
#define CHROMOSOMEREGION_H

#include "GenomePosition.h"

class ChromosomeRegion
{
public:
    ChromosomeRegion(int referenceId,
                     int startPos,
                     int endPos);
    int GetReferenceId() const { return start.GetReferenceId(); }
    int GetStartPosition() const { return start.GetPosition(); }
    int GetEndPosition() const { return end.GetPosition(); }

private:
    GenomePosition start;
    GenomePosition end;
};

#endif // CHROMOSOMEREGION_H
