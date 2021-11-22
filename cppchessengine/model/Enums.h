#ifndef CHESS_MODELS_ENUMS
#define CHESS_MODELS_ENUMS


namespace ChessEngine::Model::Enums
{
	enum Colour { BLACK, WHITE };
	enum Player { P1, P2 };
	enum PieceType { PAWN, BISHOP, CASTLE, KING, QUEEN, HORSE};
	enum MoveCheckType { STANDARD, DADS };
}

#endif