#ifndef ALIGNMENTRESULT_H
#define ALIGNMENTRESULT_H

#include "AlignmentFragment.h"

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
          score(score),
          aFragment1(aFragment2)
    {}

    void SetAFragment1(const AlignmentFragment& newFragment1) { aFragment1 = newFragment1; }

    void SetAFragment2(const AlignmentFragment& newFragment2) { aFragment2 = newFragment2; }

    double GetPercentageIdentity()
    {
        return (double)(GetAlignmentLength() - GetEditDistance()) * 100.0f / GetAlignmentLength();
    }

    int GetAlignmentLength();
    int GetEditDistance();

    bool IsQualified(int minClip, double maxErrorRate)
    {
        return NumOfAlignedBasesForS2() >= minClip && GetPercentageIdentity() >= 100*(1 - maxErrorRate);
    }

    int NumOfAlignedBasesForS2() const
    {
        return match2.Length();
    }

    int GetScore() const { return score; }

    std::string GetCigar() const { return cigar; }

    void SetSeq1(const std::string& s1) { seq1 = s1; }
    void SetSeq2(const std::string& s2) { seq2 = s2; }

    void FlipMatch1(int seqLength) { match1.Flip(seqLength); }
    void FlipMatch2(int seqLength) { match2.Flip(seqLength); }

    Interval GetMatch1() const { return match1; }
    Interval GetMatch2() const { return match2; }

private:
    std::string seq1;
    std::string seq2;

    AlignmentFragment aFragment1;
    AlignmentFragment aFragment2;

    int score;

};

#endif // ALIGNMENTRESULT_H
