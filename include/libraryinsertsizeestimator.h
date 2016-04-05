#ifndef LIBRARYINSERTSIZEESTIMATOR_H
#define LIBRARYINSERTSIZEESTIMATOR_H

#include "Library.h"

class ILibraryInsertSizeEstimator
{
public:
    virtual bool estimate(Library* pLib) = 0;
};

#endif // LIBRARYINSERTSIZEESTIMATOR_H
