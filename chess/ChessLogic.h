#pragma once
#include <array>
#include <vector>
#include <utility>
#include <cassert>

#include <SFML/Graphics.hpp>

#include "CurrentGameState.h"

// 0 is white, corresponds to lower case
// 1 is black, corresponds to upper case 
enum class SIDE
{
	WHITE = 0, 
	BLACK = 1
};

class ChessLogic
{
public:

	// returns true if the move was successful
	static bool move(CurrentGameState& gameState, sf::Vector2i start, sf::Vector2i end, std::array<char, 64>& board);


	static bool is_check(SIDE side, const std::array<char, 64>& board);

	static bool is_checkmate(SIDE side, const std::array<char, 64>& board);


	static std::vector<sf::Vector2i> available_positions(sf::Vector2i pos, const std::array<char, 64>& board);

	// checks if the castling position puts you in check, or you go through check
	static std::vector<sf::Vector2i> castling_positions(const CurrentGameState& gameState, sf::Vector2i start, const std::array<char, 64>& board);

	static SIDE get_side(char piece);

private:

	static char get_king(SIDE side);
	static bool position_is_in_board(sf::Vector2i pos);
	static bool should_pawn_be_queen(sf::Vector2i pos, const std::array<char, 64>& board);


	static std::vector<sf::Vector2i> get_rook_positions(sf::Vector2i pos, const std::array<char, 64>& board);

	static std::vector<sf::Vector2i> get_knight_positions(sf::Vector2i pos, const std::array<char, 64>& board);

	static std::vector<sf::Vector2i> get_bishop_positions(sf::Vector2i pos, const std::array<char, 64>& board);

	static std::vector<sf::Vector2i> get_queen_positions(sf::Vector2i pos, const std::array<char, 64>& board);

	static std::vector<sf::Vector2i> get_king_positions(sf::Vector2i pos, const std::array<char, 64>& board);

	static std::vector<sf::Vector2i> get_pawn_positions(sf::Vector2i pos, const std::array<char, 64>& board);
};
