#include "Deletion.h"

using namespace std;


string Deletion::ToBedpe()
{
    stringstream ss;
    ss << start.GetReferenceName()
       << "\t" << start.GetPosition() + startInterval.GetStart()
       << "\t" << start.GetPosition() + startInterval.GetEnd()
       << "\t" << end.GetReferenceName()
       << "\t" << end.GetPosition() + endInterval.GetStart()
       << "\t" << end.GetPosition() + startInterval.GetEnd()
       << "\t" << CallName();
    return ss.str();
}
