#include "CppUTest/TestHarness.h"
#include "AnovaBiPartitionQualifier.h"

using namespace std;

TEST_GROUP(AnovaBiPartitionQualifier)
{
    IBiPartitionQualifier* pQualifier;

    void setup()
    {
        pQualifier = new AnovaBiPartitionQualifier(0.0005);
    }
    void teardown()
    {
        delete pQualifier;
    }
};

TEST(AnovaBiPartitionQualifier, IsQualified_Pos)
{
    vector<int> insertSizes = {
        532, 570, 470, 486, 563,
        571, 383, 463, 2462, 551,
        502, 484, 448, 586, 603,
        457, 568, 512, 402, 495
    };
    vector<int> labels = {
        0, 0, 0, 0, 0,
        0, 0, 0, 1, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0
    };
    CHECK(pQualifier->IsQualified(insertSizes, labels));
}

TEST(AnovaBiPartitionQualifier, IsQualified_Neg)
{
    vector<int> insertSizes = {
        387, 555, 550, 517, 506,
        449, 490, 511, 487, 392
    };
    vector<int> labels = {
        0, 1, 1, 1, 1,
        1, 1, 1, 1, 0
    };
    CHECK(!pQualifier->IsQualified(insertSizes, labels));
}

TEST(AnovaBiPartitionQualifier, IsQualified_Neg2)
{
    vector<int> insertSizes = {
        435, 388, 396, 353, 1385,
        1222
    };
    vector<int> labels = {
        0, 0, 0, 0, 1,
        1
    };
    CHECK(!pQualifier->IsQualified(insertSizes, labels));
}
