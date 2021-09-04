#include "ChessGame.h"

std::vector<sf::Vector2i> ChessGame::availablePositions(sf::Vector2i position, std::array<char, 64>& const board)
{
	std::vector<sf::Vector2i> availablePositions; 
	
	char piece = board[position.x + 8 * position.y]; 

	if (piece == '#') return availablePositions; 

	if (piece == 'r' || piece == 'R') 
	{
		sf::Vector2i above = { position.x, position.y - 1 }; 
		sf::Vector2i below = { position.x, position.y + 1 }; 
		sf::Vector2i right = { position.x + 1, position.y }; 
		sf::Vector2i left = { position.x - 1, position.y }; 

		while (positionIsInBoard(above))
		{
			int index = above.x + 8 * above.y; 

			if (board[index] != '#')
			{
				if (getSide(board[index]) != getSide(piece)) // meaning it is a piece of the opposite side that we can take 
				{
					availablePositions.push_back(above); 
				}
				break; 
			}
			else
			{
				availablePositions.push_back(above);
			}
			
			above = { above.x, above.y - 1 }; 

		}
		while (positionIsInBoard(below))
		{
			int index = below.x + 8 * below.y; 

			if (board[index] != '#')
			{
				if (getSide(board[index]) != getSide(piece)) // meaning it is a piece of the opposite side that we can take 
				{
					availablePositions.push_back(below);
				}
				break; 
			}
			else
			{
				availablePositions.push_back(below); 
			}

			below = { below.x, below.y + 1 }; 
		}
		while (positionIsInBoard(right))
		{
			int index = right.x + 8 * right.y; 

			if (board[index] != '#')
			{
				if (getSide(board[index]) != getSide(piece)) // meaning it is a piece of the opposite side that we can take 
				{
					availablePositions.push_back(right);
				}
				break; 
			}
			else
			{
				availablePositions.push_back(right); 
			}
			right = { right.x + 1, right.y }; 
		}
		while (positionIsInBoard(left))
		{
			int index = left.x + 8 * left.y; 

			if (board[index] != '#')
			{
				if (getSide(board[index]) != getSide(piece)) // meaning it is a piece of the opposite side that we can take 
				{
					availablePositions.push_back(left);
				}
				break; 
			}
			else
			{
				availablePositions.push_back(left); 
			}
			left = { left.x - 1, left.y }; 
		}

	} // rook 
	
	else if (piece == 'n' || piece == 'N')
	{
		//RHS 
		sf::Vector2i pos1 = { position.x + 1, position.y - 2 }; // top 
		sf::Vector2i pos2 = { position.x + 2, position.y - 1 }; 
		
		sf::Vector2i pos3 = { position.x + 1, position.y + 2 }; // bottom 
		sf::Vector2i pos4 = { position.x + 2, position.y + 1 }; 

		//LHS
		sf::Vector2i pos5 = { position.x - 1, position.y - 2 }; // top 
		sf::Vector2i pos6 = { position.x - 2, position.y - 1 }; 
		
		sf::Vector2i pos7 = { position.x - 2, position.y + 1 }; // bottom
		sf::Vector2i pos8 = { position.x - 1, position.y + 2 }; 

		if (positionIsInBoard(pos1))
		{
			if ((board[pos1.x + 8 * pos1.y] == '#') || (getSide(board[pos1.x + 8 * pos1.y]) != getSide(piece))) availablePositions.push_back(pos1);
		}
		if (positionIsInBoard(pos2))
		{
			if ((board[pos2.x + 8 * pos2.y] == '#') || (getSide(board[pos2.x + 8 * pos2.y]) != getSide(piece))) availablePositions.push_back(pos2);
		}
		if (positionIsInBoard(pos3))
		{
			if ((board[pos3.x + 8 * pos3.y] == '#') || (getSide(board[pos3.x + 8 * pos3.y]) != getSide(piece))) availablePositions.push_back(pos3);
		}
		if (positionIsInBoard(pos4))
		{
			if ((board[pos4.x + 8 * pos4.y] == '#') || (getSide(board[pos4.x + 8 * pos4.y]) != getSide(piece))) availablePositions.push_back(pos4);
		}
		if (positionIsInBoard(pos5))
		{
			if ((board[pos5.x + 8 * pos5.y] == '#') || (getSide(board[pos5.x + 8 * pos5.y]) != getSide(piece))) availablePositions.push_back(pos5);
		}
		if (positionIsInBoard(pos6))
		{
			if ((board[pos6.x + 8 * pos6.y] == '#') || (getSide(board[pos6.x + 8 * pos6.y]) != getSide(piece))) availablePositions.push_back(pos6);
		}
		if (positionIsInBoard(pos7))
		{
			if ((board[pos7.x + 8 * pos7.y] == '#') || (getSide(board[pos7.x + 8 * pos7.y]) != getSide(piece))) availablePositions.push_back(pos7);
		}
		if (positionIsInBoard(pos8))
		{
			if ((board[pos8.x + 8 * pos8.y] == '#') || (getSide(board[pos8.x + 8 * pos8.y]) != getSide(piece))) availablePositions.push_back(pos8);
		}

	} // the commented directions dont make sense in practicality  // knight

	else if (piece == 'b' || piece == 'B')
	{
		sf::Vector2i topRight = { position.x + 1, position.y - 1 }; 
		sf::Vector2i topLeft = { position.x - 1, position.y - 1 }; 
		sf::Vector2i bottomRight = { position.x + 1, position.y + 1 }; 
		sf::Vector2i bottomLeft = { position.x - 1, position.y + 1 }; 

		while (positionIsInBoard(topRight))
		{
			int index = topRight.x + 8 * topRight.y;

			if (board[index] != '#')
			{
				if (getSide(board[index]) != getSide(piece))
				{
					availablePositions.push_back(topRight); 
				}
				break; 
			}
			else
			{
				availablePositions.push_back(topRight); 
			}
			
			topRight = { topRight.x + 1, topRight.y - 1 }; 
		}
		while (positionIsInBoard(topLeft))
		{
			int index = topLeft.x + 8 * topLeft.y;

			if (board[index] != '#')
			{
				if (getSide(board[index]) != getSide(piece))
				{
					availablePositions.push_back(topLeft); 
				}
				break; 
			}
			else
			{
				availablePositions.push_back(topLeft); 
			}
			
			topLeft = { topLeft.x - 1, topLeft.y - 1 }; 
		}
		while (positionIsInBoard(bottomRight))
		{
			int index = bottomRight.x + 8 * bottomRight.y;

			if (board[index] != '#')
			{
				
				if (getSide(board[index]) != getSide(piece))
				{
					availablePositions.push_back(bottomRight); 
				}
				break; 
			}
			else
			{
				availablePositions.push_back(bottomRight); 
			}

			bottomRight = { bottomRight.x + 1, bottomRight.y + 1 }; 
		}
		while (positionIsInBoard(bottomLeft))
		{
			int index = bottomLeft.x + 8 * bottomLeft.y;

			if (board[index] != '#')
			{
				if (getSide(board[index]) != getSide(piece))
				{
					availablePositions.push_back(bottomLeft); 
				}
				break; 
			}
			else
			{
				availablePositions.push_back(bottomLeft); 
			}

			bottomLeft = { bottomLeft.x - 1, bottomLeft.y + 1 }; 
		}
	} 

	else if (piece == 'q' || piece == 'Q')
	{
		// SAME AS ROOK 
		sf::Vector2i above = { position.x, position.y - 1 };
		sf::Vector2i below = { position.x, position.y + 1 };
		sf::Vector2i right = { position.x + 1, position.y };
		sf::Vector2i left = { position.x - 1, position.y };

		while (positionIsInBoard(above))
		{
		
			int index = above.x + 8 * above.y;

			if (board[index] != '#')
			{
				if (getSide(board[index]) != getSide(piece)) // meaning it is a piece of the opposite side that we can take 
				{
					availablePositions.push_back(above);
				}
				break;
			}
			else
			{
				availablePositions.push_back(above);
			}

			above = { above.x, above.y - 1 };

		}
		while (positionIsInBoard(below))
		{
			int index = below.x + 8 * below.y;

			if (board[index] != '#')
			{
				if (getSide(board[index]) != getSide(piece)) // meaning it is a piece of the opposite side that we can take 
				{
					availablePositions.push_back(below);
				}
				break;
			}
			else
			{
				availablePositions.push_back(below);
			}

			below = { below.x, below.y + 1 };
		}
		while (positionIsInBoard(right))
		{
			int index = right.x + 8 * right.y;

			if (board[index] != '#')
			{
				if (getSide(board[index]) != getSide(piece)) // meaning it is a piece of the opposite side that we can take 
				{
					availablePositions.push_back(right);
				}
				break;
			}
			else
			{
				availablePositions.push_back(right);
			}
			right = { right.x + 1, right.y };
		}
		while (positionIsInBoard(left))
		{
			int index = left.x + 8 * left.y;

			if (board[index] != '#')
			{
				if (getSide(board[index]) != getSide(piece)) // meaning it is a piece of the opposite side that we can take 
				{
					availablePositions.push_back(left);
				}
				break;
			}
			else
			{
				availablePositions.push_back(left);
			}
			left = { left.x - 1, left.y };
		}

		// Same as bishop 
		sf::Vector2i topRight = { position.x + 1, position.y - 1 };
		sf::Vector2i topLeft = { position.x - 1, position.y - 1 };
		sf::Vector2i bottomRight = { position.x + 1, position.y + 1 };
		sf::Vector2i bottomLeft = { position.x - 1, position.y + 1 };

		while (positionIsInBoard(topRight))
		{
			int index = topRight.x + 8 * topRight.y;

			if (board[index] != '#')
			{
				if (getSide(board[index]) != getSide(piece))
				{
					availablePositions.push_back(topRight);
				}
				break;
			}
			else
			{
				availablePositions.push_back(topRight);
			}

			topRight = { topRight.x + 1, topRight.y - 1 };
		}
		while (positionIsInBoard(topLeft))
		{
			int index = topLeft.x + 8 * topLeft.y;

			if (board[index] != '#')
			{
				if (getSide(board[index]) != getSide(piece))
				{
					availablePositions.push_back(topLeft);
				}
				break;
			}
			else
			{
				availablePositions.push_back(topLeft);
			}

			topLeft = { topLeft.x - 1, topLeft.y - 1 };
		}
		while (positionIsInBoard(bottomRight))
		{
			int index = bottomRight.x + 8 * bottomRight.y;

			if (board[index] != '#')
			{

				if (getSide(board[index]) != getSide(piece))
				{
					availablePositions.push_back(bottomRight);
				}
				break;
			}
			else
			{
				availablePositions.push_back(bottomRight);
			}

			bottomRight = { bottomRight.x + 1, bottomRight.y + 1 };
		}
		while (positionIsInBoard(bottomLeft))
		{
			int index = bottomLeft.x + 8 * bottomLeft.y;

			if (board[index] != '#')
			{
				if (getSide(board[index]) != getSide(piece))
				{
					availablePositions.push_back(bottomLeft);
				}
				break;
			}
			else
			{
				availablePositions.push_back(bottomLeft);
			}

			bottomLeft = { bottomLeft.x - 1, bottomLeft.y + 1 };
		}

	}

	else if (piece == 'k' || piece == 'K')
	{
		sf::Vector2i top = { position.x, position.y - 1 };
		sf::Vector2i right = { position.x + 1, position.y }; 
		sf::Vector2i bottom = { position.x, position.y + 1 };
		sf::Vector2i left = { position.x - 1, position.y }; 

		if (positionIsInBoard(top))
		{
			if ((board[top.x + 8 * top.y] == '#') || (getSide(board[top.x + 8 * top.y]) != getSide(piece))) availablePositions.push_back(top);
		}
		if (positionIsInBoard(right))
		{
			if ((board[right.x + 8 * right.y] == '#') || (getSide(board[right.x + 8 * right.y]) != getSide(piece))) availablePositions.push_back(right);
		}
		if (positionIsInBoard(bottom))
		{
			if ((board[bottom.x + 8 * bottom.y] == '#') || (getSide(board[bottom.x + 8 * bottom.y]) != getSide(piece))) availablePositions.push_back(bottom);
		}
		if (positionIsInBoard(left))
		{
			if ((board[left.x + 8 * left.y] == '#') || (getSide(board[left.x + 8 * left.y]) != getSide(piece))) availablePositions.push_back(left);
		}
	
		sf::Vector2i topRight = { position.x + 1, position.y - 1 }; 
		sf::Vector2i topLeft = { position.x - 1, position.y - 1 }; 
		sf::Vector2i bottomRight = {position.x + 1, position.y + 1};
		sf::Vector2i bottomLeft = { position.x - 1, position.y + 1 }; 

		if (positionIsInBoard(topRight))
		{
			if ((board[topRight.x + 8 * topRight.y] == '#') || (getSide(board[topRight.x + 8 * topRight.y]) != getSide(piece))) availablePositions.push_back(topRight);
		}
		if (positionIsInBoard(topLeft))
		{
			if ((board[topLeft.x + 8 * topLeft.y] == '#') || (getSide(board[topLeft.x + 8 * topLeft.y]) != getSide(piece))) availablePositions.push_back(topLeft);
		}
		if (positionIsInBoard(bottomRight))
		{
			if ((board[bottomRight.x + 8 * bottomRight.y] == '#') || (getSide(board[bottomRight.x + 8 * bottomRight.y]) != getSide(piece))) availablePositions.push_back(bottomRight);
		}
		if (positionIsInBoard(bottomLeft))
		{
			if ((board[bottomLeft.x + 8 * bottomLeft.y] == '#') || (getSide(board[bottomLeft.x + 8 * bottomLeft.y]) != getSide(piece))) availablePositions.push_back(bottomLeft);
		}
	}  

	else if (piece == 'p' || piece == 'P')
	{
		if (getSide(piece) == 0) // white pawn 
		{
			sf::Vector2i above = { position.x, position.y - 1 };
			sf::Vector2i right = { position.x + 1, position.y - 1 };
			sf::Vector2i left = { position.x - 1, position.y - 1 };

			if (positionIsInBoard(above))
			{
				if (board[above.x + 8 * above.y] == '#')
				{
					availablePositions.push_back(above);
				}
			}
			if (positionIsInBoard(right))
			{
				if (board[right.x + 8 * right.y] != '#')
				{
					if (getSide(board[right.x + 8 * right.y]) == 1) // the piece on the left must be black 
					{
						availablePositions.push_back(right);
					}
				}
			}
			if (positionIsInBoard(left))
			{
				if (board[left.x + 8 * left.y] != '#')
				{
					if (getSide(board[left.x + 8 * left.y]) == 1) // the piece on the left must be black 
					{
						availablePositions.push_back(left);
					}
				}
			}

			if (position.y == 6) // it is the pawns first move 
			{
				if (board[above.x + 8 * above.y] == '#')
				{
					sf::Vector2i aboveAbove = { above.x, above.y - 1 }; 
					if (board[aboveAbove.x + 8 * aboveAbove.y] == '#')
					{
						availablePositions.push_back(aboveAbove); 
					}
				}
			}
			
		}
		else // black pawn 
		{

			sf::Vector2i above = { position.x, position.y + 1 };
			sf::Vector2i right = { position.x + 1, position.y + 1 }; 
			sf::Vector2i left = { position.x - 1, position.y + 1 }; 

			if (positionIsInBoard(above))
			{
				if (board[above.x + 8 * above.y] == '#')
				{
					availablePositions.push_back(above);
				}
			}
			if (positionIsInBoard(right))
			{
				if (board[right.x + 8 * right.y] != '#')
				{
					if (getSide(board[right.x + 8 * right.y]) == 0) // other piece must be white 
					{
						availablePositions.push_back(right);
					}
				}
			}
			if (positionIsInBoard(left))
			{
				if (board[left.x + 8 * left.y] != '#')
				{
					if (getSide(board[left.x + 8 * left.y]) == 0) // other iece must be white 
					{
						availablePositions.push_back(left);
					}
				}
			}
			
			if (position.y == 1) // it is the pawns first move
			{
				if (board[above.x + 8 * above.y] == '#')
				{
					sf::Vector2i aboveAbove = { above.x, above.y + 1 };
					if (board[aboveAbove.x + 8 * aboveAbove.y] == '#') 
					{
						availablePositions.push_back(aboveAbove);
					}
				}
			}
		}
	} 

	return availablePositions;
}

std::vector<std::array<char, 64>> ChessGame::everyPosition(CurrentGameState state, std::array<char, 64>& const board)
{
	std::vector<std::array<char, 64>> output; 

	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++) 
		{
			if (board[i + 8 * j] != '#')
			{
				if (getSide(board[i + 8 * j]) == state.currentSide)
				{
					for (sf::Vector2i pos : ChessGame::availablePositions({ i, j }, board))
					{
						std::array<char, 64> testBoard = board;

						CurrentGameState newState = state; 

						if (ChessGame::move(newState, { i, j }, pos, testBoard))
						{
							output.push_back(testBoard);
						}
					}

					for (sf::Vector2i pos : ChessGame::castlingPositions(state, { i, j }, board))
					{
						std::array<char, 64> testBoard = board; 

						CurrentGameState newState = state; 

						ChessGame::move(newState, {i, j}, pos, testBoard);  // no testing needs to be done here 
						output.push_back(testBoard); 
					}
				}
			}
		}
	}

	return output; 
}

void ChessGame::everyPositionRecursive(int depth, CurrentGameState state, std::array<char, 64>& const board)
{
	if (depth == 0) return;
	
	std::vector<std::array<char, 64>> output;
	std::vector<CurrentGameState> states; 

	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (board[i + 8 * j] != '#')
			{
				if (true)
				{
					for (sf::Vector2i pos : ChessGame::availablePositions({ i, j }, board))
					{
						std::array<char, 64> testBoard = board;

						CurrentGameState newState = state; 

						if (ChessGame::move(newState, { i, j }, pos, testBoard))
						{
							output.push_back(testBoard);
							states.push_back(newState); 
						}
					}

					for (sf::Vector2i pos : ChessGame::castlingPositions(state, { i, j }, board))
					{
						CurrentGameState newState = state; 

						std::array<char, 64> testBoard = board;
						ChessGame::move(newState, { i, j }, pos, testBoard);  // no testing needs to be done here 
						
						output.push_back(testBoard);
						states.push_back(newState); 
					}
				}
			}
		}
	}
	
	std::cout << "Size: " << output.size() << std::endl; 

	for (int i = 0; i < output.size(); i++)
	{
		everyPositionRecursive(depth - 1, states[i], output[i]); 
	}

}

bool ChessGame::isCheck(bool side, std::array<char, 64>& const board)
{
	std::vector<sf::Vector2i> positions; 
	sf::Vector2i kingPosition; 
	for (int k = 0; k < 8; k++) // y value
	{
		for (int i = 0; i < 8; i++) // x value 
		{
			int index = i + 8 * k; 
			if (board[index] != '#') // going through every piece in the board
			{
				if (getSide(board[index]) != side) // for all of the pieces on the opposite side
				{
					for (sf::Vector2i position : availablePositions({ i, k }, board)) 
					{
						positions.push_back(position); // adding all available positions from the opposite side into a vector 
					}
				}
				if (board[index] == getKing(side)) // finding the king's position, whose safety is in question 
				{
					kingPosition = { i, k };
				}
			}
		}
	}

	auto it = std::find(positions.begin(), positions.end(), kingPosition); // checking if the king is in danger 
	if (it != positions.end()) 
	{
		return true; 
	}
	
	return false; 
}

bool ChessGame::isCheckMate(bool side, std::array<char, 64>& const board)
{
	if (!isCheck(side, board)) return false; // will later need to add the ability to have a stalemate
	 
	// finding the position of the king, whose safety is in question 
	sf::Vector2i kingPosition; 
	for (int i = 0; i < 64; i++)
	{
		if (board[i] == getKing(side))
		{
			int x = i % 8; 
			int y = (i - x) / 8;
			
			kingPosition = { x, y }; 
			break; 
		}
	}

	// checking if the king can move to a safe space
	std::vector<sf::Vector2i> kingPossiblePositions = availablePositions(kingPosition, board); 

	for (auto pos : kingPossiblePositions)
	{
		std::cout << "X: " << pos.x << " Y: " << pos.y << std::endl; 
	}

	for (sf::Vector2i newPos : kingPossiblePositions)
	{
		std::array<char, 64> testBoard = board; 
		testBoard[kingPosition.x + 8 * kingPosition.y] = '#';
		testBoard[newPos.x + 8 * newPos.y] = board[kingPosition.x + 8 * kingPosition.y]; 

		if (!isCheck(side, testBoard)) return false;
	}

	// checking if the checkmate can be blocked or an attacking piece taken 
	//                        START     NEW POSSIBLE POSITION
	std::vector<std::pair<sf::Vector2i, sf::Vector2i>> allPositions; // gets all the positions for every piece which belongs to the same side as the 'side' parameter 
	for (int i = 0; i < 64; i++)
	{
		if (board[i] != '#')
		{
			if (getSide(board[i]) == side) // we use it to see if a piece can be used to block the checkmate 
			{
				int x = i % 8;
				int y = (i - x) / 8;

				std::vector<sf::Vector2i> piecePossiblePositions = availablePositions({ x, y }, board);
				for (sf::Vector2i possiblePos : piecePossiblePositions)
				{
					allPositions.push_back({ { x, y }, possiblePos });
				}
			}
		}
	}

	for (auto newPos : allPositions)
	{
		std::array<char, 64> testBoard = board; 
		testBoard[newPos.first.x + 8 * newPos.first.y] = board[newPos.second.x + 8 * newPos.second.y]; 
		testBoard[newPos.second.x + 8 * newPos.second.y] = board[newPos.first.x + 8 * newPos.first.y]; 

		if (!isCheck(side, testBoard)) return false; 
	}

	return true; 
}

bool ChessGame::isStaleMate(bool side, std::array<char, 64>& const board)
{
	return false; 
}

bool ChessGame::move(CurrentGameState& gameState, sf::Vector2i start, sf::Vector2i end, std::array<char, 64>& board)
{
	// ensures only the side, whose turn it is can make a move 
	if (gameState.currentSide != getSide(board[start.x + 8 * start.y]))
	{
		return false;
	}

	if (gameState.whiteWon || gameState.blackWon) return false;  // a lost game cannot be continued from 


	// check if the user is castling 
	std::vector<sf::Vector2i> positionsToCastle = castlingPositions(gameState, start, board); 
	auto it_1 = std::find(positionsToCastle.begin(), positionsToCastle.end(), end); 
	if (it_1 != positionsToCastle.end())
	{
		// the user is castling 
		board[start.x + 8 * start.y] = '#'; 

		if (gameState.currentSide == 0) // white is castling 
		{
			gameState.whiteKingMoved = true; 

			board[end.x + 8 * end.y] = 'k'; 
			if (end.x > start.x) // castling right 
			{
				gameState.whiteRightRookMoved = true; 
				board[end.x - 1 + 8 * end.y] = 'r'; 
				board[end.x + 1 + 8 * end.y] = '#'; // removing the rook 
			}
			else
			{
				gameState.whiteLeftRookMoved = true; 
				board[end.x + 1 + 8 * end.y] = 'r'; 
				board[end.x - 1 + 8 * end.y] = '#'; // removing the rook 
			}
		}
		else if (gameState.currentSide == 1) // black is castling 
		{
			gameState.blackKingMoved = true; 
			board[end.x + 8 * end.y] = 'K'; 
			if (end.x > start.x) // castling right 
			{
				gameState.blackRightRookMoved = true; 
				board[end.x - 1 + 8 * end.y] = 'R'; 
				board[end.x + 1 + 8 * end.y] = '#'; 
			}
			else // catling left 
			{
				gameState.blackLeftRookMoved = true; 
				board[end.x + 1 + 8 * end.y] = 'R'; 
				board[end.x - 1 + 8 * end.y] = '#'; 
			}
		}

		return true; 
	}

	std::vector<sf::Vector2i> positions = availablePositions(start, board);
	auto it_2 = std::find(positions.begin(), positions.end(), end);
	
	// checking if the attempted move is possible 
	if (it_2 != positions.end()) 
	{
		std::array<char, 64> testBoard = board; 
		testBoard[start.x + 8 * start.y] = '#'; 
		testBoard[end.x + 8 * end.y] = board[start.x + 8 * start.y]; 
		
		// ensures that the new move does not put the moving player into check 
		if (!isCheck(getSide(board[start.x + 8 * start.y]), testBoard))
		{
			// executes move, updating our global gameBoard 

			board[end.x + 8 * end.y] = board[start.x + 8 * start.y]; 
			board[start.x + 8 * start.y] = '#'; 
		
			// checking if a king or rook are moved 
			if (board[end.x + 8 * end.y] == 'r' && (start.x == 7)) gameState.whiteRightRookMoved = true; 
			if (board[end.x + 8 * end.y] == 'r' && (start.x == 0)) gameState.whiteLeftRookMoved = true; 
			if (board[end.x + 8 * end.y] == 'R' && (start.x == 7)) gameState.blackRightRookMoved = true; 
			if (board[end.x + 8 * end.y] == 'R' && (start.x == 0)) gameState.blackLeftRookMoved = true; 
			if (board[end.x + 8 * end.y] == 'k') gameState.whiteKingMoved = true; 
			if (board[end.x + 8 * end.y] == 'K') gameState.blackKingMoved = true; 


			if (ChessGame::shouldPawnBeQueen(end, board))	// we use end because the piece has been moved 
			{
				if (board[end.x + 8 * end.y] == 'p')
				{
					board[end.x + 8 * end.y] = 'q'; 
				}
				else
				{
					board[end.x + 8 * end.y] = 'Q'; 
				}
			}

			return true; 
		}
	}

	return false; 
}

std::vector<sf::Vector2i> ChessGame::castlingPositions(CurrentGameState& const gameState, sf::Vector2i start, std::array<char, 64>& board)
{
	std::vector<sf::Vector2i> output{};

	// castling cannot happen while the king is in check 
	if (isCheck(gameState.currentSide, board)) return output; 

	if (board[start.x + 8 * start.y] == 'k')
	{
		if (!gameState.whiteKingMoved)
		{
			// looking at right rook
			if (!gameState.whiteRightRookMoved)
			{
				if (board[5 + 8 * 7] == '#' && board[6 + 8 * 7] == '#') // ensuring that the right of the king is empty 
				{
					// ensuring that the king is not moving across check or end up in check 
					bool kingMovesAcrossCheck = false; 

					std::array<char, 64> testBoard = board; 
					testBoard[start.x + 8 * start.y] = '#'; 
					testBoard[5 + 8 * 7] = 'k'; 
					if (isCheck(gameState.currentSide, testBoard)) kingMovesAcrossCheck = true;
					
					testBoard[5 + 8 * 7] = '#'; 
					testBoard[6 + 8 * 7] = 'k'; 
					if (isCheck(gameState.currentSide, testBoard)) kingMovesAcrossCheck = true; 

					if (!kingMovesAcrossCheck)
					{
						output.push_back({ 6, 7 });
					}

				}
			}
			// looking at left rook 
			if (!gameState.whiteLeftRookMoved)
			{
				if (board[1 + 8 * 7] == '#' && board[2 + 8 * 7] == '#' && board[3 + 8 * 7] == '#')
				{
					// ensures that the king does not move across check or end up in check 
					bool kingMovesAcrossCheck = false; 

					std::array<char, 64> testBoard = board; 
					testBoard[start.x + 8 * start.y] = '#'; 
					testBoard[1 + 8 * 7] = 'k'; 
					if (isCheck(gameState.currentSide, testBoard)) kingMovesAcrossCheck = true; 

					testBoard[1 + 8 * 7] = '#'; 
					testBoard[2 + 8 * 7] = 'k'; 
					if (isCheck(gameState.currentSide, testBoard)) kingMovesAcrossCheck = true; 

					testBoard[2 + 8 * 7] = '#'; 
					testBoard[3 + 8 * 7] = 'k'; 
					if (isCheck(gameState.currentSide, testBoard)) kingMovesAcrossCheck = true; 

					if (!kingMovesAcrossCheck)
					{
						output.push_back({ 1, 7 }); 
					}
				}
			}

		}
	}
	else if (board[start.x + 8 * start.y] == 'K')
	{
		if (!gameState.blackKingMoved)
		{
			if (!gameState.blackRightRookMoved)
			{
				if (board[5] == '#' && board[6] == '#')
				{
					// ensuring that the king does not move across check or end up in check 
					bool kingMovesAcrossCheck = false; 

					std::array<char, 64> testBoard = board; 
					testBoard[start.x + 8 * start.y] = '#';  // 8 * start.y is redundant 
					testBoard[5] = 'K'; 
					if (isCheck(gameState.currentSide, testBoard)) kingMovesAcrossCheck = true; 

					testBoard[5] = '#'; 
					testBoard[6] = 'K'; 
					if (isCheck(gameState.currentSide, testBoard)) kingMovesAcrossCheck = true; 

					if (!kingMovesAcrossCheck)
					{
						output.push_back({6, 0});
					}

				}
			}
			if (!gameState.blackLeftRookMoved)
			{
				if (board[1] == '#' && board[2] == '#' && board[3] == '#')
				{
					bool kingMovesAcrossCheck = false; 

					std::array<char, 64> testBoard = board; 
					testBoard[start.x + 8 * start.y] = '#'; 
					testBoard[1] = 'K'; 
					if (isCheck(gameState.currentSide, testBoard)) kingMovesAcrossCheck = true; 

					testBoard[1] = '#'; 
					testBoard[2] = 'K'; 
					if (isCheck(gameState.currentSide, testBoard)) kingMovesAcrossCheck = true; 

					testBoard[2] = '#'; 
					testBoard[3] = 'K'; 
					if (isCheck(gameState.currentSide, testBoard)) kingMovesAcrossCheck = true; 

					if (!kingMovesAcrossCheck)
					{
						output.push_back({ 1, 0 }); 
					}

				}
			}
		}
	}
	return output; 
}

bool ChessGame::getSide(char piece)
{

	if (piece == '#')
	{
		int eh = 3; 
	}

	assert(piece != '#'); 
	// 97 is 'a' in ASCII, while '65' is A 
	if (int(piece) >= 97) return 0; 
	return 1; 
}

char ChessGame::getKing(int side)
{
	if (side == 0) // white 
	{
		return 'k'; 
	}
	else // black 
	{
		return 'K'; 
	}
}

bool ChessGame::positionIsInBoard(sf::Vector2i pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.x > 7 || pos.y > 7) return false; 
	return true; 
}

bool ChessGame::shouldPawnBeQueen(sf::Vector2i pos, std::array<char, 64>& const board)
{
	int index = pos.x + 8 * pos.y; 
	
	if (board[index] != 'p' && board[index] != 'P') return false; 

	if (getSide(board[index]) == 0) // check if white pawn is on black side
	{
		if (pos.y == 0) return true; 
	}
	else
	{
		if (pos.y == 7) return true; 
	}

	return false; 
}
