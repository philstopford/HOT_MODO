# Non-standalone test file, generated from the original Makefile.am file

set (HalfTest_SOURCES
           main.cpp testArithmetic.cpp testArithmetic.h
           testBitPatterns.cpp testBitPatterns.h
           testClassification.cpp testClassification.h
           testError.cpp testError.h testFunction.cpp
           testFunction.h testLimits.cpp testLimits.h testSize.cpp
           testSize.h
)

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

add_executable (HalfTest ${HalfTest_SOURCES})
target_link_libraries (HalfTest Half)
add_openexr_test (HalfTest HalfTest)
