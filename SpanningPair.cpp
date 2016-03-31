#include "SpanningPair.h"

SpanningPair::SpanningPair(int insertSize,
                           int leftReadPosition,
                           int rightReadPosition,
                           int readLength)
    : insertSize(insertSize),
      leftReadPosition(leftReadPosition),
      rightReadPosition(rightReadPosition),
      readLength(readLength)
{
}
