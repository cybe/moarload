set(SRCS
    moarload_app.cc
    moarload_main.cc
    Pyload.cpp
    pyload_constants.cpp
    pyload_types.cpp
)

find_package(wxWidgets COMPONENTS core base REQUIRED)
INCLUDE(${wxWidgets_USE_FILE})

find_package(Boost REQUIRED)
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
	find_package(Boost COMPONENTS thread REQUIRED)
endif()

include_directories("/usr/local/include/thrift/")

if(UNIX)
    add_executable(moarload ${SRCS})
endif(UNIX)
if(WIN32)
    add_executable(moarload WIN32 ${SRCS})
endif(WIN32)

target_link_libraries(moarload
    ${wxWidgets_LIBRARIES}
    ${Boost_LIBRARIES}
    /usr/local/lib/libthrift.a
)

