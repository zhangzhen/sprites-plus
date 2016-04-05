#include "BamToolsPairsToLeftReader.h"
#include "api/BamAlignment.h"

BamToolsPairsToLeftReader::BamToolsPairsToLeftReader(Library *pLib, BamTools::BamReader *pReader)
    : ISpanningPairsReader(pLib),
      pReader(pReader)
{
}

void BamToolsPairsToLeftReader::Init(const GenomePosition &gPos)
{
    int end = gPos.GetPosition();
    int start = end - pLib->GetMaxInsertSize();

    assert(start > 0);

    if (!pBamReader->SetRegion(gPos.GetReferenceId(), start - 1, gPos.GetReferenceId(), end))
    {
        error("Could not set the region.");
    }
}

SpanningPair *BamToolsPairsToLeftReader::NextPair()
{
    BamAlignment al;
    while (pBamReader->GetNextAlignment(al))
    {
        std::string rg = al.HasTag("RG") ? al.GetTag("RG") : NORGTAGREADGROUPNAME;

        if (!al.IsReverseStrand() && al.IsMateReverseStrand() && al.RefID == al.MateRefID
                && al.GetEndPosition() < gPos.GetPosition() && al.Position < al.MatePosition
                && pLib->InLibrary(rg))
        {
            return new SpanningPair(abs(al.InsertSize), al.MatePosition + 1, al.Position + 1, al.Length);
        }
    }

    return NULL;

}
