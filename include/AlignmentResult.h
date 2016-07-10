#ifndef ALIGNMENTRESULT_H
#define ALIGNMENTRESULT_H

#include "AlignmentFragment.h"
#include "error.h"

#include <string>

class AlignmentResult
{
public:
    AlignmentResult(const std::string& seq1,
                    const std::string& seq2,
                    int score,
                    const AlignmentFragment& aFragment1,
                    const AlignmentFragment& aFragment2)
        : seq1(seq1),
          seq2(seq2),
          aFragment1(aFragment1),
          aFragment2(aFragment2),
          score(score),
          single(false)
    {}

    AlignmentResult(const std::string& seq1,
                    const std::string& seq2,
                    int score,
                    const AlignmentFragment& aFragment1)
        : seq1(seq1),
          seq2(seq2),
          aFragment1(aFragment1),
          score(score),
          single(true)
    {}

    std::string GetSeq1() const { return seq1; }
    std::string GetSeq2() const { return seq2; }

    double GetPercentageIdentity1()
    {
        return aFragment1.GetPercentageIdentity();
    }

    double GetPercentageIdentity2()
    {
        if (single) error("The second alignment fragment is not available");
        return aFragment2.GetPercentageIdentity();
    }

    AlignmentFragment GetAlignmentFragment1() const
    {
        return aFragment1;
    }

    AlignmentFragment GetAlignmentFragment2() const
    {
        if (single) error("The second alignment fragment is not available");
        return aFragment2;
    }

    int GetScore() const { return score; }

    bool HasSingleFragment() const { return single; }

    void Flip();

//    void ShiftMatch1(int val);

    void PrintAlignment() const;

    int NumOfHomToRight() const;

private:
    std::string seq1;
    std::string seq2;

    AlignmentFragment aFragment1;
    AlignmentFragment aFragment2;

    int score;

    bool single;

};

int NumOfLongestCommonPrefix(const std::string& v, const std::string& w);

int NumOfLongestCommonSuffix(const std::string& v, const std::string& w);


#endif // ALIGNMENTRESULT_H
