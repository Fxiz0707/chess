#pragma once

#include <vector>
#include <array>

#include "ChessGame.h"
#include "ChessLogic.h"

// COMPUTER PLAYER ALWAYS PLAYS AS BLACK 

class ComputerPlayer
{
public:
	static void do_computer_move(int depth, ChessGame& chessGame);

private:

	static int static_eval(const std::array<char, 64>& gameBoard);

	static std::vector<ChessGame> gen(const ChessGame& chessGame);

	static int minimax(int depth, ChessGame chessGame, int alpha = INT_MIN, int beta = INT_MAX); 
};
