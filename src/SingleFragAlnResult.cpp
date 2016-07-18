#include "SingleFragAlnResult.h"

#include <algorithm>


void SingleFragAlnResult::Flip()
{
    std::reverse(v.begin(), v.end());
    std::reverse(w.begin(), w.end());

    int l_v = v.length();
    int l_w = w.length();

    alnFrag.Flip(l_v, l_w);

}
