#include "AlignmentResult.h"
#include <sstream>

int AlignmentResult::GetAlignmentLength()
{
    if (alignmentLength != -1)
    {
        return alignmentLength;
    }

    alignmentLength = 0;

    std::stringstream cigarBuffer(cigar);
    int length = -1;
    char code;
    while(cigarBuffer >> length >> code)
    {
        assert(length > 0);
        alignmentLength += length;
    }

    return alignmentLength;

}

int AlignmentResult::GetEditDistance()
{
    if (editDistance != -1)
    {
        return editDistance;
    }

    // Recalculate the edit distance between the pair of strings, given this alignment
    editDistance = 0;

    // Process the matching region using the cigar operations
    size_t current1 = match1.GetStart();
    size_t current2 = match2.GetStart();

    std::stringstream cigarBuffer(cigar);
    int length = -1;
    char code;
    while(cigarBuffer >> length >> code)
    {
        assert(length > 0);
        if(code == 'M')
        {
            for(int i = 0; i < length; ++i)
            {
                if(seq1[current1 + i] != seq2[current2 + i])
                    editDistance++;
            }
            current1 += length;
            current2 += length;
        }
        else if(code == 'D')
        {
            editDistance += length;
            current1 += length;
        }
        else if(code == 'I')
        {
            editDistance += length;
            current2 += length;
        }
        length = -1;
    }

    return editDistance;
}
