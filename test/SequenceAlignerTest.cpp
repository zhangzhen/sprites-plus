#include "CppUTest/TestHarness.h"
#include "CustomSeqAligner.h"
#include "ReverseCustomSeqAligner.h"

#include <algorithm>

TEST_GROUP(SequenceAligner)
{
    std::string s1, s2, s1_rev, s2_rev;
    ISequenceAligner *pSeqAligner, *pSeqAligner2;

    void setup()
    {
        s1 = "GGGTTGGGGGTAAGGTCACAGATCCACAGGATCCCATGGCAGAAGAATTTTTCTTAGTACAGAACAAAATGAAAAGTCTCCCATGTCTACTTCTTTCTACACAGACACGGCAACCATCCG"
                "ATTTCTCAATCTTTTCCCCACCTTTCCCCCCTTTCTATTCCACAAAACCGCCATTGTCATCATGGCGCGTTCTCAATGAGCTGTTGGGTACACCTCCCAGACGGGGTGGTGGCTGGGCAG"
                "AGGGGCTCCTCACTTCCCAGTAGGGGCGGCCGGGCAGAGGCGCCCCTCACCTCCCGGACGGGGCGGCTGGCCGGGCGGGGGGCTGACCACCCCCACCTCCCTCCCGGACGGGGCGGCTGG"
                "CCGGGCGGGGGGCTGACCCCCCACCTCCCTCCCAGACAGGGCGGCTGGCCGGGCTGGGGGCTGACCCCCCCACCTCCCTCCCAGACGGGGCGGCTGGCCGGGTGGGGGGCTGACCACCCC"
                "CACCTCCCTCCCGGACGGGGCGGCTGGCCGGGCTGAGGGCTGACCCCCCACCTCCCTCCCGGACAGGGTAGCTGCCGGGCAGAGACACTCCTCACTTCCCAGACGGGGTGGTTGCCGGGC"
                "GGAGGGGCTCCTCACTTCTCAGGCGGGGCGGCTGCCGGGCGGAGGGGCT";

        s2 = "CAAGCATCTGTTTAACAAAGCACATCTTGCACCGCCATTAATCCATTTAACCCTGAGTGGACACAGAACATGTTTCAGAGAGCACCGGGTTGGGGGTAAGGTCACAGATACACAGGATC"
                "CCCCTCCCTCCCGGACGGGGCGGCTGGCCGG";

        reverse_copy(begin(s1), end(s1), back_inserter(s1_rev));
        reverse_copy(begin(s2), end(s2), back_inserter(s2_rev));

    }
    void teardown()
    {
        delete pSeqAligner;
    }
};

TEST(SequenceAligner, CustomSeqAlignerAlign)
{
    pSeqAligner = new CustomSeqAligner();
    ScoreParam sParam(2, -3, -10000);

    AlignmentResult actual = pSeqAligner->Align(s1, s2, sParam);

    CHECK_EQUAL(59, actual.GetScore());
    CHECK("32M" == actual.GetCigar());

    CHECK(Interval(118, 149) == actual.GetMatch2());


}

TEST(SequenceAligner, ReverseCustomSeqAlignerAlign)
{
    pSeqAligner2 = new ReverseCustomSeqAligner(new CustomSeqAligner());
    ScoreParam sParam(2, -3, -10000);

    AlignmentResult actual = pSeqAligner2->Align(s1_rev, s2_rev, sParam);

    CHECK(Interval(0, 31) == actual.GetMatch2());

}
