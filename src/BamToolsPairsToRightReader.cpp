#include "BamToolsPairsToRightReader.h"
#include "api/BamAlignment.h"
#include "error.h"
#include "globals.h"

using namespace BamTools;
using namespace std;

BamToolsPairsToRightReader::BamToolsPairsToRightReader(Library *pLib, BamTools::BamReader *pBamReader)
    : ISpanningPairsReader(pLib),
      pBamReader(pBamReader)
{
}

void BamToolsPairsToRightReader::Init(const GenomePosition &newGPos)
{
    int start = newGPos.GetPosition();
    int end = start + pLib->GetMaxInsertSize();

    assert(start < end);

    if (!pBamReader->SetRegion(newGPos.GetReferenceId(), start - 1, newGPos.GetReferenceId(), end))
    {
        error("Could not set the region.");
    }

    ISpanningPairsReader::Init(newGPos);
}

SpanningPair* BamToolsPairsToRightReader::NextPair()
{
    BamAlignment al;
    while (pBamReader->GetNextAlignment(al))
    {
        string rg;
        if (!al.GetTag("RG", rg))
        {
            rg = NORGTAGREADGROUPNAME;
        }

        if (al.IsReverseStrand() && !al.IsMateReverseStrand() && al.RefID == al.MateRefID
                && al.Position >= gPos.GetPosition() && al.Position > al.MatePosition
                && pLib->InLibrary(rg))
        {
            return new SpanningPair(al.RefID, abs(al.InsertSize), al.MatePosition + 1, al.Position + 1, al.Length);
        }
    }

    return NULL;
}

