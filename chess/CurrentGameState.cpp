#include "CurrentGameState.h"

#include "ChessLogic.h"

CurrentGameState::CurrentGameState():
	mCurrentSide(SIDE::WHITE), 
	mWhiteKingMoved(false), 
	mWhiteRightRookMoved(false), 
	mWhiteLeftRookMoved(false), 
	mBlackKingMoved(false), 
	mBlackRightRookMoved(false), 
	mBlackLeftRookMoved(false),
	mWhiteTotalPoints(false), 
	mBlackTotalPoints(false), 
	mWhiteWon(false), 
	mBlackWon(false)
{
}

void CurrentGameState::reset()
{
	*this = CurrentGameState(); 
}