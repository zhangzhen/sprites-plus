include_directories(../include)

find_package(CppUTest REQUIRED)
include_directories(${CPPUTEST_INCLUDE_DIR})

set(LIBRARIES ${LIBRARIES} ${CPPUTEST_LIBRARIES})
set(sources ../src/AnovaBiPartitionQualifier.cpp ../src/MaxDistDiffBiPartitioner.cpp ../src/CustomSeqAligner.cpp
../src/error.cpp ../src/Interval.cpp ../src/AlignmentResult.cpp ../src/AlignmentResult.cpp ../src/AlignmentFragment.cpp)
set(testSources AnovaQualifierTest.cpp MaxDiffPartitionerTest.cpp SequenceAlignerTest.cpp)
add_executable(sprites2test testmain.cpp ${testSources} ${sources})

target_link_libraries(sprites2test ${LIBRARIES})

set_target_properties(sprites2test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
