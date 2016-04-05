#ifndef CHROMOSOMEREGION_H
#define CHROMOSOMEREGION_H

#include "GenomePosition.h"

class ChromosomeRegion
{
public:
    ChromosomeRegion(int ReferenceId,
                     int startPos,
                     int endPos,
                     int numOfPairs,
                     bool heterozygous=false);
    int GetReferenceId() const { return start.GetReferenceId(); }
    int GetStartPosition() const { return start.GetPosition(); }
    int GetEndPosition() const { return end.GetPosition(); }
    int GetNumOfPairs() const { return numOfPairs; }
    int IsHeterozygous() const { return heterozygous; }

private:
    GenomePosition start;
    GenomePosition end;
    bool heterozygous;
    int numOfPairs;
};

#endif // CHROMOSOMEREGION_H
