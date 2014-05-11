# Non-standalone test file, generated from the original Makefile.am file

set (IexTest_SOURCES main.cpp testBaseExc.cpp testBaseExc.h)

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

add_executable (IexTest ${IexTest_SOURCES})
target_link_libraries (IexTest Iex)
add_openexr_test (IexTest IexTest)
