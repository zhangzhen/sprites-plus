#include "BamToolsPairsToRightReader.h"
#include "api/BamAlignment.h"

BamToolsPairsToRightReader::BamToolsPairsToRightReader(Library *pLib, BamTools::BamReader *pBamReader)
    : ISpanningPairsReader(pLib),
      pBamReader(pBamReader)
{
}

void BamToolsPairsToRightReader::Init(const GenomePosition &gPos)
{
    int start = gPos.GetPosition();
    int end = start + pLib->GetMaxInsertSize();

    assert(start < end);

    if (!pBamReader->SetRegion(gPos.GetReferenceId(), start - 1, gPos.GetReferenceId(), end))
    {
        error("Could not set the region.");
    }
}

SpanningPair* BamToolsPairsToRightReader::NextPair()
{
    BamAlignment al;
    while (pBamReader->GetNextAlignment(al))
    {
        std::string rg = al.HasTag("RG") ? al.GetTag("RG") : NORGTAGREADGROUPNAME;

        if (al.IsReverseStrand() && !al.IsMateReverseStrand() && al.RefID == al.MateRefID
                && al.Position >= gPos.GetPosition() && al.Position > al.MatePosition
                && pLib->InLibrary(rg))
        {
            return new SpanningPair(abs(al.InsertSize), al.MatePosition + 1, al.Position + 1, al.Length);
        }
    }

    return NULL;
}

