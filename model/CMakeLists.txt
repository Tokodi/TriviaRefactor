set(LIB_NAME model)

add_library(${LIB_NAME} STATIC
    board.cc
    dice.cc
    game.cc
    player.cc
)

target_include_directories(${LIB_NAME}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(test)
