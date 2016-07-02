#include "Deletion.h"

using namespace std;


string Deletion::ToBedpe()
{
    stringstream ss;
    ss << cRegionWithCi.GetReferenceName()
       << "\t" << cRegionWithCi.GetStartPosition() + cRegionWithCi.GetStartInterval().GetStart() - 1
       << "\t" << cRegionWithCi.GetStartPosition() + cRegionWithCi.GetStartInterval().GetEnd()
       << "\t" << cRegionWithCi.GetReferenceName()
       << "\t" << cRegionWithCi.GetEndPosition() + cRegionWithCi.GetEndInterval().GetStart() - 1
       << "\t" << cRegionWithCi.GetEndPosition() + cRegionWithCi.GetEndInterval().GetEnd()
       << "\t" << CallName()
       << "\t" << numOfReads;
    return ss.str();
}
