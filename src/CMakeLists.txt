find_package(HTSlib REQUIRED)
include_directories(${HTSLIB_INCLUDE_DIRS})
set(LIBRARIES ${LIBRARIES} ${HTSlib_LIBRARIES})

include_directories($ENV{BAMTOOLS_HOME}/include)
message("The include directory of BamTools is $ENV{BAMTOOLS_HOME}/include")
link_directories($ENV{BAMTOOLS_HOME}/lib)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
set(LIBRARIES ${LIBRARIES} ${Boost_LIBRARIES})

include_directories(../include)

set(SOURCES main.cpp Library.cpp PerChromDeletionCaller.cpp BamToolsRGToLibMapReader.cpp
BamToolsLibInsertSizeEstimator.cpp BamToolsSCReadsReader.cpp BamToolsPairsToLeftReader.cpp
BamToolsPairsToRightReader.cpp TargetRegionToLeftFinder.cpp TargetRegionToRightFinder.cpp
MaxDistDiffBiPartitioner.cpp AnovaBiPartitionQualifier.cpp MedianPositionPicker.cpp
DeletionCaller.cpp SpanningPair.cpp error.cpp LeafTargetRegionFinder.cpp
variantcaller.cpp GenomePosition.cpp TargetRegion.cpp ChromosomeRegion.cpp
FiveEndForwardSCRead.cpp FiveEndReverseSCRead.cpp)
#file(GLOB SOURCES "*.cpp")

add_executable(sprites2 ${SOURCES})
set(LIBRARIES ${LIBRARIES} ${HTSlib_LIBRARIES} $ENV{BAMTOOLS_HOME}/lib/libbamtools.a z)

target_link_libraries(sprites2 ${LIBRARIES})

set_target_properties(sprites2 PROPERTIES OUTPUT_NAME sprites2${BUILD_POSTFIX})
