#include "Piece.h"

Piece::Piece(sf::Vector2f position, char piece) : 
	mShape_(sf::Vector2f{80.f, 80.f})
{
	setPosition({ position.x , position.y});
	mShape_.setTexture(&Resources::getTexture(piece));
}

Piece::Piece() : 
	mShape_(sf::Vector2f(-1.f, -1.f))
{
} 

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = getTransform(); 
	target.draw(mShape_, states); 
}