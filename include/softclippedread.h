#ifndef SOFTCLIPPEDREAD_H
#define SOFTCLIPPEDREAD_H

#include "ChromosomeRegion.h"
#include "AlignmentResult.h"
#include "ChromosomeRegionWithCi.h"

class ISoftClippedRead
{
public:
    ISoftClippedRead(const std::string &name,
                     const ChromosomeRegion& alignedRegion,
                     const std::string& sequence,
                     int mapQuality,
                     int clippedLength,
                     int smallDelSize,
                     int smallInsSize)
        : name(name),
          alignedRegion(alignedRegion),
          sequence(sequence),
          mapQuality(mapQuality),
          clippedLength(clippedLength),
          smallDelSize(smallDelSize),
          smallInsSize(smallInsSize)
    {}

    virtual ~ISoftClippedRead() {}
    int GetReferenceId() const { return alignedRegion.GetReferenceId(); }
    std::string GetReferenceName() const { return alignedRegion.GetReferenceName(); }
    std::string GetSequence() const { return sequence; }
//    int GetReadLength() const { return sequence.length(); }
    ChromosomeRegion GetAlignedRegion() const { return alignedRegion; }

    virtual GenomePosition GetClipPosition() = 0;

    virtual ChromosomeRegionWithCi ToRegionWithCi(int refStartPos, AlignmentResult alnResult) = 0;

    virtual std::string GetType() = 0;
    virtual std::string GetClippedPart() = 0;

protected:
    std::string name;
    ChromosomeRegion alignedRegion;
    std::string sequence;
    int mapQuality;
    int clippedLength;
    int smallDelSize;
    int smallInsSize;
};

#endif // SOFTCLIPPEDREAD_H
