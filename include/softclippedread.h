#ifndef SOFTCLIPPEDREAD_H
#define SOFTCLIPPEDREAD_H

#include "GenomePosition.h"
#include "variant.h"

class ISoftClippedRead
{
public:
    ISoftClippedRead(const std::string &name,
                     int referenceId,
                     int clipPosition,
                     const std::string &sequence,
                     int mapQuality,
                     int clippedLength,
                     int smallDelSize,
                     int smallInsSize)
        : name(name),
          clipPosition(referenceId, clipPosition),
          sequence(sequence),
          mapQuality(mapQuality),
          clippedLength(clippedLength),
          smallDelSize(smallDelSize),
          smallInsSize(smallInsSize)
    {}

    virtual ~ISoftClippedRead() {}
    GenomePosition GetClipPosition() const { return clipPosition; }
    int GetReferenceId() const { return clipPosition.GetReferenceId(); }
//    virtual IVariant* FindCall() = 0;
    virtual std::string GetType() = 0;

private:
    std::string name;
    GenomePosition clipPosition;
    std::string sequence;
    int mapQuality;
    int clippedLength;
    int smallDelSize;
    int smallInsSize;
};

#endif // SOFTCLIPPEDREAD_H
