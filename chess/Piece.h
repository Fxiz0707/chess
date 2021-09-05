#pragma once
#include "SFML/Graphics.hpp"
#include "Resources.h"

class Piece : public sf::Drawable, public sf::Transformable
{
public:
	Piece(sf::Vector2f position, char piece); 
	
	Piece(); // only used for mCurrentlyHeld in Application 

private: 
	sf::RectangleShape mShape_; 

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};