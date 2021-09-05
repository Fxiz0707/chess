#pragma once

enum class SIDE;

class CurrentGameState
{
public: 
	CurrentGameState();

	SIDE mCurrentSide; 
	
	bool mWhiteKingMoved; 
	bool mWhiteRightRookMoved; 
	bool mWhiteLeftRookMoved; 

	bool mBlackKingMoved; 
	bool mBlackRightRookMoved; 
	bool mBlackLeftRookMoved; 

	int mWhiteTotalPoints; 
	int mBlackTotalPoints; 

	bool mWhiteWon; 
	bool mBlackWon; 

	void reset(); 
};