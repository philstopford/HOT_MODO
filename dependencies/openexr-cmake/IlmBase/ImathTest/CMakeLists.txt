# Non-standalone test file, generated from the original Makefile.am file

set (ImathTest_SOURCES
            main.cpp testExtractEuler.cpp testExtractSHRT.cpp
            testFrustum.cpp testFun.cpp testInvert.cpp
            testMatrix.cpp testRandom.cpp testRoots.cpp
            testShear.cpp testColor.cpp testColor.h
            testExtractEuler.h testExtractSHRT.h testFrustum.h
            testFun.h testInvert.h testMatrix.h testRandom.h
            testRoots.h testShear.h testQuatSetRotation.cpp
            testQuatSetRotation.h testLineAlgo.cpp testLineAlgo.h
            testQuatSlerp.cpp testQuatSlerp.h testQuat.cpp
            testQuat.h testBoxAlgo.cpp testBoxAlgo.h
            testVec.cpp testVec.h testBox.cpp testBox.h
            testMiscMatrixAlgo.cpp testMiscMatrixAlgo.h
            testProcrustes.cpp testProcrustes.h
            testTinySVD.cpp testTinySVD.h
            testJacobiEigenSolver.cpp testJacobiEigenSolver.h
            testFrustumTest.cpp testFrustumTest.h
)

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

add_executable (ImathTest ${ImathTest_SOURCES})
target_link_libraries (ImathTest Imath Iex Half)
add_openexr_test (ImathTest ImathTest)
