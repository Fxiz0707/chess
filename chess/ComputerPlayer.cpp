#include "ComputerPlayer.h"

static int count = 0; 

int ComputerPlayer::minimax(int depth, CurrentGameState state, std::array<char, 64> board, int alpha, int beta)
{
	if (depth == 0) // static analysis 
	{
		int output = 0;
		int knightCount = 0;

		for (char possiblePiece : board)
		{
			switch (possiblePiece)
			{
			case('P'):
				output -= 10;
				break;
			case('N'):
				knightCount++;
				output -= 30;
				break;
			case('B'):
				output -= 30;
				break;
			case('R'):
				output -= 60;
				break;
			case('Q'):
				output -= 90;
				break;
			case('K'):
				output -= 900;
				break;
			case('p'):
				output += 10;
				break;
			case('n'):
				output += 30;
				break;
			case('b'):
				output += 30;
				break;
			case('r'):
				output += 60;
				break;
			case('q'):
				output += 90;
				break;
			case('k'):
				output += 900;
				break;
			default:
				output += 0;
			}
		}
		count++;
		
		if (count == 2117)
		{
			int eh = 3; 
		}

		return output; 
	}

	if (state.currentSide == 0)  // white turn 
	{
		int currentMax = INT_MIN; 
		state.currentSide = 1; // switching sides, assuming that the other person makes their OPTIMAL move 
		for (std::array<char, 64>& possibleBoard : ChessGame::everyPosition(state, board)) // whites turn, white goes through every single position that black can make from here 
		{
			int eval = minimax(depth - 1, state, possibleBoard, alpha, beta); // evaluates each one further 
			currentMax = std::max(currentMax, eval);  
			alpha = std::max(alpha, eval); 
			//currentMax = std::max(currentMax, minimax(depth - 1, state, possibleBoard, alpha, beta)); 
			//alpha = std::max(alpha, currentMax); // what white is guaranteed
			if (alpha >= beta) break; 
		}
		return currentMax; 
	}
	else
	{
		int currentMin = INT_MAX; 
		state.currentSide = 0; 
		for (std::array<char, 64>& possibleBoard : ChessGame::everyPosition(state, board)) // goes through every single position that white can make 
		{
			int eval = minimax(depth - 1, state, possibleBoard, alpha, beta); // evaluates the position 
			currentMin = std::min(currentMin, eval); 
			beta = std::min(beta, currentMin); 
		//	currentMin = std::min(currentMin, minimax(depth - 1, state, possibleBoard, alpha, beta));
		///*	std::cout << currentMin << std::endl; */
		//	beta = std::min(beta, currentMin); 
			if (alpha >= beta) break; 
		}
		return currentMin; 
	}

	return 0; 
}