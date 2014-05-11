# Install script for directory: /Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath

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
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/libImath.1.0.3.dylib"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/libImath.7.0.0.dylib"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/libImath.dylib"
    )
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libImath.1.0.3.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libImath.7.0.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libImath.dylib"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libImath.7.0.0.dylib"
        -change "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Iex/libIex.7.0.0.dylib" "libIex.7.0.0.dylib"
        "${file}")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenEXR" TYPE FILE FILES
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathColorAlgo.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathMatrixAlgo.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathVec.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathShear.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathFun.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathBox.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathBoxAlgo.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathEuler.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathExc.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathLimits.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathLine.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathLineAlgo.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathMatrix.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathPlane.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathSphere.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathVecAlgo.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathQuat.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathFrustum.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathMath.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathGL.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathColor.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathRandom.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathRoots.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathHalfLimits.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathInterval.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathGLU.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathFrame.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathPlatform.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Imath/ImathInt64.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

