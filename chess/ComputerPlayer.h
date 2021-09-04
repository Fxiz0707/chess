#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <random>
#include <vector>

#include "ChessGame.h"
#include "CurrentGameState.h"

class ComputerPlayer
{
public: 
	static void randomMove(CurrentGameState state, std::array<char, 64>&  board); 
	static int minimax(int depth, CurrentGameState state, std::array<char, 64> board, int alpha = INT_MIN, int beta = INT_MAX);
};