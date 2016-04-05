#include "SpanningPair.h"

SpanningPair::SpanningPair(int referenceId,
                           int insertSize,
                           int leftReadPosition,
                           int rightReadPosition,
                           int readLength)
    : referenceId(referenceId),
      insertSize(insertSize),
      leftReadPosition(leftReadPosition),
      rightReadPosition(rightReadPosition),
      readLength(readLength)
{
}
