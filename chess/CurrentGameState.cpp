#include "CurrentGameState.h"

CurrentGameState::CurrentGameState():
	currentSide(0), 
	whiteKingMoved(0), 
	whiteRightRookMoved(0), 
	whiteLeftRookMoved(0), 
	blackKingMoved(0), 
	blackRightRookMoved(0), 
	blackLeftRookMoved(0),
	whiteTotalPoints(0), 
	blackTotalPoints(0), 
	whiteWon(0), 
	blackWon(0)
{
}

void CurrentGameState::reset()
{
	*this = CurrentGameState(); 
}