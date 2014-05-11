# Install script for directory: /Users/phil/Documents/development/hg/openexr-cmake/OpenEXR

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenEXR" TYPE FILE FILES "/Users/phil/Documents/development/hg/openexr-cmake/config/OpenEXRConfig.h")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/cmake_install.cmake")
  INCLUDE("/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/exr2aces/cmake_install.cmake")
  INCLUDE("/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/exrenvmap/cmake_install.cmake")
  INCLUDE("/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/exrheader/cmake_install.cmake")
  INCLUDE("/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/exrmakepreview/cmake_install.cmake")
  INCLUDE("/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/exrmaketiled/cmake_install.cmake")
  INCLUDE("/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/exrmultiview/cmake_install.cmake")
  INCLUDE("/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/exrstdattr/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

