#pragma once
#include "SFML/Graphics.hpp"
#include "Resources.h"

class Piece : public sf::Drawable, public sf::Transformable
{
public:
	char mPiece; 
	sf::Vector2i mBoardPosition; 
	
	Piece(sf::Vector2i position, char piece); 
	
	Piece(); // only used for mCurrentlyHeld in Application 

private: 
	sf::RectangleShape mShape; 

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};