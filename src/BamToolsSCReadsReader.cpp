#include "BamToolsSCReadsReader.h"
#include "api/BamAlignment.h"
#include "FiveEndForwardSCRead.h"
#include "FiveEndReverseSCRead.h"

using namespace std;
using namespace BamTools;

BamToolsSCReadsReader::BamToolsSCReadsReader(BamTools::BamReader *pBamReader,
                                             int sigClipSize,
                                             int ignoredNum,
                                             ISequenceFetcher *pSeqFetcher)
    : pBamReader(pBamReader),
      sigClipSize(sigClipSize),
      ignoredNum(ignoredNum),
      pSeqFetcher(pSeqFetcher)
{
}


ISoftClippedRead *BamToolsSCReadsReader::NextRead()
{
    BamAlignment al;
    while (pBamReader->GetNextAlignment(al)) {
        vector<int> clipSizes, readPositions, genomePositions;
        if (!al.GetSoftClips(clipSizes, readPositions, genomePositions)) continue;
//        if (al.MapQuality < minMapQual || !al.GetSoftClips(clipSizes, readPositions, genomePositions)) continue;
        int size = clipSizes.size();

        if (al.IsProperPair())
        {
            int smallDelSize = 0;
            int smallInsSize = 0;

            for (auto &ci: al.CigarData)
            {
                if (ci.Type == 'D') smallDelSize += ci.Length;
                else if (ci.Type == 'I') smallInsSize += ci.Length;
            }

            if (!al.IsReverseStrand() && al.Position == genomePositions[0] &&
                    clipSizes[0] >= sigClipSize &&
                    (size == 1 ||
                     (size == 2 && clipSizes[1] <= ignoredNum)))
            {
//                if (genomePositions[0] + 1 == 37130093)
//                {
//                    cout << "debug here..." << endl;
//                }
                ChromosomeRegion cRegion(al.RefID,
                                         pBamReader->GetReferenceData()[al.RefID].RefName,
                        genomePositions[0] + 1,
                        al.GetEndPosition());
                return new FiveEndForwardSCRead(al.Name,
                                                cRegion,
                                                al.QueryBases,
                                                pSeqFetcher->Fetch(cRegion).GetSequence(),
                                                al.MapQuality,
                                                al.CigarData[0].Length,
                                                smallDelSize,
                                                smallInsSize);
            }
            if (al.IsReverseStrand() && al.Position != genomePositions[size - 1] &&
                    clipSizes[size - 1] >= sigClipSize &&
                    (size == 1 ||
                     (size == 2 && clipSizes[0] <= ignoredNum)))
            {
//                if (genomePositions[0] + 1 == 37130093)
//                {
//                    cout << "debug here..." << endl;
//                }

                ChromosomeRegion cRegion(al.RefID,pBamReader->GetReferenceData()[al.RefID].RefName,
                        al.Position + 1,
                        genomePositions[size - 1]);
                return new FiveEndReverseSCRead(al.Name,
                                                cRegion,
                                                al.QueryBases,
                                                pSeqFetcher->Fetch(cRegion).GetSequence(),
                                                al.MapQuality,
                                                al.CigarData[al.CigarData.size() - 1].Length,
                                                smallDelSize,
                                                smallInsSize);
            }
        }
    }

    return NULL;
}
