set(LIB_NAME controller)

add_library(${LIB_NAME} STATIC
    controller.cc
)

target_include_directories(${LIB_NAME}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${LIB_NAME}
    model
    view
)
