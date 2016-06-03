#include "BamToolsRGToLibMapReader.h"
#include "BamToolsLibInsertSizeEstimator.h"
#include "BamToolsSCReadsReader.h"
#include "PerChromDeletionCaller.h"
#include "MaxDistDiffBiPartitioner.h"
#include "AnovaBiPartitionQualifier.h"
#include "MedianPositionPicker.h"
#include "TargetRegionToLeftFinder.h"
#include "TargetRegionToRightFinder.h"
#include "BamToolsPairsToLeftReader.h"
#include "BamToolsPairsToRightReader.h"
#include "BamToolsRefNameFetcher.h"
#include "globals.h"
#include "error.h"

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

namespace po = boost::program_options;

#include <string>

//using namespace std;

#define PROGRAM_NAME "sprites2"
#define PROGRAM_VERSION "2.0.1"
#define PROGRAM_BUGREPORT "zhangz@csu.edu.cn"

const std::string PROGRAM_VERSION_MESSAGE =
        PROGRAM_NAME " Version " PROGRAM_VERSION "\n"
        "Written by Zhen Zhang.\n"
        "Report bugs to " PROGRAM_BUGREPORT "\n"
        "Copyright 2016 netlab.csu.edu.cn\n";

void MakeLibraries(IReadGroupToLibraryMapReader *pMapReader, std::map<std::string, Library*> &libraries)
{
    std::map<std::string, std::string> readGroupToLibMap;
    if(pMapReader->GetMap(readGroupToLibMap))
    {
        for (auto &elt : readGroupToLibMap)
        {
            if (libraries.count(elt.second))
            {
                libraries[elt.second]->AddReadGroup(elt.first);
            }
            else
            {
                libraries[elt.second] = new Library(elt.second, elt.first);
            }
        }
        return;
    }

    libraries[NORGTAGLIBNAME] = new Library(NORGTAGLIBNAME, NORGTAGREADGROUPNAME);
}

void EstimateInsertSizeForLibrarys(ILibraryInsertSizeEstimator *pEstimator, std::map<std::string, Library*> &libraries)
{
    for (auto &p : libraries)
    {
        pEstimator->estimate(p.second);
    }
}

//void FindVariantCalls(PerChromDeletionCaller &caller, IVariantsWriter *pVarsWriter)
//{
//    std::vector<IVariant*> variants;
//    caller.Call(variants);
//    caller.Clear();
//    if (!variants.empty()) pVarsWriter->write(variants);
//}

void FindTargetRegions(PerChromDeletionCaller &caller, IReferenceNameFetcher *pRefNameFetcher)
{
    std::vector<TargetRegion *> regions;
    caller.FindTargetRegions(regions);
    for (auto &pRegion : regions)
    {
        std::cout << pRefNameFetcher->Fetch(pRegion->GetReferenceId())
             << "\t" << pRegion->GetStartPosition()
             << "\t" << pRegion->GetEndPosition()
             << "\t" << pRegion->GetFromClipPosition()
             << "\t" << pRegion->GetNumOfPairs()
             << "\t" << pRegion->IsHeterozygous()
             << std::endl;
    }
    caller.Clear();
}

int main(int argc, char *argv[])
{

    po::options_description desc("Allowed options");

    desc.add_options()
        ("help,h", "Display this help message")
        ("version,v", "Display the version number")
        ("reffile,r", po::value<std::string>()->required(), "Reference file (*)")
        ("outfile,o", po::value<std::string>()->required(), "Output file for deletion calls (*)")
        ("error-rate,e", po::value<double>()->default_value(0.04, "0.04"), "Max error rate")
        ("min-overlap,m", po::value<int>()->default_value(12), "Min overlap required between two reads")
        ("mapping-qual", po::value<int>()->default_value(1), "Min mapping quality of a read")
        ("allowed-num,n", po::value<int>()->default_value(5), "Min size of soft-clipped part")
        ("insert-mean,i", po::value<int>(), "Mean of insert size")
        ("insert-sd,s", po::value<int>(), "Standard deviation of insert size")
        ("bamfile", po::value<std::string>()->required(), "Input BAM file (*)");

    po::positional_options_description p;
    p.add("bamfile", -1);
    po::variables_map vm;

    try
    {
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);

        if(vm.count("help"))
        {
            std::cout << "Usage: sprites2 [options] <bamfile>" << std::endl;
            std::cout << desc;
            std::cout << "Note: options marked by an asterisk are required." << std::endl;
            return 0;
        }

        if(vm.count("version"))
        {
            std::cout << PROGRAM_VERSION_MESSAGE;
            return 0;
        }

        po::notify(vm);
    }
    catch(std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cout << "Usage: sprites2 [options] <bamfile>" << std::endl;
        std::cout << desc;
        std::cout << "Note: options marked by an asterisk are required." << std::endl;
        return 0;
    }
    catch(...)
    {
        std::cerr << "Unknown error!" << std::endl;
        return 0;
    }

    std::string bamfile;

    if (vm.count("bamfile"))
    {
        bamfile = vm["bamfile"].as<std::string>();
    }


    BamTools::BamReader *pBamReader = new BamTools::BamReader();
    if (!pBamReader->Open(bamfile))
    {
        error("Could not open the input BAM file.");
    }
    if (!pBamReader->LocateIndex())
    {
        error("Could not locate the index file");
    }

    IReadGroupToLibraryMapReader *pMapReader = new BamToolsRGToLibMapReader(pBamReader);
    std::map<std::string, Library*> libraries;
    MakeLibraries(pMapReader, libraries);
    ILibraryInsertSizeEstimator *pEstimator = new BamToolsLibInsertSizeEstimator(pBamReader);
    EstimateInsertSizeForLibrarys(pEstimator, libraries);

    ISoftClippedReadsReader *pReadsReader = new BamToolsSCReadsReader(pBamReader, 5, 20);

    int prevId = -1;
    int currentId;

    ISpanningPairsReader *pPairsToLeftReader;
    ISpanningPairsReader *pPairsToRightReader;

    if (libraries.size() == 1)
    {
        pPairsToLeftReader = new BamToolsPairsToLeftReader(libraries.begin()->second, pBamReader);
        pPairsToRightReader = new BamToolsPairsToRightReader(libraries.begin()->second, pBamReader);
    }
    IBiPartitioner* pPartitioner = new MaxDistDiffBiPartitioner();
    IBiPartitionQualifier* pQualifier = new AnovaBiPartitionQualifier(0.00001);
    IPositionPicker* pPosPicker = new MedianPositionPicker();
    ITargetRegionFinder *pRegionToLeftFinder = new TargetRegionToLeftFinder(pPairsToLeftReader,
                                                                            pPartitioner,
                                                                            pQualifier,
                                                                            pPosPicker);
    ITargetRegionFinder *pRegionToRightFinder = new TargetRegionToRightFinder(pPairsToRightReader,
                                                                            pPartitioner,
                                                                            pQualifier,
                                                                            pPosPicker);

    IReferenceNameFetcher *pRefNameFetcher = new BamToolsRefNameFetcher(pBamReader);

    ISoftClippedRead *pRead;
    PerChromDeletionCaller caller(pRegionToLeftFinder, pRegionToRightFinder);
    while ((pRead = pReadsReader->NextRead()))
    {
        currentId = pRead->GetReferenceId();
        if (prevId != -1 && prevId != currentId)
        {
            FindTargetRegions(caller, pRefNameFetcher);
//            FindVariantCalls(caller, pVarsWriter);
        }
        caller.AddRead(pRead);
        prevId = currentId;
    }
    FindTargetRegions(caller, pRefNameFetcher);
//    FindVariantCalls(caller,pVarsWriter);

    return 0;
}
