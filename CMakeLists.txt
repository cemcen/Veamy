cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" AND
        NOT "${CMAKE_C_COMPILER_VERSION}" VERSION_LESS 4.2)
endif()


project(Veamy)

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
include(GNUInstallDirs)

# Targets that we develop here
enable_testing()
add_subdirectory(lib/utilities)
add_subdirectory(lib/delynoi)
add_subdirectory(veamy)
add_subdirectory(test)
