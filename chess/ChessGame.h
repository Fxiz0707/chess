#pragma once

#include <array>

#include <SFML/Graphics.hpp>

#include "ChessLogic.h"
#include "CurrentGameState.h"

class ChessGame
{
public:
	ChessGame(); 

	bool move(sf::Vector2i start, sf::Vector2i end); 

	void do_computer_move();


	bool is_check() const;

	bool is_checkmate() const; 


	const std::array<char, 64>& get_game_board() const; 
	std::vector<sf::Vector2i> get_available_positions(sf::Vector2i pos) const; 

	SIDE get_current_side() const;  

private:
	std::array<char, 64> mGameBoard_;

	CurrentGameState mCurrentGameState_;
};
