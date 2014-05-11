# CMake project file to build the OpenEXR components
#
# Assumes  that the variables set up by FindZlib are already configured by another entity,
# like the top level directory, and also ZLIB_LIB_FILENAME must
# contain the full path to the zlib import library when building
# this as a Windows DLL.

project(OpenEXR)
cmake_minimum_required(VERSION 2.6.2 FATAL_ERROR)

option(OPENEXR_SHARED_LIBS
  "Builds the different OpenEXR components as shared libraries." ON)
  
if(OPENEXR_SHARED_LIBS)
  set(OPENEXR_LIBTYPE "SHARED")
else()
  set(OPENEXR_LIBTYPE "STATIC")
endif()

# Building Windows DLL's on MSVC requires lots of extra work
if(OPENEXR_SHARED_LIBS AND MSVC)
  set(OPENEXR_DLL ON)
endif()

# OpenEXR requires zlib
find_package(ZLIB REQUIRED)


# Macro to get the version information from the configure.ac file in the
# current directory. Its argument is the name of the library as passed to
# AC_INIT. It will set the variables LIBNAME_VERSION and LIBNAME_SOVERSION
macro (GET_VERSION libname)
  string(TOUPPER "${libname}" libname_upper)
  
  # Read the relevant content from configure.ac
  file (STRINGS configure.ac tmp_configure_ac
    REGEX "(AC_INIT.+)|LIBTOOL_.+=[ \\t]*[0-9]+")
  
  string (REGEX REPLACE ".*AC_INIT\\([ \\t]*([0-9a-zA-z_]+)[ \\t]*,[ \\t]*([0-9\\.]+).*" "\\2"
    ${libname_upper}_VERSION ${tmp_configure_ac})
  if (NOT ${CMAKE_MATCH_1} STREQUAL ${libname})
    message (WARNING "The configure.ac file inits \"${CMAKE_MATCH_1}\" but \"${libname}\" was expected instead.")
  endif()
  string (REGEX REPLACE ".*LIBTOOL_CURRENT[ \\t]*=[ \\t]*([0-9]+).*" "\\1"
    ${libname_upper}_LIBTOOL_CURRENT ${tmp_configure_ac})
  string (REGEX REPLACE ".*LIBTOOL_REVISION[ \\t]*=[ \\t]*([0-9]+).*" "\\1"
    ${libname_upper}_LIBTOOL_REVISION ${tmp_configure_ac})
  string (REGEX REPLACE ".*LIBTOOL_AGE[ \\t]*=[ \\t]*([0-9]+).*" "\\1"
    ${libname_upper}_LIBTOOL_AGE ${tmp_configure_ac})
    
  # Version string for libtool
  set (${libname_upper}_SOVERSION 
    ${${libname_upper}_LIBTOOL_CURRENT}.${${libname_upper}_LIBTOOL_REVISION}.${${libname_upper}_LIBTOOL_AGE}
  )
  
  # Checks if the string needs to be displayed
  set (${libname_upper}_DISPLAYSTR_AUX 
    "Found ${libname} version ${${libname_upper}_VERSION}, soversion ${${libname_upper}_SOVERSION} from configure.ac"
  )
  if ((NOT ${libname_upper}_DISPLAYSTR) OR (NOT ${libname_upper}_DISPLAYSTR STREQUAL ${libname_upper}_DISPLAYSTR_AUX))
    set (${libname_upper}_DISPLAYSTR ${${libname_upper}_DISPLAYSTR_AUX} 
      CACHE INTERNAL "Version string from ${libname}" FORCE)
    message (STATUS ${${libname_upper}_DISPLAYSTR})
  endif ()

endmacro()

# A small macro to pass extra compiler properties to MSVC (useful to disable warnings)
macro(MSVC_COMPILE_FLAGS targetname flags)
  if(MSVC)
  set_target_properties(${targetname}
    PROPERTIES
    COMPILE_FLAGS "${flags}"
    )
  endif(MSVC)
endmacro()


# Configurable target directories
set(INSTALL_INCLUDE_DIR "include/OpenEXR" CACHE STRING
  "Installation path for the public headers (relative to the install prefix.)")
set(INSTALL_LIBRARY_DIR "lib" CACHE STRING
  "Installation path for the link libraries (relative to the install prefix.)")
set(INSTALL_RUNTIME_DIR "bin" CACHE STRING
  "Installation path for the binary runtime (relative to the install prefix.)")

# For install we define a macro
macro(INSTALL_TARGET targetname)
  install(TARGETS ${targetname}
    RUNTIME DESTINATION ${INSTALL_RUNTIME_DIR}
    LIBRARY DESTINATION ${INSTALL_LIBRARY_DIR}
    ARCHIVE DESTINATION ${INSTALL_LIBRARY_DIR}
    PUBLIC_HEADER DESTINATION ${INSTALL_INCLUDE_DIR}
  )
endmacro()


# First we need to create the configuration headers

# Directory for the generated configuration files
set(OPENEXR_CFG_DIR ${CMAKE_CURRENT_BINARY_DIR}/config)

find_package(Threads)

# pthreads
if(CMAKE_USE_PTHREADS_INIT)
  set(HAVE_PTHREAD 1)
endif()

# POSIX semaphores
include(CheckIncludeFile)
if(APPLE)
  set(HAVE_POSIX_SEMAPHORES 0)
else()
  CHECK_INCLUDE_FILE("semaphore.h" HAVE_POSIX_SEMAPHORES)
endif()


if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(HAVE_LINUX_PROCFS 1)
endif()

if(APPLE)
  set(HAVE_DARWIN 1)
endif()

# Detect that std::right if is usable
include(CheckCXXSourceCompiles)
CHECK_CXX_SOURCE_COMPILES("
#include <iomanip>
int main (int argc, char **argv) {
  std::right;
  return 0;
}
" HAVE_COMPLETE_IOMANIP)

# Check if the stack is large enough (ie more than 256 KiB)
include(CheckCSourceRuns)
CHECK_C_SOURCE_RUNS("
#include <stddef.h>
#include <string.h>
int main (int argc, char **argv)
{
    size_t arr[0x40000];
    memset(arr, 0, sizeof(arr));
    return 0;
}
" HAVE_LARGE_STACK)


# The build requires headers defined within all directories
include_directories( ${OPENEXR_CFG_DIR} )
include_directories( IlmBase/Half )
include_directories( IlmBase/Iex )
include_directories( IlmBase/Imath )
include_directories( IlmBase/IlmThread )
include_directories( OpenEXR/IlmImf )


# Flag to indicate whether this needs the special createDLL tool
set (NEEDS_CREATEDLL FALSE)

# When building a windows dll we need to add some defines and build the create dll tool
if(OPENEXR_DLL)
  add_definitions(-DOPENEXR_DLL)
  
  if (MSVC)
    set (NEEDS_CREATEDLL TRUE)
  endif()
  
  if (NEEDS_CREATEDLL)
    if (MSVC_IDE)
      add_subdirectory(IlmBase/vc/createDLL)
    else ()
      message (FATAL_ERROR "The createDLL toolchain is only supported using Visual Studio.")
    endif ()
  endif ()
  
  # The DLLs need special handling. It assumes that the resource file has been generated!
  if (NEEDS_CREATEDLL)
  
    # List of the paths of the different version of the zlib to use
    set(ZLIB_PATHS "")
  
    # Extract the full filename of zlib, both the debug and release versions if they are present
    list(LENGTH ZLIB_LIBRARIES zlib_libraries_len)
    if (zlib_libraries_len GREATER 0)
      # Loop over all libraries
      foreach(zlib_current ${ZLIB_LIBRARIES})
        if (NOT ("${zlib_current}" STREQUAL "debug" OR 
            "${zlib_current}" STREQUAL "optimized" OR
              "${zlib_current}" STREQUAL "general"))
          get_filename_component(zlib_filename "${zlib_current}" ABSOLUTE)
          get_filename_component(zlib_path "${zlib_filename}" PATH)
          list (APPEND ZLIB_PATHS ${zlib_path})
        endif()
        list(REMOVE_DUPLICATES ZLIB_PATHS)
      endforeach()
    else()
      message (FATAL_ERROR "Could not identify the zlib components")
    endif()
  
    macro(CREATEDLL targetname)
  
      # The createdll program needs an export map while keeping all the symbols
      set_target_properties(${targetname} PROPERTIES
        LINK_FLAGS "/MAP /MAPINFO:EXPORTS /OPT:NOREF /OPT:ICF")
        
      if(${ARGC} EQUAL 2)
        set(EXTRA_LIB "-o${ARGV1}")
      endif()
      
      if (CMAKE_GENERATOR MATCHES "Visual Studio")
        set (createDLL_ARGS
          "-x${targetname}.res" "-M$(PlatformName)"
          "-n$(OutDir)\\$(TargetName).map"
          "-l$(IntDir)"
          "-l$(SolutionDir)IlmBase\\Half\\${CMAKE_CFG_INTDIR}"
          "-l$(SolutionDir)IlmBase\\Iex\\${CMAKE_CFG_INTDIR}"
          "-l$(SolutionDir)IlmBase\\Imath\\${CMAKE_CFG_INTDIR}"
          "-l$(SolutionDir)IlmBase\\IlmThread\\${CMAKE_CFG_INTDIR}"
          "-i$(OutDir)\\$(TargetName).lib"
        )
      else()
        message(AUTHOR_WARNING "Check that this path works properly")
        if (CMAKE_SIZEOF_VOID_P EQUAL 8)
          set (createDLL_Platform "X64")
        else()
          set (createDLL_Platform "X86")
        endif()
        set (createDLL_ARGS
          "-x${targetname}.res" "-M${createDLL_Platform}"
          "-n${CMAKE_CURRENT_BINARY_DIR}\\${CMAKE_CFG_INTDIR}\\${targetname}.map"
          "-l${CMAKE_CURRENT_BINARY_DIR}\\${targetname}.dir\\${CMAKE_CFG_INTDIR}"
          "-l${PROJECT_BINARY_DIR}\\IlmBase\\Half\\${CMAKE_CFG_INTDIR}"
          "-l${PROJECT_BINARY_DIR}\\IlmBase\\Iex\\${CMAKE_CFG_INTDIR}"
          "-l${PROJECT_BINARY_DIR}\\IlmBase\\Imath\\${CMAKE_CFG_INTDIR}"
          "-l${PROJECT_BINARY_DIR}\\IlmBase\\IlmThread\\${CMAKE_CFG_INTDIR}"
          "-i${CMAKE_CURRENT_BINARY_DIR}\\${CMAKE_CFG_INTDIR}\\${targetname}.lib"
        )
      endif()
      if (ZLIB_PATHS)
        set (createDLL_ARGS ${createDLL_ARGS} "-l${ZLIB_PATHS}")
      endif()
      add_custom_command(TARGET ${targetname} POST_BUILD
        COMMAND createDLL
          ${createDLL_ARGS}
          "${EXTRA_LIB}"
        COMMENT "Exporting all public symbols from $(TargetFileName)..."
      )
      
      # If createDLL does not exist before the target is created, horrible things happen
      add_dependencies(${targetname} createDLL)
    endmacro()
    
  else()
  
    # Define the macro as no-ops
    macro(CREATEDLL targetname)
    endmacro()
  endif () # NEEDS_CREATEDLL
  
endif()


if (WIN32 AND OPENEXR_SHARED_LIBS)
  # Store in cache the master resource file
  get_filename_component(OPENEXR_RC_PATH "win32/openexr.rc" 
    ABSOLUTE CACHE)
  mark_as_advanced(OPENEXR_RC_PATH)

  # Macro to add the resource file
  macro(ADD_RESOURCE targetname sourceslst_var description version year)
    
    set(RC_DESCRIPTION "${description}")
    set(RC_VERSION "${version}.0")
    string(REPLACE "." "," RC_VERSION_COMMA ${RC_VERSION})
    set(RC_FILENAME "${targetname}.dll")
    set(RC_NAME "${targetname}")
    set(RC_YEAR "${year}")
    configure_file("${OPENEXR_RC_PATH}"
      "${CMAKE_CURRENT_BINARY_DIR}/${RC_NAME}.rc"  ESCAPE_QUOTES)
    
    # MSVC can take the .rc file directly, MINGW needs more magic
    if (MSVC)
      list(APPEND ${sourceslst_var} "${CMAKE_CURRENT_BINARY_DIR}/${RC_NAME}.rc")
    elseif (MINGW)
      # Based on the function from zlib 1.2.5:
      # This gets us DLL resource information when compiling on MinGW.
      add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${RC_NAME}_rc.obj"
                         COMMAND windres.exe
                              -D GCC_WINDRES
                              -o "${CMAKE_CURRENT_BINARY_DIR}/${RC_NAME}_rc.obj"
                              -i "${CMAKE_CURRENT_BINARY_DIR}/${RC_NAME}.rc")
      list(APPEND ${sourceslst_var} "${CMAKE_CURRENT_BINARY_DIR}/${RC_NAME}_rc.obj")
    endif ()
  
  endmacro()

endif()



# Helper global property to hold the targets created with ADD_OPENEXR_LIBRARY.
set_property(GLOBAL PROPERTY OPENEXR_LIBRARY_TARGETS "")

# Super macro with all the common stuff. The arguments are:
#   - Name of the target to build
#   - Variable with the public headers list
#   - Variable with all the other sources
#   - Description of the library
#   - Version of the library (e.g. 1.0.1)
#   - soversion of the library, as used by libtool (e.g. 6.0.0)
#   - Copyright year
#   - Optional extra arg: extra library to add when linking the dll
macro(ADD_OPENEXR_LIBRARY targetname publicheaders_var sources_var description 
                          version soversion year)

  # Adds the resource and module definitions files if necessary
  if (OPENEXR_SHARED_LIBS AND WIN32)
    ADD_RESOURCE (${targetname} ${sources_var} 
      ${description} ${version} ${year})
  endif()
  
  # Adds the target
  add_library(${targetname} ${OPENEXR_LIBTYPE} ${${publicheaders_var}} ${${sources_var}})
  set_target_properties(${targetname} PROPERTIES 
    VERSION ${version}
    SOVERSION ${soversion}
    DEBUG_POSTFIX "d"
    PUBLIC_HEADER "${${publicheaders_var}}"
  )
  set_property(GLOBAL APPEND PROPERTY OPENEXR_LIBRARY_TARGETS "${targetname}")
  
  # If built as a static library in gcc we need to add the fpic flag, so that the code will work when linked into a shared lib
  if(OPENEXR_LIBTYPE STREQUAL "STATIC" AND CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_COMPILER_IS_GNUCC)
    set_target_properties(${targetname} PROPERTIES 
      COMPILE_FLAGS "-fpic"
    )
  endif()
  
  # For MSVC static libraries, modify the name for easier identification
  if(MSVC AND OPENEXR_LIBTYPE STREQUAL "STATIC")
    set_target_properties(${targetname} PROPERTIES 
      OUTPUT_NAME "${targetname}_static"
    )
  endif()
  
  # For the windows dll we need extra definitions and use createDLL
  if(OPENEXR_DLL)
    string(TOUPPER ${targetname} targetUpper)
    add_definitions(-D${targetUpper}_EXPORTS)
    CREATEDLL(${targetname} ${ARGV7})
  endif()
  
  # Finally installs the target
  INSTALL_TARGET(${targetname})

endmacro()



option(BUILD_TESTING "Build the tests." OFF)
if(BUILD_TESTING)
  # Enable ctest-based tests here and in all the subdirectories
  enable_testing()
endif()

# Helper function to add tests. When using the Visual Studio generators with
# CMake 2.8 it will wrap the test in a batch file so that tests may be launched
# from within the IDE
function(add_openexr_test testname Exename)  
  if (NOT MSVC_IDE OR ${CMAKE_VERSION} VERSION_LESS "2.8")
    add_test("${testname}" "${Exename}" ${ARGN})
    return()
  endif()
  
  # More involved test specification using generator expressions
  set(extra "")
  get_property(openexr_targets GLOBAL PROPERTY OPENEXR_LIBRARY_TARGETS)
  foreach (target ${openexr_targets})
    if(TARGET ${target})
      list(APPEND extra "$<TARGET_FILE_DIR:${target}>")
    endif()
  endforeach()
  if(NOT extra)
    set(extra "NONE")
  endif()
  
  if(TARGET "${Exename}")
    set(exe "$<TARGET_FILE:${Exename}>")
  else()
    set(exe "${Exename}")
  endif()
  
  # Protect the semicolons in the path list using batch delayed expansion
  string(REPLACE ";" "!CMAKE_PATH_SEPARATOR!" extra "${extra}")
  add_test(NAME "${testname}"
    COMMAND "${OpenEXR_SOURCE_DIR}\\win32\\test_wrapper.cmd"
    "${extra}" "${exe}" ${ARGN}
  )
endfunction()



# Process each group of libraries
add_subdirectory(IlmBase)
add_subdirectory(OpenEXR)
