#ifndef DELETION
#define DELETION

#include "variant.h"

class Deletion : public IVariant
{
public:
    Deletion(const GenomePosition& start,
             const Interval& startInterval,
             const GenomePosition& end,
             const Interval& endInterval,
             bool heterozygous,
             const GenomePosition& fromClipPosition,
             const std::string& fromReadType)
        : IVariant(start,
                   startInterval,
                   end,
                   endInterval,
                   heterozygous,
                   fromClipPosition,
                   fromReadType)
    {}

    std::string GetType() { return "DEL"; }

    std::string ToBedpe();

};


#endif // DELETION

