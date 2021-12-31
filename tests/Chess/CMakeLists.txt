set(This cppchessTests)

set(Sources
    TestBoardEvaluator.cpp
)

add_executable(${This} ${Sources})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include(Dart)
target_link_libraries(${This} PUBLIC
	gtest_main
)
add_dependencies(${This}
	cppchess
)

add_test(
	NAME ${This}
	COMMAND ${This}
)