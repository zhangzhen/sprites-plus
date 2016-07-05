#include "Deletion.h"

using namespace std;


string Deletion::ToBedpe()
{
    stringstream ss;
    ss << cRegionWithCi.GetReferenceName()
       << "\t" << cRegionWithCi.GetStartPosition() + cRegionWithCi.GetStartCi().GetStart() - 1
       << "\t" << cRegionWithCi.GetStartPosition() + cRegionWithCi.GetStartCi().GetEnd()
       << "\t" << cRegionWithCi.GetReferenceName()
       << "\t" << cRegionWithCi.GetEndPosition() + cRegionWithCi.GetEndCi().GetStart() - 1
       << "\t" << cRegionWithCi.GetEndPosition() + cRegionWithCi.GetEndCi().GetEnd()
       << "\t" << CallName()
       << "\t" << numOfReads;
    return ss.str();
}
