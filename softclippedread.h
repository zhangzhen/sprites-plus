#ifndef SOFTCLIPPEDREAD_H
#define SOFTCLIPPEDREAD_H

#include "GenomePosition.h"

class ISoftClippedRead
{
public:
    virtual ~ISoftClippedRead() {}
    GenomePosition GetClippingPosition() {}
    virtual IVariant* FindCall() = 0;
    virtual std::string GetType() = 0;
};

#endif // SOFTCLIPPEDREAD_H
