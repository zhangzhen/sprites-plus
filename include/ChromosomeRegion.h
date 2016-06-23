#ifndef CHROMOSOMEREGION_H
#define CHROMOSOMEREGION_H

#include "GenomePosition.h"
#include <iostream>

class ChromosomeRegion
{
public:
    ChromosomeRegion(int referenceId,
                     const std::string& referenceName,
                     int startPos,
                     int endPos);
    int GetReferenceId() const { return start.GetReferenceId(); }
    std::string GetReferenceName() const { return start.GetReferenceName(); }
    int GetStartPosition() const { return start.GetPosition(); }
    int GetEndPosition() const { return end.GetPosition(); }

    friend std::ostream &operator <<(std::ostream& stream, const ChromosomeRegion& cRegion);

private:
    GenomePosition start;
    GenomePosition end;
};

#endif // CHROMOSOMEREGION_H
