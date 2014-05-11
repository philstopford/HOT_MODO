# Cmake file for the IlmBase libraries. This is not an standalone project!

# Extract the version information from configure.ac
GET_VERSION (IlmBase)

# Create the configuration header and install it
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/config/IlmBaseConfig.h.cmake
  ${OPENEXR_CFG_DIR}/IlmBaseConfig.h
)
install(FILES ${OPENEXR_CFG_DIR}/IlmBaseConfig.h
  DESTINATION "include/OpenEXR"
)

# Now add the actual projects
add_subdirectory(Half)
add_subdirectory(Iex)
add_subdirectory(Imath)
add_subdirectory(IlmThread)

# Add the tests
if(BUILD_TESTING)
  add_subdirectory(HalfTest)
  add_subdirectory(IexTest)
  add_subdirectory(ImathTest)
  add_subdirectory(IlmThreadTest)
endif()
