cmake_minimum_required(VERSION 2.8)

project(sprites2)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

find_package(HTSlib REQUIRED)
include_directories(${HTSLIB_INCLUDE_DIRS})
set(LIBRARIES ${LIBRARIES} ${HTSlib_LIBRARIES})

include_directories($ENV{BAMTOOLS_HOME}/include)
message("The include directory of BamTools is $ENV{BAMTOOLS_HOME}/include")
link_directories($ENV{BAMTOOLS_HOME}/lib)
add_definitions(-std=c++11)

include_directories(include)

#add_executable(sprites2 main.cpp error.cpp Helper.cpp Deletion.cpp Thirdparty/overlapper.cpp
#    BamStatCalculator.cpp ClipReader.cpp clip.cpp FaidxWrapper.cpp range.cpp SoftClippedReadCluster.cpp)
#target_link_libraries(sprites2 $ENV{HTSLIB_HOME}/libhts.a $ENV{BAMTOOLS_HOME}/lib/libbamtools.a pthread z)

set(SOURCES src/main.cpp src/Library.cpp src/PerChromDeletionCaller.cpp src/BamToolsRGToLibMapReader.cpp
src/BamToolsLibInsertSizeEstimator.cpp src/BamToolsSCReadsReader.cpp src/BamToolsPairsToLeftReader.cpp
src/BamToolsPairsToRightReader.cpp src/TargetRegionToLeftFinder.cpp src/TargetRegionToRightFinder.cpp
src/MaxDistDiffBiPartitioner.cpp src/AnovaBiPartitionQualifier.cpp src/MedianPositionPicker.cpp
src/DeletionCaller.cpp src/SpanningPair.cpp src/error.cpp src/LeafTargetRegionFinder.cpp
src/variantcaller.cpp src/GenomePosition.cpp src/TargetRegion.cpp src/ChromosomeRegion.cpp)
#file(GLOB SOURCES "src/*.cpp")

add_executable(sprites2 ${SOURCES})
set(LIBRARIES ${LIBRARIES} ${HTSlib_LIBRARIES} $ENV{BAMTOOLS_HOME}/lib/libbamtools.a z)

target_link_libraries(sprites2 ${LIBRARIES})

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-3 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O2 -Wall")

if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    message(${CMAKE_CXX_FLAGS_DEBUG})
else(CMAKE_BUILD_TYPE MATCHES DEBUG)
    message(${CMAKE_CXX_FLAGS_RELEASE})
endif(CMAKE_BUILD_TYPE MATCHES DEBUG)
