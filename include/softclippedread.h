#ifndef SOFTCLIPPEDREAD_H
#define SOFTCLIPPEDREAD_H

#include "AlignmentResult.h"
#include "ChromosomeRegionWithCi.h"
#include "ChromoFragment.h"
#include "CallParams.h"


class ISoftClippedRead
{
public:
    ISoftClippedRead(const std::string &name,
                     const ChromosomeRegion& alignedRegion,
                     const std::string& sequence,
                     const std::string& refSeqPart,
                     int mapQuality,
                     int clippedLength,
                     int smallDelSize,
                     int smallInsSize)
        : name(name),
          alignedRegion(alignedRegion),
          sequence(sequence),
          refSeqPart(refSeqPart),
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

    virtual bool IsQualified(const AlignmentResult& aResult, const CallParams& cParams) = 0;

    virtual ChromosomeRegionWithCi ToRegionWithCi(const AlignmentResult& aResult, int refStartPos) = 0;

    virtual ChromoFragment CutFragment(const ChromoFragment& cFragment) = 0;

    virtual ChromoFragment ExtendFragment(const ChromoFragment& cFragment) = 0;

    virtual std::string GetType() = 0;
    virtual std::string GetClippedPart() = 0;

protected:
    std::string name;
    ChromosomeRegion alignedRegion;
    std::string sequence;
    std::string refSeqPart;
    int mapQuality;
    int clippedLength;
    int smallDelSize;
    int smallInsSize;
};

#endif // SOFTCLIPPEDREAD_H
