# Install script for directory: /Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf

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
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/libIlmImf.1.7.1.dylib"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/libIlmImf.7.0.0.dylib"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/libIlmImf.dylib"
    )
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImf.1.7.1.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImf.7.0.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImf.dylib"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libIlmImf.7.0.0.dylib"
        -change "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Half/libHalf.7.0.0.dylib" "libHalf.7.0.0.dylib"
        -change "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/Iex/libIex.7.0.0.dylib" "libIex.7.0.0.dylib"
        -change "/Users/phil/Documents/development/hg/openexr-cmake/IlmBase/IlmThread/libIlmThread.7.0.0.dylib" "libIlmThread.7.0.0.dylib"
        "${file}")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenEXR" TYPE FILE FILES
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfAcesFile.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfArray.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfAttribute.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfB44Compressor.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfBoxAttribute.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfCRgbaFile.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfChannelList.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfChannelListAttribute.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfChromaticities.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfChromaticitiesAttribute.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfCompression.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfCompressionAttribute.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfConvert.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfDoubleAttribute.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfEnvmap.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfEnvmapAttribute.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfFloatAttribute.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfFrameBuffer.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfFramesPerSecond.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfHeader.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfHuf.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfIO.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfInputFile.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfInt64.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfIntAttribute.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfKeyCode.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfKeyCodeAttribute.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfLineOrder.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfLineOrderAttribute.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfLut.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfMatrixAttribute.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfMultiView.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfName.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfOpaqueAttribute.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfOutputFile.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfPixelType.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfPreviewImage.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfPreviewImageAttribute.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfRational.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfRationalAttribute.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfRgba.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfRgbaFile.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfRgbaYca.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfStandardAttributes.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfStringAttribute.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfStringVectorAttribute.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfTestFile.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfThreading.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfTileDescription.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfTileDescriptionAttribute.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfTiledInputFile.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfTiledOutputFile.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfTiledRgbaFile.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfTimeCode.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfTimeCodeAttribute.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfVecAttribute.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfVersion.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfWav.h"
    "/Users/phil/Documents/development/hg/openexr-cmake/OpenEXR/IlmImf/ImfXdr.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

