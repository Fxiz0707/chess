#include "Piece.h"

Piece::Piece(sf::Vector2i position, char piece) : 
	mShape(sf::Vector2f{80.f, 80.f}),
	mPiece(piece),
	mBoardPosition(position)
{
	setPosition({ 80.f * mBoardPosition.x , 80.f * mBoardPosition.y});
	mShape.setTexture(&Resources::getTexture(mPiece)); 
}

Piece::Piece() : 
	mShape(sf::Vector2f(-1.f, -1.f)), 
	mPiece('#'), 
	mBoardPosition({-1, -1})
{
} 

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = getTransform(); 
	target.draw(mShape, states); 
}