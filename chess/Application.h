#pragma once

#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Piece.h"
#include "ChessGame.h"
#include "ComputerPlayer.h"

class Application
{
public:
	Application();
	void run();
private:

	sf::RenderWindow mRenderWindow_;
	const sf::Time mTimeFrame_;

	ChessGame mChessGame_; 
	bool mWhiteWon_;
	bool mBlackWon_; 

	// drawing components 
	sf::VertexArray mBackgroundBoard_; 
	std::vector<sf::CircleShape> mPossibleMoveMarkings_; 
	std::vector<Piece> mGamePieces_;
	sf::Text mWhiteWinsText_; 
	sf::Text mBlackWinsText_; 

	// sound components 
	sf::Sound mPieceMovedSound_; 
	sf::Sound mCheckSound_; 

	// the piece that the user is currently attempting to drag 
	Piece mCurrentlyHeldPiece_; 
	bool mUserIsCurrentlyHoldingPiece_; 
	sf::Vector2i mCurrentlyHeldPiecePos_; 

	void update(sf::Time dt);
	void render();
	void handle_events();

	// ran after a move has been made
	void update_drawing_components(); 

	void reset_board();


	void handle_mouse_press(sf::Vector2i mousePos);

	void updatePossibleMarkings(sf::Vector2i boardPos); 

	void handle_mouse_release(sf::Vector2i mousePos);

	void handle_mouse_moved(sf::Vector2i mousePos); 
};