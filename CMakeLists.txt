# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
set(This cppchess)

project (${This} VERSION 1.0)
set (CMAKE_CXX_STANDARD 17)

set(Headers
    chess/cppchess.h
    chess/Textures.h
    chess/Game.h
    chess/Interfaces.h
)

set(Sources
    chess/cppchess.cpp
    chess/Textures.cpp
    chess/Game.cpp
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

# copy resources
add_custom_command(TARGET ${This} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_LIST_DIR}/res/
    $<TARGET_FILE_DIR:${This}>/res/)

# copy dependencies
set(SFML_DEPS
    ${CMAKE_CURRENT_LIST_DIR}/deps/sfml-graphics-3.dll
    ${CMAKE_CURRENT_LIST_DIR}/deps/sfml-system-3.dll
    ${CMAKE_CURRENT_LIST_DIR}/deps/sfml-window-3.dll)

foreach(file_i ${SFML_DEPS})
    add_custom_command(TARGET ${This} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${file_i} $<TARGET_FILE_DIR:${This}>)
endforeach(file_i ${SFML_DEPS})


target_include_directories(cppchess PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/cppchessengine"
                          )