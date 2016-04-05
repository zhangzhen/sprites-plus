#ifndef GENOMEPOSITION_H
#define GENOMEPOSITION_H

class GenomePosition
{
public:
    GenomePosition(int referenceId, int position);
    int GetReferenceId() const { return referenceId; }
    int GetPosition() const { return position; }

private:
    int referenceId;
    int position;
};

#endif // GENOMEPOSITION_H
