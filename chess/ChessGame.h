#pragma once
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>
#include <cassert>
#include <iostream>
#include <utility>

#include "CurrentGameState.h"

// 0 is white, corresponds to lower case
// 1 is black, corresponds to upper case 

namespace ChessGame
{
	std::vector<sf::Vector2i> availablePositions(sf::Vector2i position, std::array<char, 64>& const board); 
	
	std::vector<std::array<char, 64>> everyPosition(CurrentGameState state, std::array<char, 64>& const board);
	void everyPositionRecursive(int depth, CurrentGameState state, std::array<char, 64>& const board); 


	bool isCheck(bool side, std::array<char, 64>& const board); 
	bool isCheckMate(bool side, std::array<char, 64>& const board);
	bool isStaleMate(bool side, std::array<char, 64>& const board); 

	// returns true if the move was successful
	bool move(CurrentGameState& gameState, sf::Vector2i start, sf::Vector2i end, std::array<char, 64>& board); // only method which manipulates the board 

	// checks if the castling position puts you in check, or you go through check
	std::vector<sf::Vector2i> castlingPositions(CurrentGameState& const gameState, sf::Vector2i start, std::array<char, 64>& board);

	// helpers 
	bool getSide(char piece); 
	char getKing(int side); 
	bool positionIsInBoard(sf::Vector2i pos); 
	bool shouldPawnBeQueen(sf::Vector2i pos, std::array<char, 64>& const board); 
}