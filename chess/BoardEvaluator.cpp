#include "BoardEvaluator.h"

namespace Chess
{
    PlayerBoardScore BoardEvaluator::GetBoardsValue(
            const ChessEngine::Model::Enums::Colour& m_p1Colour, 
            const ChessEngine::Model::Enums::MoveCheckType& m_gameType, 
            ChessEngine::Controller::BoardController& c_board
        ) {
            PlayerBoardScore result;
            int whiteScore = 0, blackScore = 0;
            auto pieces = c_board.ActivePieces();
            for(auto piece: pieces.v)
            {
                int positionalScore = GetPiecePositionalScore(m_p1Colour, piece);
                int pieceValue = GetPieceValue(piece);
                if(piece->IsWhite())
                {
                    whiteScore += positionalScore + pieceValue;
                }
                else
                {
                    blackScore += positionalScore + pieceValue;
                }
            }
            result.whiteScore = m_gameType == ChessEngine::Model::Enums::DADS? blackScore - whiteScore: whiteScore - blackScore;
            result.blackScore = m_gameType == ChessEngine::Model::Enums::DADS? whiteScore - blackScore: blackScore - whiteScore;
            return result;
        }

    int BoardEvaluator::GetPiecePositionalScore(
            const ChessEngine::Model::Enums::Colour& m_p1Colour, 
            const ChessEngine::Model::Piece* m_piece
        )
        {
            auto WHITE = ChessEngine::Model::Enums::WHITE;
            auto BLACK = ChessEngine::Model::Enums::BLACK;
            auto DADS = ChessEngine::Model::Enums::DADS;

            bool isWhite = 
                m_p1Colour == WHITE && m_piece->IsWhite() || 
                m_p1Colour == BLACK && !m_piece->IsWhite()? 
                true: false;

            int posX = m_piece->GetPosition().GetX();
            int posY = m_piece->GetPosition().GetY();
            int points;
            switch(m_piece->GetType())
            {
            case PAWN:
                points = isWhite? P1PAWN[posY][posX]: P2PAWN[posY][posX];
                break;
            case CASTLE:
                points = isWhite? P1CASTLE[posY][posX]: P2CASTLE[posY][posX];
                break;
            case HORSE:
                points = isWhite? P1HORSE[posY][posX]: P2HORSE[posY][posX];
                break;
            case BISHOP:
                points = isWhite? P1BISH[posY][posX]: P2BISHOP[posY][posX];
                break;
            case QUEEN:
                points = isWhite? P1QUEEN[posY][posX]: P2QUEEN[posY][posX];
                break;
            default:
                points = isWhite? P1KING[posY][posX]: P2KING[posY][posX];
                break;
            }
            return points;
        }
    
    int BoardEvaluator::GetPieceValue(const ChessEngine::Model::Piece* m_piece)
    {
        int value;
        switch(m_piece->GetType())
        {
            case PAWN:
                value = PAWN;
                break;
            case CASTLE:
                value = CASTLE;
                break;
            case HORSE:
                value = HORSE;
                break;
            case BISHOP:
                value = BISHOP;
                break;
            case QUEEN:
                value = QUEEN;
                break;
            default:
                value = 0;
                break;            
        }
        return value;
    }
}