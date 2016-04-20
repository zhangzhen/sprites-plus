#include "CppUTest/TestHarness.h"
#include "MaxDistDiffBiPartitioner.h"

using namespace std;

TEST_GROUP(MaxDistDiffBiPartitioner)
{
    IBiPartitioner *pPartitioner;

    void setup()
    {
        pPartitioner = new MaxDistDiffBiPartitioner();
    }
    void teardown()
    {
        delete pPartitioner;
    }
};

TEST(MaxDistDiffBiPartitioner, Partition)
{
    vector<int> insertSizes = {
        532, 570, 470, 486, 563,
        571, 383, 463, 2462, 551,
        502, 484, 448, 586, 603,
        457, 568, 512, 402, 495
    };
    vector<int> expected = {
        0, 0, 0, 0, 0,
        0, 0, 0, 1, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0
    };

    auto actual = pPartitioner->Partition(insertSizes);
    CHECK_TRUE(expected == actual);
}

TEST(MaxDistDiffBiPartitioner, Partition2)
{
    vector<int> insertSizes = {
        387, 555, 550, 517, 506,
        449, 490, 511, 487, 392
    };
    vector<int> expected = {
        0, 1, 1, 1, 1,
        1, 1, 1, 1, 0
    };

    auto actual = pPartitioner->Partition(insertSizes);
    CHECK_TRUE(expected == actual);
}
