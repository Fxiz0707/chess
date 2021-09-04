#include "Resources.h"

const sf::Texture& Resources::getTexture(char piece)
{
	return Resources::get().i_getTexture(piece); 
}

const sf::SoundBuffer& Resources::getClickSound()
{
	return get().clickBuffer; 
}

const sf::SoundBuffer& Resources::getPieceTakenSound()
{
	return get().pieceTakenBuffer; 
}

const sf::Font& Resources::getMonoSpacedFont()
{
	return get().mMonospacedFont; 
}

Resources::Resources() : 
	w_King(),
	w_Queen(),
	w_Bishop(),
	w_Knight(), 
	w_Rook(), 
	w_Pawn(),
	b_King(), 
	b_Queen(),
	b_Bishop(), 
	b_Knight(),
	b_Rook(),
	b_Pawn(), 
	clickBuffer(), 
	pieceTakenBuffer(), 
	mMonospacedFont()
{
	w_King.loadFromFile("pieces/w_king.png");
	w_Queen.loadFromFile("pieces/w_queen.png");
	w_Bishop.loadFromFile("pieces/w_bishop.png");
	w_Knight.loadFromFile("pieces/w_knight.png");
	w_Rook.loadFromFile("pieces/w_rook.png");
	w_Pawn.loadFromFile("pieces/w_pawn.png");

	b_King.loadFromFile("pieces/b_king.png");
	b_Queen.loadFromFile("pieces/b_queen.png");
	b_Bishop.loadFromFile("pieces/b_bishop.png");
	b_Knight.loadFromFile("pieces/b_knight.png");
	b_Rook.loadFromFile("pieces/b_rook.png");
	b_Pawn.loadFromFile("pieces/b_pawn.png");

	w_King.setSmooth(true); 
	w_Queen.setSmooth(true); 
	w_Bishop.setSmooth(true); 
	w_Knight.setSmooth(true); 
	w_Rook.setSmooth(true); 
	w_Pawn.setSmooth(true); 

	b_King.setSmooth(true);
	b_Queen.setSmooth(true);
	b_Bishop.setSmooth(true);
	b_Knight.setSmooth(true);
	b_Rook.setSmooth(true);
	b_Pawn.setSmooth(true);

	clickBuffer.loadFromFile("sounds/clickSound.wav");
	pieceTakenBuffer.loadFromFile("sounds/pieceTakenSound.wav");

	mMonospacedFont.loadFromFile("fonts/joystix monospace.ttf"); 
}

Resources& Resources::get()
{
	static Resources s_Resources; 
	return s_Resources; 
}

const sf::Texture& Resources::i_getTexture(char piece)
{
	assert(piece != '#'); 

	if (piece == 'k') return w_King; 
	if (piece == 'q') return w_Queen; 
	if (piece == 'b') return w_Bishop; 
	if (piece == 'n') return w_Knight; 
	if (piece == 'r') return w_Rook; 
	if (piece == 'p') return w_Pawn; 
	
	if (piece == 'K') return b_King;
	if (piece == 'Q') return b_Queen;
	if (piece == 'B') return b_Bishop;
	if (piece == 'N') return b_Knight;
	if (piece == 'R') return b_Rook;
	
	else  return b_Pawn; // to stop compiler error message 
}
