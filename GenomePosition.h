#ifndef GENOMEPOSITION_H
#define GENOMEPOSITION_H

#include "Reference.h"

class GenomePosition
{
public:
    GenomePosition(int referenceId, const std::string& referenceName, int position);
    int GetReferenceId() const { return reference.GetId(); }
    std::string GetReferenceName() const { return reference.GetName(); }
    int GetPosition() const { return position; }

private:
    Reference reference;
    int position;
};

#endif // GENOMEPOSITION_H
