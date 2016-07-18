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
             int numOfReads,
             const std::string& microHom,
             const std::string& microIns)
        : IVariant(cRegion,
                   startInterval,
                   endInterval,
                   heterozygous,
                   fromClipPosition,
                   fromReadType,
                   numOfReads,
                   microHom),
          microIns(microIns)
    {}

    std::string GetType() { return "DEL"; }

    std::string ToBedpe();

    std::string ToBed();

private:
    std::string microIns;
};


#endif // DELETION

