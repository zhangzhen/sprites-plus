#ifndef SOFTCLIPPEDREAD_H
#define SOFTCLIPPEDREAD_H

#include "GenomePosition.h"

class ISoftClippedRead
{
public:
    ISoftClippedRead(const std::string &name,
                     int referenceId,
                     int clipPosition,
                     const std::string &sequence,
                     int mapQuality)
        : name(name),
          clipPosition(referenceId, clipPosition),
          sequence(sequence),
          mapQuality(mapQuality)
    {}

    virtual ~ISoftClippedRead() {}
    GenomePosition GetClipPosition() const { return clipPosition; }
    virtual IVariant* FindCall() = 0;
    virtual std::string GetType() = 0;

private:
    std::string name;
    GenomePosition clipPosition;
    std::string sequence;
    int mapQuality;
};

#endif // SOFTCLIPPEDREAD_H
