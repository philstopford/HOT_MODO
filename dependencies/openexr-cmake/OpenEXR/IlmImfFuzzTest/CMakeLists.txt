# Non-standalone test file, generated from the original Makefile.am file

set (SRCS
    fuzzFile.cpp fuzzFile.h main.cpp tmpDir.h
    testFuzzScanLines.cpp testFuzzScanLines.h
    testFuzzTiles.cpp testFuzzTiles.h
)

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

add_executable (IlmImfFuzzTest ${SRCS})
target_link_libraries (IlmImfFuzzTest
  Half Iex Imath IlmThread IlmImf ${ZLIB_LIBRARIES})
add_openexr_test (IlmImfFuzzTest IlmImfFuzzTest)
