#include "softclippedread.h"


bool IsQualified(int matchLen, int percentIdent, const CallParams &cParams)
{
    return matchLen >= cParams.GetMinClip() &&
            percentIdent >= (1 - cParams.GetMaxErrorRate()) * 100;
}
