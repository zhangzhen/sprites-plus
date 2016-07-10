#include "AlignmentResult.h"

#include <sstream>
#include <algorithm>


void AlignmentResult::Flip()
{
    std::reverse(seq1.begin(), seq1.end());
    std::reverse(seq2.begin(), seq2.end());

    aFragment1.Flip(seq1.length(), seq2.length());

    if (!single)
    {
        aFragment2.Flip(seq1.length(), seq2.length());
    }
}

//void AlignmentResult::ShiftMatch1(int val)
//{
//    aFragment1.ShiftMatch1(val);

//    if (!single)
//    {
//        aFragment2.ShiftMatch1(val);
//    }

//}

void AlignmentResult::PrintAlignment() const
{
    aFragment1.PrintAlignment();

    if (!single)
    {
        std::cout << "<EXCISED REGION>" << std::endl;
        aFragment2.PrintAlignment();
    }
}

int AlignmentResult::NumOfHomToRight() const
{
    if (single) return 0;

    int e1 = aFragment1.GetMatch1().GetEnd();
    int s2 = aFragment2.GetMatch1().GetStart();

    std::string v = seq1.substr(e1 + 1, s2 - e1);
    std::string w = seq1.substr(s2);

    return NumOfLongestCommonPrefix(v, w);
}


int NumOfLongestCommonPrefix(const std::string &v, const std::string &w)
{

    int n = std::min(v.length(), w.length());
    int i = 0;

    while (i < n && v[i] == w[i])
    {
        i++;
    }

    return i;
}

int NumOfLongestCommonSuffix(const std::__cxx11::string &v, const std::__cxx11::string &w)
{
    return 0;
}
