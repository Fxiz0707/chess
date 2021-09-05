#include "ChessGame.h"

ChessGame::ChessGame() :
	mGameBoard_
({
	//       0   1   2   3   4   5   6   7		
	/*0*/	'R','N','B','Q','K','B','N','R',
	/*1*/	'P','P','P','P','P','P','P','P',
	/*2*/	'#','#','#','#','#','#','#','#',
	/*3*/	'#','#','#','#','#','#','#','#',
	/*4*/	'#','#','#','#','#','#','#','#',
	/*5*/	'#','#','#','#','#','#','#','#',
	/*6*/	'p','p','p','p','p','p','p','p',
	/*7*/	'r','n','b','q','k','b','n','r'
	})
{
}

bool ChessGame::move(sf::Vector2i start, sf::Vector2i end)
{
	if (ChessLogic::get_side(mGameBoard_[start.x + 8 * start.y]) != mCurrentGameState_.mCurrentSide) return false; 

	if (ChessLogic::get_side(mGameBoard_[start.x + 8 * start.y]) == SIDE::BLACK)
	{
		int eh = 3; 
	}

	if (ChessLogic::move(mCurrentGameState_, start, end, mGameBoard_))
	{
		if (mCurrentGameState_.mCurrentSide == SIDE::WHITE) mCurrentGameState_.mCurrentSide = SIDE::BLACK;
		else if (mCurrentGameState_.mCurrentSide == SIDE::BLACK) mCurrentGameState_.mCurrentSide = SIDE::WHITE; 

		return true; 
	}

	return false; 
}

void ChessGame::do_computer_move()
{
}

bool ChessGame::is_check() const 
{
	return ChessLogic::is_check(mCurrentGameState_.mCurrentSide, mGameBoard_); 
}

bool ChessGame::is_checkmate() const 
{
	return ChessLogic::is_checkmate(mCurrentGameState_.mCurrentSide, mGameBoard_); 
}

const std::array<char, 64>& ChessGame::get_game_board() const
{
	return mGameBoard_; 
}

std::vector<sf::Vector2i> ChessGame::get_available_positions(sf::Vector2i pos) const
{
	std::vector<sf::Vector2i> positions1 = ChessLogic::available_positions(pos, mGameBoard_);
	std::vector<sf::Vector2i> castlingPositions = ChessLogic::castling_positions(mCurrentGameState_, pos, mGameBoard_);

	positions1.insert(positions1.end(), castlingPositions.begin(), castlingPositions.end()); 

	return positions1; 
}

SIDE ChessGame::get_current_side() const 
{
	return mCurrentGameState_.mCurrentSide; 
}

