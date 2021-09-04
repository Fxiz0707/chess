#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

#include "ChessGame.h"
#include "Piece.h"
#include "CurrentGameState.h"

#include "ComputerPlayer.h"

class Application
{
public:
	Application();
	void run();
private:
	sf::RenderWindow mRenderWindow;
	const sf::Time mTimeframe;
	std::array<char, 64> mGameArr; // this field should only ever be edited by functions in the ChessGame namespace
	CurrentGameState mCurrentGameState; 

	// drawing components 
	sf::VertexArray mBackgroundBoard; 
	std::vector<sf::CircleShape> mPossibleMoveMarkings; 
	std::vector<Piece> mPieces; // gets synced by the pieces in mGameArr 
	sf::Text mWhiteWinsText; 
	sf::Text mBlackWinsText; 

	// sound components 
	sf::Sound mClickSound; 
	sf::Sound mPieceTakenSound; 

	// the piece that the user is currently attempting to drag 
	Piece mCurrentlyHeldPiece; 
	bool mUserIsCurrentlyHoldingPiece; 

	void update(sf::Time dt);
	void render();
	void handleEvents();

	// ran after a move has been made
	void updateDrawingComponents(); 

	void resetBoard(); 
};