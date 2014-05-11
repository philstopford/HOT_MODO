# Non-standalone Cmake driver for OpenEXR. Assumes that the IlmBase
# libraries have been previously defined and that find_package(ZLIB)
# succeeded

# Extract the version information from configure.ac
GET_VERSION (OpenEXR)

# Create the configuration header and install it
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/config/OpenEXRConfig.h.cmake
  ${OPENEXR_CFG_DIR}/OpenEXRConfig.h
)
install(FILES ${OPENEXR_CFG_DIR}/OpenEXRConfig.h
  DESTINATION "include/OpenEXR"
)

# Add the actual OpenEXR library
add_subdirectory(IlmImf)

# Add the tests
if (BUILD_TESTING)
  add_subdirectory(IlmImfTest)

  option(OPENEXR_BUILD_FUZZTEST 
    "Build IlmImf damaged input resilience test" OFF)
  if (OPENEXR_BUILD_FUZZTEST)
    add_subdirectory(IlmImfFuzzTest)
  endif()
endif()

option(OPENEXR_BUILD_EXAMPLE
  "Build IlmImf example program" OFF)
if (OPENEXR_BUILD_EXAMPLE)
add_subdirectory(IlmImfExamples)
endif()

option(OPENEXR_BUILD_UTILS
  "Build the IlmImf command line utilities" ON)
if(OPENEXR_BUILD_UTILS)
  add_subdirectory(exr2aces)
  add_subdirectory(exrenvmap)
  add_subdirectory(exrheader)
  add_subdirectory(exrmakepreview)
  add_subdirectory(exrmaketiled)
  add_subdirectory(exrmultiview)
  add_subdirectory(exrstdattr)
endif()
