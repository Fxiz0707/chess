#pragma once

class CurrentGameState
{
public: 
	CurrentGameState();

	bool currentSide; 
	
	bool whiteKingMoved; 
	bool whiteRightRookMoved; 
	bool whiteLeftRookMoved; 

	bool blackKingMoved; 
	bool blackRightRookMoved; 
	bool blackLeftRookMoved; 

	int whiteTotalPoints; 
	int blackTotalPoints; 

	bool whiteWon = false; 
	bool blackWon = false; 

	void reset(); 
};