include(cmake/compilerwarnings.cmake)
include(cmake/requirements.cmake)

########################################################################################################################
# Defaults                                                                                                             #
########################################################################################################################
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(C_CXX_DIAGNOSTIC_FLAG "-fdiagnostics-color ${C_CXX_MAX_ERRORS}")
set(C_CXX_FLAGS "-fPIC ${C_CXX_DIAGNOSTIC_FLAG}")
set(CMAKE_CXX_FLAGS "${C_CXX_FLAGS} ${CXX_WARNINGS}")

########################################################################################################################
# Modules                                                                                                              #
########################################################################################################################
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

include(clangtidy)
