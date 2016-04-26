#ifndef SPANNINGPAIR_H
#define SPANNINGPAIR_H

#include <string>

class SpanningPair
{
public:
    SpanningPair(int referenceId,
                 int insertSize,
                 int leftReadPosition,
                 int rightReadPosition,
                 int readLength);
    int GetReferenceId() const { return referenceId; }
    int GetInsertSize() const { return insertSize; }
    int GetLeftReadPosition() const { return leftReadPosition; }
    int GetRightReadPosition() const { return rightReadPosition; }
    int GetReadLength() const { return readLength; }

private:
    int referenceId;
    int insertSize;
    int leftReadPosition;
    int rightReadPosition;
    int readLength;
};

#endif // SPANNINGPAIR_H
