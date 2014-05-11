# Non-standalone test file

# Use OpenMP for external test threads
find_package (OpenMP)
if (OPENMP_FOUND)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()

set (IlmThreadTest_SOURCES
           main.cpp
           testGlobalThreadPoolInit.cpp testGlobalThreadPoolInit.h
)

add_executable (IlmThreadTest ${IlmThreadTest_SOURCES})
target_link_libraries (IlmThreadTest IlmThread)
add_openexr_test (IlmThreadTest IlmThreadTest)
