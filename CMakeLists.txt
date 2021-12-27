# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
set(This cppchess)

project (${This} VERSION 1.0)
set (CMAKE_CXX_STANDARD 17)

set(Headers
    chess/cppchess.h
)

set(Sources
    chess/cppchess.cpp
)

enable_testing()
# Include sub-projects.

add_subdirectory("libs")
add_subdirectory ("cppchessengine")
add_subdirectory ("tests")
add_executable(${This} ${Headers} ${Sources})
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${This} PRIVATE sfml-graphics sfml-system)
target_link_libraries(${This} PUBLIC chessengine)

add_custom_command(TARGET ${This} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_LIST_DIR}/res/
    $<TARGET_FILE_DIR:${This}>/res/)

target_include_directories(cppchess PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/cppchessengine"
                          )