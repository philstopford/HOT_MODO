# Non-standalone test file, generated from the original Makefile.am file

set (IlmImfTest_SOURCES
             main.cpp tmpDir.h testAttributes.cpp testChannels.cpp
             testCompression.cpp testCopyPixels.cpp
             testCustomAttributes.cpp testHuf.cpp testLineOrder.cpp
             testLut.cpp testRgba.cpp testRgbaThreading.cpp
             testSampleImages.cpp testSharedFrameBuffer.cpp
             testWav.cpp testXdr.cpp testAttributes.h testChannels.h
             testCompression.h testCopyPixels.h
             testCustomAttributes.h testHuf.h testLineOrder.h
             testLut.h testRgba.h testRgbaThreading.h
             testSampleImages.h testWav.h testSharedFrameBuffer.h
             testXdr.h testConversion.cpp testConversion.h
             testNativeFormat.cpp testNativeFormat.h
             testPreviewImage.cpp testPreviewImage.h
             testMagic.cpp testMagic.h testStandardAttributes.cpp
             testStandardAttributes.h testExistingStreams.cpp
             testExistingStreams.h testScanLineApi.cpp
             testScanLineApi.h testTiledCompression.cpp
             testTiledCompression.h testTiledCopyPixels.cpp
             testTiledCopyPixels.h testTiledLineOrder.cpp
             testTiledLineOrder.h testTiledRgba.cpp
             testTiledRgba.h compareFloat.h compareFloat.cpp
             testTiledYa.cpp testTiledYa.h
             testYca.cpp testYca.h compareB44.h compareB44.cpp
                     testMultiView.cpp testMultiView.h
             testIsComplete.cpp testIsComplete.h
)

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

add_definitions( -DILM_IMF_TEST_IMAGEDIR=\"${CMAKE_CURRENT_SOURCE_DIR}/\" )

add_executable (IlmImfTest ${IlmImfTest_SOURCES})
target_link_libraries (IlmImfTest
  Half Iex Imath IlmThread IlmImf ${ZLIB_LIBRARIES})
add_openexr_test (IlmImfTest IlmImfTest)
