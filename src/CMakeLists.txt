#--- source files

set(SRCS
    main.cpp
    util.cpp
    lib/json/jsoncpp.cpp
    net/py_load_connector.cpp
    net/py_load_http_connector.cpp
    net/py_load_thrift_connector.cpp
    net/request_queue.cpp
    net/http/cookie.cpp
    net/http/http_client.cpp
    net/thrift/pyload.cpp
    net/thrift/pyload_constants.cpp
    net/thrift/pyload_types.cpp
    services/configuration_service.cpp
    services/pyload_data_store.cpp
    ui/model/download_list_model_node.cpp
    ui/model/download_list_model.cpp
    ui/download_panel.cpp
    ui/main_frame_view.cpp
)


#--- dependencies

# wxWidgets
if(WIN32)
    SET(wxWidgets_ROOT_DIR "C:/dev/libs/wxWidgets-2.9.2")
endif(WIN32)
find_package(wxWidgets COMPONENTS adv core base REQUIRED)
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
    include_directories("C:/dev/libs/cpp-netlib-0.9.2")
endif(WIN32)

# thrift
if(UNIX)
    include_directories("/usr/local/include/thrift")
    set(thrift_LIBRARIES /usr/local/lib/libthrift.a)
endif(UNIX)
if(WIN32)
    include_directories("C:/dev/libs/thrift-trunk/lib/cpp/src")
	include_directories("C:/dev/libs/pthreads-w32-2.8.0/include")
	set(thrift_LIBRARIES
		C:/dev/libs/thrift-trunk/lib/cpp/Release/libthrift.lib
		C:/dev/libs/pthreads-w32-2.8.0/lib/pthreadVCE2.lib
	)
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
    ${Boost_LIBRARIES}
    ${thrift_LIBRARIES}
    ${wxWidgets_LIBRARIES}
)
