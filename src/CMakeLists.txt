set(SRCS
    moarload_app.cc
    moarload_main.cc
)

find_package(wxWidgets COMPONENTS core base REQUIRED)

INCLUDE(${wxWidgets_USE_FILE})

add_executable (moarload ${SRCS})

target_link_libraries(moarload
    ${wxWidgets_LIBRARIES}
)

