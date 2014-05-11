# Non-standalone test file, generated from the original Makefile.am file

set (SRCS
    main.cpp drawImage.cpp rgbaInterfaceExamples.cpp
    rgbaInterfaceTiledExamples.cpp
    generalInterfaceExamples.cpp
    lowLevelIoExamples.cpp previewImageExamples.cpp
    generalInterfaceTiledExamples.cpp
    generalInterfaceTiledExamples.h drawImage.h
    rgbaInterfaceExamples.h generalInterfaceExamples.h
    rgbaInterfaceTiledExamples.h
    lowLevelIoExamples.h previewImageExamples.h
)

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

add_executable (imfexamples ${SRCS})
target_link_libraries (imfexamples
  Half Iex Imath IlmThread IlmImf ${ZLIB_LIBRARIES})
