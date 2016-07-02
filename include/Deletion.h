#ifndef DELETION
#define DELETION

#include "variant.h"

class Deletion : public IVariant
{
public:
    Deletion(const ChromosomeRegionWithCi& cRegionWithCi,
             bool heterozygous,
             const GenomePosition& fromClipPosition,
             const std::string& fromReadType,
             int numOfReads)
        : IVariant(cRegionWithCi,
                   heterozygous,
                   fromClipPosition,
                   fromReadType,
                   numOfReads)
    {}

    std::string GetType() { return "DEL"; }

    std::string ToBedpe();

};


#endif // DELETION

