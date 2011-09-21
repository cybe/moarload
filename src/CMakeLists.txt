#--- source files

set(SRCS
    moarload_app.cc
    moarload_main.cc
)


#--- dependencies

# wxWidgets
find_package(wxWidgets COMPONENTS core base REQUIRED)
INCLUDE(${wxWidgets_USE_FILE})

# boost
find_package(Boost 1.45.0 REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
	link_directories (${Boost_LIBRARY_DIRS})
    SET(Boost_USE_MULTITHREADED ON)
    SET(Boost_USE_STATIC_RUNTIME OFF)
	if(WIN32)
        SET(Boost_USE_STATIC_LIBS ON)
    endif(WIN32)
    if(UNIX)
         SET(Boost_USE_STATIC_LIBS OFF)
    endif(UNIX)
	find_package(Boost COMPONENTS thread system REQUIRED)
endif()

# cpp-netlib
if(UNIX)
    include_directories("/usr/local/include/cpp-netlib")
endif(UNIX)
if(WIN32)
    include_directories("C:/dev/libs/cpp-netlib")
endif(WIN32)


#--- compile & link

# compile
if(UNIX)
    add_executable(moarload ${SRCS})
endif(UNIX)
if(WIN32)
    add_executable(moarload WIN32 ${SRCS})
endif(WIN32)

# link
target_link_libraries(moarload
    ${wxWidgets_LIBRARIES}
    ${Boost_LIBRARIES}
)

