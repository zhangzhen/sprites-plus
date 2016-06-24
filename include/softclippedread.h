#ifndef SOFTCLIPPEDREAD_H
#define SOFTCLIPPEDREAD_H

#include "GenomePosition.h"
#include "variant.h"
#include "AlignmentResult.h"

class ISoftClippedRead
{
public:
    ISoftClippedRead(const std::string &name,
                     int referenceId,
                     const std::string& referenceName,
                     int clipPosition,
                     const std::string &sequence,
                     int mapQuality,
                     int clippedLength,
                     int smallDelSize,
                     int smallInsSize)
        : name(name),
          clipPosition(referenceId, referenceName, clipPosition),
          sequence(sequence),
          mapQuality(mapQuality),
          clippedLength(clippedLength),
          smallDelSize(smallDelSize),
          smallInsSize(smallInsSize)
    {}

    virtual ~ISoftClippedRead() {}
    GenomePosition GetClipPosition() const { return clipPosition; }
    int GetReferenceId() const { return clipPosition.GetReferenceId(); }
    std::string GetReferenceName() const { return clipPosition.GetReferenceName(); }
    std::string GetSequence() const { return sequence; }
    virtual IVariant* FindCall(int refStartPos, AlignmentResult alnResult) = 0;
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
