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
project(moarload)

# Minium CMake version
cmake_minimum_required(VERSION 2.6)

IF(CMAKE_COMPILER_IS_GNUCXX)
    ADD_DEFINITIONS("-Wall -Wextra -pedantic")
    ADD_DEFINITIONS("-ansi -std=c++0x")
    ADD_DEFINITIONS("-ffunction-sections -fdata-sections -s -Wl,--gc-sections")
    ADD_DEFINITIONS("-isystem /usr/local/include/cpp-netlib")
    ADD_DEFINITIONS("-isystem /usr/local/include/thrift")
    ADD_DEFINITIONS("-DHAVE_NETINET_IN_H")
ENDIF()
IF(MSVC)
    ADD_DEFINITIONS("/D _WIN32_WINNT=0x0600 /wd 4065 /D _CRT_SECURE_NO_WARNINGS /D WIN32_LEAN_AND_MEAN")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GL")
ENDIF()

# Subdirectories
add_subdirectory(src)

