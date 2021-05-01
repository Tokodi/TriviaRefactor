cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME trivia)

project(${PROJECT_NAME})

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message("####################################")
    message("# Do NOT build in source directory #")
    message("####################################")
endif()

include(cmake/compilersettings.cmake)

add_executable(${PROJECT_NAME}
    main.cc
)

target_link_libraries(${PROJECT_NAME}
    controller
)

add_subdirectory(controller)
add_subdirectory(model)
add_subdirectory(view)
