include_directories(../include)

find_package(CppUTest REQUIRED)
include_directories(${CPPUTEST_INCLUDE_DIR})

set(LIBRARIES ${LIBRARIES} ${CPPUTEST_LIBRARIES})
set(sources ../src/AnovaBiPartitionQualifier.cpp ../src/MaxDistDiffBiPartitioner.cpp)
set(testSources AnovaQualifierTest.cpp MaxDiffPartitionerTest.cpp)
add_executable(sprites2test testmain.cpp ${testSources} ${sources})

target_link_libraries(sprites2test ${LIBRARIES})
