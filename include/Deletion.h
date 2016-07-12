#ifndef DELETION
#define DELETION

#include "variant.h"

class Deletion : public IVariant
{
public:
    Deletion(const ChromosomeRegion& cRegion,
             const Interval& startInterval,
             const Interval& endInterval,
             bool heterozygous,
             const GenomePosition& fromClipPosition,
             const std::string& fromReadType,
             int numOfReads)
        : IVariant(cRegion,
                   startInterval,
                   endInterval,
                   heterozygous,
                   fromClipPosition,
                   fromReadType,
                   numOfReads)
    {}

    std::string GetType() { return "DEL"; }

    std::string ToBedpe();

    std::string ToBed();

};


#endif // DELETION

