#ifndef SPANNINGPAIRSREADER_H
#define SPANNINGPAIRSREADER_H

#include "GenomePosition.h"
#include "SpanningPair.h"
#include "Library.h"

class ISpanningPairsReader
{
public:
    ISpanningPairsReader(const GenomePosition &gPos, Library *pLib) : gPos(gPos), pLib(pLib) {}
    int GetMeanInsertSize() const { return pLib->GetMeanInsertSize(); }
    int GetMaxInsertSize() const { return pLib->GetMaxInsertSize(); }
    int GetReferenceId() const { return gPos.GetReferenceId(); }
    std::string GetReferenceName() const { return gPos.GetReferenceName(); }
    virtual ~ISpanningPairsReader() {}
    virtual SpanningPair *NextPair() = 0;

private:
    GenomePosition gPos;
    Library *pLib;
};

#endif // SPANNINGPAIRSREADER_H
