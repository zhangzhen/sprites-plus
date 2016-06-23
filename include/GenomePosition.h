#ifndef GENOMEPOSITION_H
#define GENOMEPOSITION_H

#include <iostream>

class GenomePosition
{
public:
    GenomePosition(int referenceId, const std::string& referenceName, int position);
    GenomePosition() : GenomePosition(-1, "NA", 0) {}
    int GetReferenceId() const { return referenceId; }
    std::string GetReferenceName() const { return referenceName; }
    int GetPosition() const { return position; }
    bool operator == (const GenomePosition &other) const
    {
        return referenceId == other.referenceId &&
                referenceName == other.referenceName &&
                position == other.position;
    }

    friend std::ostream &operator <<(std::ostream& stream, const GenomePosition& gPos);

private:
    int referenceId;
    std::string referenceName;
    int position;
};

#endif // GENOMEPOSITION_H
