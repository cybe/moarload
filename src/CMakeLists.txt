set(SRCS
    moarload_app.cc
    moarload_main.cc
)

find_package(wxWidgets COMPONENTS core base REQUIRED)

INCLUDE(${wxWidgets_USE_FILE})

if(UNIX)
	add_executable(moarload ${SRCS})
endif(UNIX)

if(WIN32)
	add_executable(moarload WIN32 ${SRCS})
endif(WIN32)

target_link_libraries(moarload
    ${wxWidgets_LIBRARIES}
)

