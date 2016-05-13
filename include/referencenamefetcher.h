#ifndef REFERENCENAMEFETCHER_H
#define REFERENCENAMEFETCHER_H

#include <string>

class IReferenceNameFetcher
{
public:
    virtual std::string Fetch(int referenceId) = 0;
};

#endif // REFERENCENAMEFETCHER_H
