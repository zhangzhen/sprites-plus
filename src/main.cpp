#include "BamToolsRGToLibMapReader.h"
#include "BamToolsLibInsertSizeEstimator.h"
#include "BamToolsSCReadsReader.h"
#include "PerChromDeletionFinder.h"
#include "MaxDistDiffBiPartitioner.h"
#include "AnovaBiPartitionQualifier.h"
#include "MedianPositionPicker.h"
#include "CompositeTargetRegionFinder.h"
#include "TargetRegionToLeftFinder.h"
#include "TargetRegionToRightFinder.h"
#include "BamToolsPairsToLeftReader.h"
#include "BamToolsPairsToRightReader.h"
#include "globals.h"
#include "error.h"
#include "HTSlibSequenceFetcher.h"
#include "CustomSeqAligner.h"
#include "ReverseCustomSeqAligner.h"
#include "AGERealignWholeReadCaller.h"
#include "AGEAlignerAdapter.h"

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

void FindVariants(PerChromDeletionFinder &finder, const CallParams &cParams, std::ostream& out)
{
    std::vector<IVariant*> variants;
    finder.FindCalls(cParams, variants);
    auto finalVariants = finder.MergeCalls(variants);
    for (auto &pVariant : finalVariants)
    {
        // out << pVariant->ToBedpe() << std::endl;
        out << pVariant->ToBed() << std::endl;
    }
    finder.Clear();
}

void FindTargetRegions(PerChromDeletionFinder &finder, std::ostream& out)
{
    std::vector<TargetRegion *> regions;
    finder.FindTargetRegions(regions);
    for (auto &pRegion : regions)
    {
        out << *pRegion << std::endl;
    }
    finder.Clear();
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
        ("min-aligned,m", po::value<int>()->default_value(12), "Min aligned bases of re-aligning a soft-clipped read")
        ("mapping-qual", po::value<int>()->default_value(1), "Min mapping quality of a read")
        ("sig-clip,c", po::value<int>()->default_value(20), "Significant size of soft-clipped part")
        ("ignored-num,n", po::value<int>()->default_value(5), "Number of soft-clipped bases should not be considered")
        ("alpha-level,a", po::value<double>()->default_value(0.0005, "0.0005"), "Alpha level for Anova")
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

//    std::cout << *libraries.begin()->second << std::endl;

    ISequenceFetcher *pSeqFetcher = new HTSlibSequenceFetcher(vm["reffile"].as<std::string>());

    ISoftClippedReadsReader *pReadsReader = new BamToolsSCReadsReader(
                pBamReader,
                vm["sig-clip"].as<int>(),
                vm["ignored-num"].as<int>());

    int prevId = -1;
    int currentId;

    BamTools::BamReader *pBamReader2 = new BamTools::BamReader();
    if (!pBamReader2->Open(bamfile))
    {
        error("Could not open the input BAM file.");
    }
    if (!pBamReader2->LocateIndex())
    {
        error("Could not locate the index file");
    }

    CompositeTargetRegionFinder tRegionToLeftFinder;
    CompositeTargetRegionFinder tRegionToRightFinder;

    IBiPartitioner* pPartitioner = new MaxDistDiffBiPartitioner();
    IBiPartitionQualifier* pQualifier = new AnovaBiPartitionQualifier(vm["alpha-level"].as<double>());
    IPositionPicker* pPosPicker = new MedianPositionPicker();

    for (auto elt: libraries)
    {
        ISpanningPairsReader *pPairsToLeftReader = new BamToolsPairsToLeftReader(elt.second, pBamReader2);
        tRegionToLeftFinder.Add(new TargetRegionToLeftFinder(pPairsToLeftReader,
                                                             pPartitioner,
                                                             pQualifier,
                                                             pPosPicker));
        ISpanningPairsReader *pPairsToRightReader = new BamToolsPairsToRightReader(elt.second, pBamReader2);
        tRegionToRightFinder.Add(new TargetRegionToRightFinder(pPairsToRightReader,
                                                               pPartitioner,
                                                               pQualifier,
                                                               pPosPicker));
    }

    IRealignmentCaller *pPrefixCaller = new AGERealignWholeReadCaller(new AGEAlignerAdapter(), pSeqFetcher);
//    IReadRealigner *pPrefixRealigner = new WholeReadRealigner(new ReverseCustomSeqAligner(new CustomSeqAligner()));

    IRealignmentCaller *pSuffixCaller = pPrefixCaller;
//    IReadRealigner *pSuffixRealigner = new WholeReadRealigner(new CustomSeqAligner());

    CallParams cParams(vm["min-aligned"].as<int>(), vm["error-rate"].as<double>());


    ISoftClippedRead *pRead;
    PerChromDeletionFinder finder(&tRegionToLeftFinder, &tRegionToRightFinder, pSeqFetcher, pPrefixCaller, pSuffixCaller);

    pReadsReader->Init();

    while ((pRead = pReadsReader->NextRead()))
    {
        currentId = pRead->GetReferenceId();
//        std::cout << currentId << std::endl;
        if (prevId != -1 && prevId != currentId)
        {
//            FindTargetRegions(finder, std::cout);
            FindVariants(finder, cParams, std::cout);
        }

        finder.AddRead(pRead);
        prevId = currentId;
    }
//    FindTargetRegions(finder, std::cout);
    FindVariants(finder, cParams, std::cout);

    return 0;
}
