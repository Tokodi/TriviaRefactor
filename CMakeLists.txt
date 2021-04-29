cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME trivia)

project(${PROJECT_NAME})

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message("####################################")
    message("# Do NOT build in source directory #")
    message("####################################")
endif()

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

add_executable(${PROJECT_NAME}
    Game.cpp
    GameRunner.cpp
)
