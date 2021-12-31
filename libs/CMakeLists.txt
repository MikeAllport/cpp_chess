#SFML
add_subdirectory(sfml)
include_directories(${SFML_INCLUDE_DIR})

#gtest
add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})