#ifndef GENOMEPOSITION_H
#define GENOMEPOSITION_H

#include <iostream>

class GenomePosition
{
public:
    GenomePosition(int referenceId, int position);
    GenomePosition() : GenomePosition(-1, 0) {}
    int GetReferenceId() const { return referenceId; }
    int GetPosition() const { return position; }
    bool operator == (const GenomePosition &other) const
    {
        return referenceId == other.referenceId && position == other.position;
    }

    friend std::ostream &operator <<(std::ostream& stream, const GenomePosition& gPos);

private:
    int referenceId;
    int position;
};

#endif // GENOMEPOSITION_H
