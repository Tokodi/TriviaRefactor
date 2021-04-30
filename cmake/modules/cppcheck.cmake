set(CPPCHECK_BUILD_DIR "${CMAKE_BINARY_DIR}/analysis/cppcheck")

file(MAKE_DIRECTORY ${CPPCHECK_BUILD_DIR})

list(APPEND CPPCHECK_ARGS "-j 1")
list(APPEND CPPCHECK_ARGS "--cppcheck-build-dir=${CPPCHECK_BUILD_DIR}")
list(APPEND CPPCHECK_ARGS "--error-exitcode=-1")
list(APPEND CPPCHECK_ARGS "--enable=all")
list(APPEND CPPCHECK_ARGS "--std=c++17")
list(APPEND CPPCHECK_ARGS "--suppress=missingInclude")
list(APPEND CPPCHECK_ARGS "--suppress=unmatchedSuppression")
list(APPEND CPPCHECK_ARGS "--suppress=unusedFunction")
list(APPEND CPPCHECK_ARGS "--library=googletest")
list(APPEND CPPCHECK_ARGS "--quiet")
list(APPEND CPPCHECK_ARGS "-i${PROJECT_SOURCE_DIR}/build")

set(CPPCHECK_BUILD
    cppcheck
    ${CPPCHECK_ARGS}
    ${PROJECT_SOURCE_DIR}
)

add_custom_target(cppcheck ALL COMMAND ${CPPCHECK_BUILD})
