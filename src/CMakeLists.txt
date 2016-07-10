find_package(HTSlib REQUIRED)
include_directories(${HTSLIB_INCLUDE_DIRS})
set(LIBRARIES ${LIBRARIES} ${HTSlib_LIBRARIES})

include_directories($ENV{BAMTOOLS_HOME}/include)
message("The include directory of BamTools is $ENV{BAMTOOLS_HOME}/include")
link_directories($ENV{BAMTOOLS_HOME}/lib)

set(BOOST_INCLUDEDIR "/usr/local/include/boost")
set(BOOST_LIBRARYDIR "/usr/loca/lib")
set(Boost_USE_STATIC_LIBS ON)

find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
set(LIBRARIES ${LIBRARIES} ${Boost_LIBRARIES})

include_directories(../include)

set(SOURCES main.cpp Library.cpp PerChromDeletionCaller.cpp BamToolsRGToLibMapReader.cpp
BamToolsLibInsertSizeEstimator.cpp BamToolsSCReadsReader.cpp BamToolsPairsToLeftReader.cpp
BamToolsPairsToRightReader.cpp TargetRegionToLeftFinder.cpp TargetRegionToRightFinder.cpp
MaxDistDiffBiPartitioner.cpp AnovaBiPartitionQualifier.cpp MedianPositionPicker.cpp
DeletionCaller.cpp SpanningPair.cpp error.cpp LeafTargetRegionFinder.cpp
variantcaller.cpp GenomePosition.cpp TargetRegion.cpp ChromosomeRegion.cpp
FiveEndForwardSCRead.cpp FiveEndReverseSCRead.cpp HTSlibSequenceFetcher.cpp
CustomSeqAligner.cpp AlignmentResult.cpp Deletion.cpp AlignmentFragment.cpp
Interval.cpp AGEAlignerAdapter.cpp age/AGEaligner.cpp)
#file(GLOB SOURCES "*.cpp")

add_executable(sprites2 ${SOURCES})
set(LIBRARIES ${LIBRARIES} ${HTSlib_LIBRARIES} $ENV{BAMTOOLS_HOME}/lib/libbamtools.a z)

target_link_libraries(sprites2 ${LIBRARIES})

set_target_properties(sprites2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set_target_properties(sprites2 PROPERTIES OUTPUT_NAME sprites2${BUILD_POSTFIX})
