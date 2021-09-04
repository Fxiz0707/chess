#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cassert>

// Singleton design pattern
// So that resources are held in one static 
class Resources
{
public: 
	static const sf::Texture& getTexture(char piece); 
	static const sf::SoundBuffer& getClickSound(); 
	static const sf::SoundBuffer& getPieceTakenSound(); 
	static const sf::Font& getMonoSpacedFont(); 
private: 
	sf::Texture w_King;
	sf::Texture w_Queen; 
	sf::Texture w_Bishop; 
	sf::Texture w_Knight; 
	sf::Texture w_Rook; 
	sf::Texture w_Pawn; 

	sf::Texture b_King;
	sf::Texture b_Queen;
	sf::Texture b_Bishop;
	sf::Texture b_Knight;
	sf::Texture b_Rook;
	sf::Texture b_Pawn;

	sf::SoundBuffer clickBuffer; 
	sf::SoundBuffer pieceTakenBuffer; 

	sf::Font mMonospacedFont; 
private: 
	Resources(); 
	static Resources& get(); 
	
	const sf::Texture& i_getTexture(char piece); 
};