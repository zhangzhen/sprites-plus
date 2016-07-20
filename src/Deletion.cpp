#include "Deletion.h"
#include "globals.h"

using namespace std;


string Deletion::ToBedpe()
{
    stringstream ss;
    ss << cRegion.GetReferenceName()
       << "\t" << cRegion.GetStartPosition() + startInterval.GetStart() - 1
       << "\t" << cRegion.GetStartPosition() + startInterval.GetEnd()
       << "\t" << cRegion.GetReferenceName()
       << "\t" << cRegion.GetEndPosition() + endInterval.GetStart() - 1
       << "\t" << cRegion.GetEndPosition() + endInterval.GetEnd()
       << "\t" << CallName()
       << "\t" << numOfReads;
    return ss.str();
}

string Deletion::ToBed()
{
    stringstream ss;
    string alternatives = otherPositions.size() ?
             join(otherPositions.begin(), otherPositions.end(), ";") : "NA";
    ss << cRegion.GetReferenceName()
       << "\t" << cRegion.GetStartPosition()
       << "\t" << cRegion.GetEndPosition()
       << "\t" << CallName()
       << "\t" << numOfReads
       << "\t" << alternatives;
    return ss.str();
}
