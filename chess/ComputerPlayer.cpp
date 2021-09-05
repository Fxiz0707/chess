#include "ComputerPlayer.h"

// testing
#include <iostream>

void ComputerPlayer::do_computer_move(int depth, ChessGame& chessGame)
{
	assert(chessGame.get_current_side() == SIDE::BLACK);

	int minEval = INT_MAX;

	sf::Vector2i posOfMovingPiece;
	sf::Vector2i posPieceIsMovingTo;

	ChessGame winningGame;
	for (auto possibility : gen(chessGame))
	{
		int eval = minimax(depth - 1, possibility);
		if (eval < minEval)
		{
			minEval = eval;
			winningGame = possibility;
		}
	}
	chessGame = winningGame; 
}

int ComputerPlayer::static_eval(const std::array<char, 64>& gameBoard)
{
	int eval = 0;

	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			switch (gameBoard[i + 8 * j])
			{
			case 'r':
				eval += 50;
				break;
			case('R'):
				eval -= 50;
				break;
			case('n'):
				eval += 30;
				break;
			case('N'):
				eval -= 30;
				break;
			case('b'):
				eval += 30;
				break;
			case('B'):
				eval -= 30;
				break;
			case('q'):
				eval += 90;
				break;
			case('Q'):
				eval -= 90;
				break;
			case('k'):
				eval += 10000;
				break;
			case('K'):
				eval -= 10000;
				break;
			case('p'):
				eval += 10;
				break;
			case('P'):
				eval -= 10;
				break;
			default:
				eval += 0;
			}
		}
	}

	return eval;
}

std::vector<ChessGame> ComputerPlayer::gen(const ChessGame& chessGame)
{
	std::vector<ChessGame> allPossibilities;

	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (chessGame.get_game_board()[i + 8 * j] != '#')
			{
				// this if statement ensures that only possibilities that are reachable by the CURRENT SIDE, are explored 
				if (ChessLogic::get_side(chessGame.get_game_board()[i + 8 * j]) == chessGame.get_current_side())
				{
					std::vector<sf::Vector2i> possiblePositions = chessGame.get_available_positions({ i, j });

					for (sf::Vector2i possiblePosition : possiblePositions)
					{
						ChessGame possibleGame = chessGame; // expensive copy 
						if (possibleGame.move({ i, j }, possiblePosition))
						{
							allPossibilities.push_back(possibleGame); // expensive copy - again  
						};

					}
				}
			}
		}
	}

	return allPossibilities;
}

int ComputerPlayer::minimax(int depth, ChessGame chessGame, int alpha, int beta)
{
	if (depth == 0) return static_eval(chessGame.get_game_board());

	if (chessGame.get_current_side() == SIDE::WHITE)
	{
		int maxEval = INT_MIN;
		for (auto possibility : gen(chessGame))
		{
			int eval = minimax(depth - 1, possibility, alpha, beta);
			maxEval = std::max(maxEval, eval);
			alpha = std::max(alpha, eval);

			if (alpha > beta) break;
		}
		return maxEval;
	}
	else if (chessGame.get_current_side() == SIDE::BLACK)
	{
		int minEval = INT_MAX;
		for (auto possibility : gen(chessGame))
		{
			int eval = minimax(depth - 1, possibility, alpha, beta);
			minEval = std::min(minEval, eval);
			beta = std::min(beta, eval);
			if (alpha > beta) break;
		}
		return minEval;
	}

	assert(false);
	return 0;
}
