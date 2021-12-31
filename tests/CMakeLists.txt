# CMakeList.txt : CMake project for cppchessengine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
enable_testing()
add_subdirectory("ChessEngine")
add_subdirectory("Chess")