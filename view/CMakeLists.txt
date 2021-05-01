set(LIB_NAME view)

add_library(${LIB_NAME} STATIC
    text_view.cc
)

target_include_directories(${LIB_NAME}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${LIB_NAME}
    model
)
