#ifndef CHROMOSOMEREGION_H
#define CHROMOSOMEREGION_H

#include "GenomePosition.h"

class ChromosomeRegion
{
public:
    ChromosomeRegion(int ReferenceId,
                     const std::string& referenceName,
                     int startPos,
                     int endPos,
                     int numOfPairs,
                     bool heterozygous=false);
    std::string GetReferenceName() const { return start.GetReferenceName(); }
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
