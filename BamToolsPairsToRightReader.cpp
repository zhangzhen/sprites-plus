#include "BamToolsPairsToRightReader.h"
#include "api/BamAlignment.h"

BamToolsPairsToRightReader::BamToolsPairsToRightReader(const GenomePosition &gPos, Library *pLib, BamTools::BamReader *pReader)
    : ISpanningPairsReader(gPos, pLib),
      pReader(pReader)
{
    int start = gPos.GetPosition();
    int end = start + pLib->GetMaxInsertSize();

    assert(start < end);

    if (!pReader->SetRegion(gPos.GetReferenceId(), start - 1, gPos.GetReferenceId(), end))
    {
        error("Could not set the region.");
    }
}

SpanningPair* BamToolsPairsToRightReader::NextPair()
{
    BamAlignment al;
    while (pReader->GetNextAlignment(al))
    {
        std::string rg = al.HasTag("RG") ? al.GetTag("RG") : NORGTAGREADGROUPNAME;

        if (al.IsReverseStrand() && !al.IsMateReverseStrand() && al.RefID == al.MateRefID
                && al.Position >= gPos.GetPosition() && al.Position > al.MatePosition
                && pLib->InLibrary(rg))
        {
            return new SpanningPair(abs(al.InsertSize), al.MatePosition, al.Position, al.Length);
        }
    }

    return NULL;
}

