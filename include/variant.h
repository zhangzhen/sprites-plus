#ifndef VARIANT_H
#define VARIANT_H

#include <string>

class IVariant
{
public:
    virtual std::string GetType() = 0;
};

#endif // VARIANT_H
