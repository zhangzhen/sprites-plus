#ifndef ALIGNMENTRESULT_H
#define ALIGNMENTRESULT_H

#include "Interval.h"

#include <string>

class AlignmentResult
{
public:
    AlignmentResult(const std::string& seq1,
                    const std::string& seq2,
                    const Interval& match1,
                    const Interval& match2,
                    int score,
                    const std::string& cigar)
        : seq1(seq1),
          seq2(seq2),
          match1(match1),
          match2(match2),
          score(score),
          cigar(cigar),
          alignmentLength(-1),
          editDistance(-1)
    {}

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

    Interval match1;
    Interval match2;

    int score;
    std::string cigar;
    int alignmentLength;
    int editDistance;

};

#endif // ALIGNMENTRESULT_H
