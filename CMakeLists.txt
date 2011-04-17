# If the user specifies -DCMAKE_BUILD_TYPE on the command line, take their
# definition and dump it in the cache along with proper documentation,
# otherwise set CMAKE_BUILD_TYPE to Debug prior to calling PROJECT()
IF(DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of
build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug
Release RelWithDebInfo MinSizeRel.")
ELSE()
    SET(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build,
options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release
RelWithDebInfo MinSizeRel.")
ENDIF()

# Project name
project(moreload)

# Minium CMake version
cmake_minimum_required(VERSION 2.6)

IF(CMAKE_COMPILER_IS_GNUCXX)
    ADD_DEFINITIONS("-Wall -Wextra -ansi -pedantic")
ENDIF()
IF(MSVC)
    MESSAGE(msvc compiler detected)
ENDIF()

# Subdirectories
add_subdirectory(src)

