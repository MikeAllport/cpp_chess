# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
set(This cppchessengineproject)

project (${This} VERSION 1.0)
set (CMAKE_CXX_STANDARD 17)

set(Headers
    cppchess.h
)

set(Sources
    cppchess.cpp
)

enable_testing()
# Include sub-projects.

add_subdirectory ("cppchessengine")
add_subdirectory ("tests")
add_executable(${This} ${Headers} ${Sources})
target_link_libraries(${This} PUBLIC chess)
target_include_directories(cppchessengineproject PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/cppchessengine"
                          )    