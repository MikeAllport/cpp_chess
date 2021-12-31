set(This cppchessengineTests)

set(Sources
	TestMoveController.cpp
	TestBoardController.cpp
	TestStandardMoveTikrintojas.cpp
	TestDadsMoveTikrintojas.cpp
	TestBoard.cpp
	TestGame.cpp
)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(${This} ${Sources})
target_link_libraries(${This}
	gtest
	gtest_main
	chessengine
)


add_test(
	NAME ${This}
	COMMAND ${This}
)