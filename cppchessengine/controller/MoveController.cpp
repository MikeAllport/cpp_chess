#include "MoveController.h"

namespace ChessEngine::Controller
{
	std::map<ChessEngine::Model::Point, VectorHelper<ChessEngine::Model::Move>> MoveController::GetAllColoursMoves(const ChessEngine::Model::Enums::Colour colour)
	{
		std::map<ChessEngine::Model::Point, VectorHelper<ChessEngine::Model::Move>> moveMap;
		auto pieces = board->ActivePieces().Filter([colour](ChessEngine::Model::Piece* piece) { 
			bool isWhite = colour == ChessEngine::Model::Enums::WHITE;
			return piece->IsWhite() == isWhite;
		});
		for(auto piece: pieces.v)
		{
			auto moves = GetMoves(piece);
			if(!moves.v.empty())
				// no need to check if key exists, should be one piece per position
				moveMap[piece->GetPosition()] = moves;
		}
		return moveMap;
	}

	VectorHelper<Model::Move> ChessEngine::Controller::MoveController::GetMoves(Model::Piece* piece)
	{
		switch (piece->GetType())
		{
			case Model::Enums::PAWN :
				return GetMoves((Model::Pawn*)piece);
			case Model::Enums::BISHOP :
				return GetMoves((Model::Bishop*)piece);
			case Model::Enums::CASTLE :
				return GetMoves((Model::Castle*)piece);
			case Model::Enums::HORSE :
				return GetMoves((Model::Horse*)piece);
			case Model::Enums::KING :
				return GetMoves((Model::King*)piece);
			case Model::Enums::QUEEN :
				return GetMoves((Model::Queen*)piece);
			default: 
				return VectorHelper<Model::Move>();
		}
	}

	VectorHelper<Model::Move> ChessEngine::Controller::MoveController::GetMoves(Model::Pawn* piece)
	{
		VectorHelper<Model::Move> moves;
		int direction;
		if (player->IsWhite())
		{
			if (piece->IsWhite())
			{
				direction = -1;
			}
			else
			{
				direction = 1;
			}
		}
		else
		{
			if (piece->IsWhite())
			{
				direction = 1;
			}
			else
			{
				direction = -1;
			}
		}

		// gets positions can move		
		Model::Point position = piece->GetPosition();
		Model::Point infront(position.GetX(), position.GetY() + direction);
		Model::Point leftDiag(position.GetX()-1, position.GetY() + direction);
		Model::Point rightDiag(position.GetX()+1, position.GetY() + direction);
		// forward check
		if (infront.GetY() >= 0 && infront.GetY() <= 7 &&
			(*board)(infront) == nullptr)
		{
			moves.v.push_back(Model::Move(position, infront, false));
		}

		// leftDiag1
		if(leftDiag.GetX() >=0 && (*board)(leftDiag) && (*board)(leftDiag)->IsWhite() != piece->IsWhite())
		{
			moves.v.push_back(Model::Move(position, leftDiag, true));
		}

		// rightDiag
		if(rightDiag.GetX() <= 7 && (*board)(rightDiag) && (*board)(rightDiag)->IsWhite() != piece->IsWhite())
		{
			moves.v.push_back(Model::Move(position, rightDiag, true));
		}
		return moves;
	}

	VectorHelper<Model::Move> MoveController::GetMoves(Model::Bishop* piece)
	{
		return GetVerticalMoves(piece);
	}

	VectorHelper<Model::Move> MoveController::GetMoves(Model::Horse* piece)
	{
		VectorHelper<Model::Move> moves;
		auto position = piece->GetPosition();
		// side 2 spaces
		AddPieceMove(moves, piece, position.GetX() - 2, position.GetY() + 1);
		AddPieceMove(moves, piece, position.GetX() - 2, position.GetY() - 1);
		AddPieceMove(moves, piece, position.GetX() + 2, position.GetY() + 1);
		AddPieceMove(moves, piece, position.GetX() + 2, position.GetY() - 1);
		
		// vertical 2 spaces
		AddPieceMove(moves, piece, position.GetX() - 1, position.GetY() + 2);
		AddPieceMove(moves, piece, position.GetX() - 1, position.GetY() - 2);
		AddPieceMove(moves, piece, position.GetX() + 1, position.GetY() + 2);
		AddPieceMove(moves, piece, position.GetX() + 1, position.GetY() - 2);
		return moves;
	}

	VectorHelper<Model::Move> MoveController::GetMoves(Model::Castle* piece)
	{
		return GetVerticalMoves(piece).Concatenate(GetHorizontalMoves(piece));
	}

	VectorHelper<Model::Move> MoveController::GetMoves(Model::King* piece)
	{
		VectorHelper<Model::Move> moves;
		auto position = piece->GetPosition();
		AddPieceMove(moves, piece, position.GetX() - 1, position.GetY());
		AddPieceMove(moves, piece, position.GetX() - 1, position.GetY() - 1);
		AddPieceMove(moves, piece, position.GetX() - 1, position.GetY() + 1);
		AddPieceMove(moves, piece, position.GetX() + 1, position.GetY());
		AddPieceMove(moves, piece, position.GetX() + 1, position.GetY() - 1);
		AddPieceMove(moves, piece, position.GetX() + 1, position.GetY() - 1);
		AddPieceMove(moves, piece, position.GetX(), position.GetY() - 1);
		AddPieceMove(moves, piece, position.GetX(), position.GetY() + 1);

		// castling moves
		AddCastlingMove(moves, piece);
		return moves;
	}

	void MoveController::AddCastlingMove(VectorHelper<Model::Move>& moves, 
	Model::King* piece)
	{
		if(piece->HasMoved())
		{
			// cant castle
			return;
		}

		// get castle positions
		bool IsWhite = piece->IsWhite();
		auto position = piece->GetPosition();
		int leftCastleX = 0;
		int rightCastleX = 7;
		int castleY;
		if (player->IsWhite())
		{
			castleY = IsWhite? 7: 0;
		}
		else
		{
			castleY = IsWhite? 0: 7;
		}

		// get castles
		BoardController c_board(*board, *player);
		auto leftCastlePiece = c_board.GetPieceSafe(Model::Point(leftCastleX, castleY));
		auto rightCastlePiece = c_board.GetPieceSafe(Model::Point(rightCastleX, castleY));

		// check path is clear
		bool pieceBlockingLeft = false;
		bool pieceBlockingRight = false;
		// check left
		for(int i = 1; i < 4; ++i)
		{
			if(c_board.GetPieceSafe(Model::Point(i, castleY)))
			{
				pieceBlockingLeft = true;
			}
		}
		// check right
		for(int i = 5; i < 7; ++i)
		{
			if(c_board.GetPieceSafe(Model::Point(i, castleY)))
			{
				pieceBlockingRight = true;
			}
		}

		// do logic
		if(leftCastlePiece && leftCastlePiece->GetType() == Model::Enums::CASTLE)
		{
			// left castle
			auto leftCastle = (Model::Castle*) leftCastlePiece;
			if(leftCastle && !leftCastle->HasMoved() && !pieceBlockingLeft)
			{
				AddPieceMove(moves, piece, position.GetX()-2, position.GetY());
			}

			// right castle
			auto rightCastle = (Model::Castle*) rightCastlePiece;
			if(rightCastle && !rightCastle->HasMoved() && !pieceBlockingRight)
			{
				AddPieceMove(moves, piece, position.GetX() + 2, position.GetY());
			}
		}
	}

	VectorHelper<Model::Move> MoveController::GetMoves(Model::Queen* piece)
	{
		return GetDiagonalMoves(piece).Concatenate(GetHorizontalMoves(piece).Concatenate(GetVerticalMoves(piece)));
	}

	VectorHelper<Model::Move> MoveController::GetDiagonalMoves(Model::Piece* piece)
	{
		VectorHelper<Model::Move> moves;
		int pieceX = piece->GetPosition().GetX();
		int pieveY = piece->GetPosition().GetY();
		bool canMove = true;
		// upper left diag
		for(int x = pieceX - 1, y = pieveY - 1; x >= 0 && y >= 0 && canMove; --x, --y)
		{
			canMove = AddPieceMove(moves, piece, x, y);
		}

		//upper right diag
		canMove = true;
		for(int x = pieceX + 1, y = pieveY - 1; x <= 7 && y >= 0 && canMove; ++x, --y)
		{
			canMove = AddPieceMove(moves, piece, x, y);
		}

		//lower right diag
		canMove = true;
		for(int x = pieceX + 1, y = pieveY + 1; x <= 7 && y <= 7 && canMove; ++x, ++y)
		{
			canMove = AddPieceMove(moves, piece, x, y);
		}

		//lower left diag
		canMove = true;
		for(int x = pieceX - 1, y = pieveY + 1; x >= 0 && y <= 7 && canMove; --x, ++y)
		{
			canMove = AddPieceMove(moves, piece, x, y);
		}
		return moves;
	}

	bool MoveController::AddPieceMove(VectorHelper<Model::Move>& moves, Model::Piece* piece, int x, int y)
	{
		if (x < 0 || x > 7 || y < 0 || y > 7)
		{
			return false;
		}
		if(!(*board)(x, y))
		{
			moves.v.push_back(Model::Move(piece->GetPosition(), Model::Point(x, y), false));
			return true;
		}
		else if((*board)(x, y)->IsWhite() != piece->IsWhite())
		{
			moves.v.push_back(Model::Move(piece->GetPosition(), Model::Point(x, y), true));
		}
		return false;
	}

	VectorHelper<Model::Move> MoveController::GetHorizontalMoves(Model::Piece* piece)
	{
		VectorHelper<Model::Move> moves;
		int y = piece->GetPosition().GetY();
		bool canMove = true;

		// get left
		for(int x = piece->GetPosition().GetX() - 1; x >= 0 && canMove; --x)
		{
			canMove = AddPieceMove(moves, piece, x, y);
		}

		// get right
		for(int x = piece->GetPosition().GetX() + 1; x <= 7 && canMove; ++x)
		{
			canMove = AddPieceMove(moves, piece, x, y);		
		}
		return moves;
	}

	VectorHelper<Model::Move> MoveController::GetVerticalMoves(Model::Piece* piece)
	{
		VectorHelper<Model::Move> moves;
		int x = piece->GetPosition().GetX();
		bool canMove = true;

		// get up
		for(int y = piece->GetPosition().GetY() - 1; y >= 0 && canMove; --y)
		{
			canMove = AddPieceMove(moves, piece, x, y);
		}
		// get down
		for(int y = piece->GetPosition().GetY() + 1; y <= 7 && canMove; ++y)
		{
			canMove = AddPieceMove(moves, piece, x, y);		
		}
		return moves;
	}
}
