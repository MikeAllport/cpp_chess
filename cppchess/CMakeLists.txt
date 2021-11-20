# CMakeList.txt : CMake project for cppchess, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 17)
set(This chess)
set(Headers
	model/Piece.h
	model/Point.h
	model/Pawn.h
	model/Horse.h
	model/Bishop.h
	model/Castle.h
	model/Queen.h
	model/King.h
	model/Enums.h
	model/Board.h
	model/Move.h
	model/Player.h
	model/AllPiecesInclude.h
	model/Game.h
	utils/VectorHelper.h
	controller/MoveController.h
	controller/BoardController.h
	controller/MoveTikrintojas.h
	controller/StandardMoveTikrintojas.h
	controller/DadsMoveTikrintojas.h
	controller/GameController.h
)

set(Sources
	controller/MoveController.cpp
	controller/BoardController.cpp
	controller/StandardMoveTikrintojas.cpp
	controller/DadsMoveTikrintojas.cpp
	controller/GameController.cpp
)

# Add source to this project's executable.
add_library (${This} STATIC ${Headers} ${Sources})

set (CMAKE_CXX_STANDARD 17)

# TODO: Add tests and install targets if needed.
