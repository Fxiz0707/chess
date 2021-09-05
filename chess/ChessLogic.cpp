#include "ChessLogic.h"

std::vector<sf::Vector2i> ChessLogic::available_positions(sf::Vector2i pos, const std::array<char, 64>& board)
{
	std::vector<sf::Vector2i> available_positions; 
	
	char piece = board[pos.x + 8 * pos.y]; 

	if (piece == '#') return available_positions; 

	if (piece == 'r' || piece == 'R') 
	{
		return get_rook_positions(pos, board); 
	} 
	
	else if (piece == 'n' || piece == 'N')
	{
		return get_knight_positions(pos, board); 
	} 

	else if (piece == 'b' || piece == 'B')
	{
		return get_bishop_positions(pos, board); 
	} 

	else if (piece == 'q' || piece == 'Q')
	{
		return get_queen_positions(pos, board); 
	}

	else if (piece == 'k' || piece == 'K')
	{
		return get_king_positions(pos, board); 
	}  

	else if (piece == 'p' || piece == 'P')
	{
		return get_pawn_positions(pos, board); 
	} 

	return available_positions;
}

bool ChessLogic::is_check(SIDE side, const std::array<char, 64>& board)
{
	std::vector<sf::Vector2i> positions;
	sf::Vector2i kingPosition;

	for (int k = 0; k < 8; k++) // y value
	{
		for (int i = 0; i < 8; i++) // x value 
		{
			const int index = i + 8 * k;
			if (board[index] != '#') // going through every piece in the board
			{
				if (get_side(board[index]) != side) // for all of the pieces on the opposite side
				{
					for (sf::Vector2i position : available_positions({ i, k }, board))
					{
						positions.push_back(position); // adding all available positions from the opposite side into a vector 
					}
				}
				if (board[index] == get_king(side)) // finding the king's position, whose safety is in question 
				{
					kingPosition = { i, k };
				}
			}
		}
	}

	const auto it = std::find(positions.begin(), positions.end(), kingPosition); // checking if the king is in danger 
	if (it != positions.end())
	{
		return true;
	}

	return false;
}

bool ChessLogic::is_checkmate(SIDE side, const std::array<char, 64>& board)  
{
	if (!is_check(side, board)) return false; // will later need to add the ability to have a stalemate
	 
	// finding the position of the king, whose safety is in question 
	sf::Vector2i kingPosition; 
	for (int i = 0; i < 64; i++)
	{
		if (board[i] == get_king(side))
		{
			int x = i % 8; 
			int y = (i - x) / 8;
			
			kingPosition = { x, y }; 
			break; 
		}
	}

	// checking if the king can move to a safe space
	const std::vector<sf::Vector2i> kingPossiblePositions = available_positions(kingPosition, board);

	for (sf::Vector2i newPos : kingPossiblePositions)
	{
		std::array<char, 64> testBoard = board; 
		testBoard[kingPosition.x + 8 * kingPosition.y] = '#';
		testBoard[newPos.x + 8 * newPos.y] = board[kingPosition.x + 8 * kingPosition.y]; 

		if (!is_check(side, testBoard)) return false;
	}

	// checking if the checkmate can be blocked or an attacking piece taken 
	//                        START     NEW POSSIBLE POSITION
	std::vector<std::pair<sf::Vector2i, sf::Vector2i>> allPositions; // gets all the positions for every piece which belongs to the same side as the 'side' parameter 
	for (int i = 0; i < 64; i++)
	{
		if (board[i] != '#')
		{
			if (get_side(board[i]) == side) // we use it to see if a piece can be used to block the checkmate 
			{
				int x = i % 8;
				int y = (i - x) / 8;

				std::vector<sf::Vector2i> piecePossiblePositions = available_positions({ x, y }, board);
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
		testBoard[newPos.first.x + 8 * newPos.first.y] = '#';
		testBoard[newPos.second.x + 8 * newPos.second.y] = board[newPos.first.x + 8 * newPos.first.y]; 

		if (!is_check(side, testBoard)) return false; 
	}

	return true; 
}

bool ChessLogic::move(CurrentGameState& gameState, sf::Vector2i start, sf::Vector2i end, std::array<char, 64>& board) 
{
	// ensures only the side, whose turn it is can make a move 
	if (gameState.mCurrentSide != get_side(board[start.x + 8 * start.y]))
	{
		return false;
	}

	if (gameState.mWhiteWon || gameState.mBlackWon) return false;  // a lost game cannot be continued from 

	// check if the user is castling 
	std::vector<sf::Vector2i> positionsToCastle = castling_positions(gameState, start, board); 
	const auto it1 = std::find(positionsToCastle.begin(), positionsToCastle.end(), end); 
	if (it1 != positionsToCastle.end())
	{
		// the user is castling 
		board[start.x + 8 * start.y] = '#'; 

		if (gameState.mCurrentSide == SIDE::WHITE) // white is castling 
		{
			gameState.mWhiteKingMoved = true; 

			board[end.x + 8 * end.y] = 'k'; 
			if (end.x > start.x) // castling right 
			{
				gameState.mWhiteRightRookMoved = true; 
				board[end.x - 1 + 8 * end.y] = 'r'; 
				board[end.x + 1 + 8 * end.y] = '#'; // removing the rook 
			}
			else
			{
				gameState.mWhiteLeftRookMoved = true; 
				board[end.x + 1 + 8 * end.y] = 'r'; 
				board[end.x - 1 + 8 * end.y] = '#'; // removing the rook 
			}
		}
		else if (gameState.mCurrentSide == SIDE::BLACK) // black is castling 
		{
			gameState.mBlackKingMoved = true; 
			board[end.x + 8 * end.y] = 'K'; 
			if (end.x > start.x) // castling right 
			{
				gameState.mBlackRightRookMoved = true; 
				board[end.x - 1 + 8 * end.y] = 'R'; 
				board[end.x + 1 + 8 * end.y] = '#'; 
			}
			else // catling left 
			{
				gameState.mBlackLeftRookMoved = true; 
				board[end.x + 1 + 8 * end.y] = 'R'; 
				board[end.x - 1 + 8 * end.y] = '#'; 
			}
		}

		return true; 
	}

	std::vector<sf::Vector2i> positions = available_positions(start, board);
	const auto it2 = std::find(positions.begin(), positions.end(), end);
	
	// checking if the attempted move is possible 
	if (it2 != positions.end()) 
	{
		std::array<char, 64> testBoard = board; 
		testBoard[start.x + 8 * start.y] = '#'; 
		testBoard[end.x + 8 * end.y] = board[start.x + 8 * start.y]; 
		
		// ensures that the new move does not put the moving player into check 
		if (!is_check(get_side(board[start.x + 8 * start.y]), testBoard))
		{
			// executes move, updating our global gameBoard 

			board[end.x + 8 * end.y] = board[start.x + 8 * start.y]; 
			board[start.x + 8 * start.y] = '#'; 
		
			// checking if a king or rook are moved 
			if (board[end.x + 8 * end.y] == 'r' && (start.x == 7)) gameState.mWhiteRightRookMoved = true; 
			if (board[end.x + 8 * end.y] == 'r' && (start.x == 0)) gameState.mWhiteLeftRookMoved = true; 
			if (board[end.x + 8 * end.y] == 'R' && (start.x == 7)) gameState.mBlackRightRookMoved = true; 
			if (board[end.x + 8 * end.y] == 'R' && (start.x == 0)) gameState.mBlackLeftRookMoved = true; 
			if (board[end.x + 8 * end.y] == 'k') gameState.mWhiteKingMoved = true; 
			if (board[end.x + 8 * end.y] == 'K') gameState.mBlackKingMoved = true; 


			if (ChessLogic::should_pawn_be_queen(end, board))	// we use end because the piece has been moved 
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

std::vector<sf::Vector2i> ChessLogic::castling_positions(const CurrentGameState& gameState, sf::Vector2i start, const std::array<char, 64>& board)
{
	std::vector<sf::Vector2i> output{};

	// castling cannot happen while the king is in check 
	if (is_check(gameState.mCurrentSide, board)) return output; 

	if (board[start.x + 8 * start.y] == 'k')
	{
		if (!gameState.mWhiteKingMoved)
		{
			// looking at right rook
			if (!gameState.mWhiteRightRookMoved)
			{
				if (board[5 + 8 * 7] == '#' && board[6 + 8 * 7] == '#') // ensuring that the right of the king is empty 
				{
					// ensuring that the king is not moving across check or end up in check 
					bool kingMovesAcrossCheck = false; 

					std::array<char, 64> testBoard = board; 
					testBoard[start.x + 8 * start.y] = '#'; 
					testBoard[5 + 8 * 7] = 'k'; 
					if (is_check(gameState.mCurrentSide, testBoard)) kingMovesAcrossCheck = true;
					
					testBoard[5 + 8 * 7] = '#'; 
					testBoard[6 + 8 * 7] = 'k'; 
					if (is_check(gameState.mCurrentSide, testBoard)) kingMovesAcrossCheck = true; 

					if (!kingMovesAcrossCheck)
					{
						output.emplace_back(6, 7);
					}

				}
			}
			// looking at left rook 
			if (!gameState.mWhiteLeftRookMoved)
			{
				if (board[1 + 8 * 7] == '#' && board[2 + 8 * 7] == '#' && board[3 + 8 * 7] == '#')
				{
					// ensures that the king does not move across check or end up in check 
					bool kingMovesAcrossCheck = false; 

					std::array<char, 64> testBoard = board; 
					testBoard[start.x + 8 * start.y] = '#'; 
					testBoard[1 + 8 * 7] = 'k'; 
					if (is_check(gameState.mCurrentSide, testBoard)) kingMovesAcrossCheck = true; 

					testBoard[1 + 8 * 7] = '#'; 
					testBoard[2 + 8 * 7] = 'k'; 
					if (is_check(gameState.mCurrentSide, testBoard)) kingMovesAcrossCheck = true; 

					testBoard[2 + 8 * 7] = '#'; 
					testBoard[3 + 8 * 7] = 'k'; 
					if (is_check(gameState.mCurrentSide, testBoard)) kingMovesAcrossCheck = true; 

					if (!kingMovesAcrossCheck)
					{
						output.emplace_back( 1, 7 ); 
					}
				}
			}

		}
	}
	else if (board[start.x + 8 * start.y] == 'K')
	{
		if (!gameState.mBlackKingMoved)
		{
			if (!gameState.mBlackRightRookMoved)
			{
				if (board[5] == '#' && board[6] == '#')
				{
					// ensuring that the king does not move across check or end up in check 
					bool kingMovesAcrossCheck = false; 

					std::array<char, 64> testBoard = board; 
					testBoard[start.x + 8 * start.y] = '#';  // 8 * start.y is redundant 
					testBoard[5] = 'K'; 
					if (is_check(gameState.mCurrentSide, testBoard)) kingMovesAcrossCheck = true; 

					testBoard[5] = '#'; 
					testBoard[6] = 'K'; 
					if (is_check(gameState.mCurrentSide, testBoard)) kingMovesAcrossCheck = true; 

					if (!kingMovesAcrossCheck)
					{
						output.emplace_back(6, 0);
					}

				}
			}
			if (!gameState.mBlackLeftRookMoved)
			{
				if (board[1] == '#' && board[2] == '#' && board[3] == '#')
				{
					bool kingMovesAcrossCheck = false; 

					std::array<char, 64> testBoard = board; 
					testBoard[start.x + 8 * start.y] = '#'; 
					testBoard[1] = 'K'; 
					if (is_check(gameState.mCurrentSide, testBoard)) kingMovesAcrossCheck = true; 

					testBoard[1] = '#'; 
					testBoard[2] = 'K'; 
					if (is_check(gameState.mCurrentSide, testBoard)) kingMovesAcrossCheck = true; 

					testBoard[2] = '#'; 
					testBoard[3] = 'K'; 
					if (is_check(gameState.mCurrentSide, testBoard)) kingMovesAcrossCheck = true; 

					if (!kingMovesAcrossCheck)
					{
						output.emplace_back( 1, 0 ); 
					}

				}
			}
		}
	}
	return output; 
}

SIDE ChessLogic::get_side(char piece) 
{
	assert(piece != '#'); 

	// 97 is 'a' in ASCII, while '65' is A 
	if (int(piece) >= 97) return SIDE::WHITE; 

	return SIDE::BLACK; 
}

char ChessLogic::get_king(SIDE side) 
{
	if (side == SIDE::WHITE) 
	{
		return 'k'; 
	}
	else 
	{
		return 'K'; 
	}
}

bool ChessLogic::position_is_in_board(sf::Vector2i pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.x > 7 || pos.y > 7) return false; 
	return true; 
}

bool ChessLogic::should_pawn_be_queen(sf::Vector2i pos, const std::array<char, 64>& board)
{
	const int index = pos.x + 8 * pos.y; 
	
	if (board[index] != 'p' && board[index] != 'P') return false; 

	if (get_side(board[index]) == SIDE::WHITE) // check if white pawn is on black side
	{
		if (pos.y == 0) return true; 
	}
	else
	{
		if (pos.y == 7) return true; 
	}

	return false; 
}

std::vector<sf::Vector2i> ChessLogic::get_rook_positions(sf::Vector2i pos, const std::array<char, 64>& board) 
{
	const char piece = board[pos.x + 8 * pos.y]; 
	assert(piece == 'r' || piece == 'R' || piece == 'q' || piece == 'Q');
	std::vector<sf::Vector2i> availablePositions; 

	sf::Vector2i above = { pos.x, pos.y - 1 };
	sf::Vector2i below = { pos.x, pos.y + 1 };
	sf::Vector2i right = { pos.x + 1, pos.y };
	sf::Vector2i left = { pos.x - 1, pos.y };

	while (position_is_in_board(above))
	{
		const int index = above.x + 8 * above.y;

		if (board[index] != '#')
		{
			if (get_side(board[index]) != get_side(piece)) // meaning it is a piece of the opposite side that we can take 
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
	while (position_is_in_board(below))
	{
		const int index = below.x + 8 * below.y;

		if (board[index] != '#')
		{
			if (get_side(board[index]) != get_side(piece)) // meaning it is a piece of the opposite side that we can take 
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
	while (position_is_in_board(right))
	{
		const int index = right.x + 8 * right.y;

		if (board[index] != '#')
		{
			if (get_side(board[index]) != get_side(piece)) // meaning it is a piece of the opposite side that we can take 
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
	while (position_is_in_board(left))
	{
		const int index = left.x + 8 * left.y;

		if (board[index] != '#')
		{
			if (get_side(board[index]) != get_side(piece)) // meaning it is a piece of the opposite side that we can take 
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

	return availablePositions; 
}

std::vector<sf::Vector2i> ChessLogic::get_knight_positions(sf::Vector2i pos, const std::array<char, 64>& board) 
{
	const char piece = board[pos.x + 8 * pos.y];
	assert(piece == 'n' || piece == 'N'); 

	std::vector<sf::Vector2i> availablePositions; 

	//RHS 
	const sf::Vector2i pos1 = { pos.x + 1, pos.y - 2 }; // top 
	const sf::Vector2i pos2 = { pos.x + 2, pos.y - 1 };

	const sf::Vector2i pos3 = { pos.x + 1, pos.y + 2 }; // bottom 
	const sf::Vector2i pos4 = { pos.x + 2, pos.y + 1 };

	//LHS
	const sf::Vector2i pos5 = { pos.x - 1, pos.y - 2 }; // top 
	sf::Vector2i pos6 = { pos.x - 2, pos.y - 1 };

	const sf::Vector2i pos7 = { pos.x - 2, pos.y + 1 }; // bottom
	const sf::Vector2i pos8 = { pos.x - 1, pos.y + 2 };

	if (position_is_in_board(pos1))
	{
		if ((board[pos1.x + 8 * pos1.y] == '#') || (get_side(board[pos1.x + 8 * pos1.y]) != get_side(piece))) availablePositions.push_back(pos1);
	}
	if (position_is_in_board(pos2))
	{
		if ((board[pos2.x + 8 * pos2.y] == '#') || (get_side(board[pos2.x + 8 * pos2.y]) != get_side(piece))) availablePositions.push_back(pos2);
	}
	if (position_is_in_board(pos3))
	{
		if ((board[pos3.x + 8 * pos3.y] == '#') || (get_side(board[pos3.x + 8 * pos3.y]) != get_side(piece))) availablePositions.push_back(pos3);
	}
	if (position_is_in_board(pos4))
	{
		if ((board[pos4.x + 8 * pos4.y] == '#') || (get_side(board[pos4.x + 8 * pos4.y]) != get_side(piece))) availablePositions.push_back(pos4);
	}
	if (position_is_in_board(pos5))
	{
		if ((board[pos5.x + 8 * pos5.y] == '#') || (get_side(board[pos5.x + 8 * pos5.y]) != get_side(piece))) availablePositions.push_back(pos5);
	}
	if (position_is_in_board(pos6))
	{
		if ((board[pos6.x + 8 * pos6.y] == '#') || (get_side(board[pos6.x + 8 * pos6.y]) != get_side(piece))) availablePositions.push_back(pos6);
	}
	if (position_is_in_board(pos7))
	{
		if ((board[pos7.x + 8 * pos7.y] == '#') || (get_side(board[pos7.x + 8 * pos7.y]) != get_side(piece))) availablePositions.push_back(pos7);
	}
	if (position_is_in_board(pos8))
	{
		if ((board[pos8.x + 8 * pos8.y] == '#') || (get_side(board[pos8.x + 8 * pos8.y]) != get_side(piece))) availablePositions.push_back(pos8);
	}

	return availablePositions; 
}

std::vector<sf::Vector2i> ChessLogic::get_bishop_positions(sf::Vector2i pos, const std::array<char, 64>& board)
{
	char piece = board[pos.x + 8 * pos.y];
	assert(piece == 'b' || piece == 'B' || piece == 'q' || piece == 'Q');

	std::vector<sf::Vector2i> availablePositions; 

	sf::Vector2i topRight = { pos.x + 1, pos.y - 1 };
	sf::Vector2i topLeft = { pos.x - 1, pos.y - 1 };
	sf::Vector2i bottomRight = { pos.x + 1, pos.y + 1 };
	sf::Vector2i bottomLeft = { pos.x - 1, pos.y + 1 };

	while (position_is_in_board(topRight))
	{
		const int index = topRight.x + 8 * topRight.y;

		if (board[index] != '#')
		{
			if (get_side(board[index]) != get_side(piece))
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
	while (position_is_in_board(topLeft))
	{
		const int index = topLeft.x + 8 * topLeft.y;

		if (board[index] != '#')
		{
			if (get_side(board[index]) != get_side(piece))
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
	while (position_is_in_board(bottomRight))
	{
		const int index = bottomRight.x + 8 * bottomRight.y;

		if (board[index] != '#')
		{

			if (get_side(board[index]) != get_side(piece))
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
	while (position_is_in_board(bottomLeft))
	{
		const int index = bottomLeft.x + 8 * bottomLeft.y;

		if (board[index] != '#')
		{
			if (get_side(board[index]) != get_side(piece))
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

	return availablePositions; 
}

std::vector<sf::Vector2i> ChessLogic::get_queen_positions(sf::Vector2i pos, const std::array<char, 64>& board)
{
	std::vector<sf::Vector2i> positions1 = get_rook_positions(pos, board);
	std::vector<sf::Vector2i> positions2 = get_bishop_positions(pos, board);

	positions1.insert(positions1.end(), positions2.begin(), positions2.end());

	return positions1; 
}

std::vector<sf::Vector2i> ChessLogic::get_king_positions(sf::Vector2i pos, const std::array<char, 64>& board)
{
	const char piece = board[pos.x + 8 * pos.y];
	assert(piece == 'k' || piece == 'K');

	std::vector<sf::Vector2i> availablePositions; 

	const sf::Vector2i top = { pos.x, pos.y - 1 };
	const sf::Vector2i right = { pos.x + 1, pos.y };
	const sf::Vector2i bottom = { pos.x, pos.y + 1 };
	const sf::Vector2i left = { pos.x - 1, pos.y };

	if (position_is_in_board(top))
	{
		if ((board[top.x + 8 * top.y] == '#') || (get_side(board[top.x + 8 * top.y]) != get_side(piece))) availablePositions.push_back(top);
	}
	if (position_is_in_board(right))
	{
		if ((board[right.x + 8 * right.y] == '#') || (get_side(board[right.x + 8 * right.y]) != get_side(piece))) availablePositions.push_back(right);
	}
	if (position_is_in_board(bottom))
	{
		if ((board[bottom.x + 8 * bottom.y] == '#') || (get_side(board[bottom.x + 8 * bottom.y]) != get_side(piece))) availablePositions.push_back(bottom);
	}
	if (position_is_in_board(left))
	{
		if ((board[left.x + 8 * left.y] == '#') || (get_side(board[left.x + 8 * left.y]) != get_side(piece))) availablePositions.push_back(left);
	}

	const sf::Vector2i topRight = { pos.x + 1, pos.y - 1 };
	const sf::Vector2i topLeft = { pos.x - 1, pos.y - 1 };
	const sf::Vector2i bottomRight = { pos.x + 1, pos.y + 1 };
	const sf::Vector2i bottomLeft = { pos.x - 1, pos.y + 1 };

	if (position_is_in_board(topRight))
	{
		if ((board[topRight.x + 8 * topRight.y] == '#') || (get_side(board[topRight.x + 8 * topRight.y]) != get_side(piece))) availablePositions.push_back(topRight);
	}
	if (position_is_in_board(topLeft))
	{
		if ((board[topLeft.x + 8 * topLeft.y] == '#') || (get_side(board[topLeft.x + 8 * topLeft.y]) != get_side(piece))) availablePositions.push_back(topLeft);
	}
	if (position_is_in_board(bottomRight))
	{
		if ((board[bottomRight.x + 8 * bottomRight.y] == '#') || (get_side(board[bottomRight.x + 8 * bottomRight.y]) != get_side(piece))) availablePositions.push_back(bottomRight);
	}
	if (position_is_in_board(bottomLeft))
	{
		if ((board[bottomLeft.x + 8 * bottomLeft.y] == '#') || (get_side(board[bottomLeft.x + 8 * bottomLeft.y]) != get_side(piece))) availablePositions.push_back(bottomLeft);
	}

	return availablePositions; 
}

std::vector<sf::Vector2i> ChessLogic::get_pawn_positions(sf::Vector2i pos, const std::array<char, 64>& board)
{
	const char piece = board[pos.x + 8 * pos.y];
	assert(piece == 'p' || piece == 'P');

	std::vector<sf::Vector2i> availablePositions; 

	if (get_side(piece) == SIDE::WHITE) // white pawn 
	{
		const sf::Vector2i above = { pos.x, pos.y - 1 };
		const sf::Vector2i right = { pos.x + 1, pos.y - 1 };
		const sf::Vector2i left = { pos.x - 1, pos.y - 1 };

		if (position_is_in_board(above))
		{
			if (board[above.x + 8 * above.y] == '#')
			{
				availablePositions.push_back(above);
			}
		}
		if (position_is_in_board(right))
		{
			if (board[right.x + 8 * right.y] != '#')
			{
				if (get_side(board[right.x + 8 * right.y]) == SIDE::BLACK) // the piece on the left must be black 
				{
					availablePositions.push_back(right);
				}
			}
		}
		if (position_is_in_board(left))
		{
			if (board[left.x + 8 * left.y] != '#')
			{
				if (get_side(board[left.x + 8 * left.y]) == SIDE::BLACK) // the piece on the left must be black 
				{
					availablePositions.push_back(left);
				}
			}
		}

		if (pos.y == 6) // it is the pawns first move 
		{
			if (board[above.x + 8 * above.y] == '#')
			{
				const sf::Vector2i aboveAbove = { above.x, above.y - 1 };
				if (board[aboveAbove.x + 8 * aboveAbove.y] == '#')
				{
					availablePositions.push_back(aboveAbove);
				}
			}
		}

	}
	else // black pawn 
	{

		const sf::Vector2i above = { pos.x, pos.y + 1 };
		const sf::Vector2i right = { pos.x + 1, pos.y + 1 };
		const sf::Vector2i left = { pos.x - 1, pos.y + 1 };

		if (position_is_in_board(above))
		{
			if (board[above.x + 8 * above.y] == '#')
			{
				availablePositions.push_back(above);
			}
		}
		if (position_is_in_board(right))
		{
			if (board[right.x + 8 * right.y] != '#')
			{
				if (get_side(board[right.x + 8 * right.y]) == SIDE::WHITE) // other piece must be white 
				{
					availablePositions.push_back(right);
				}
			}
		}
		if (position_is_in_board(left))
		{
			if (board[left.x + 8 * left.y] != '#')
			{
				if (get_side(board[left.x + 8 * left.y]) == SIDE::WHITE) // other iece must be white 
				{
					availablePositions.push_back(left);
				}
			}
		}

		if (pos.y == 1) // it is the pawns first move
		{
			if (board[above.x + 8 * above.y] == '#')
			{
				const sf::Vector2i aboveAbove = { above.x, above.y + 1 };
				if (board[aboveAbove.x + 8 * aboveAbove.y] == '#')
				{
					availablePositions.push_back(aboveAbove);
				}
			}
		}
	}

	return availablePositions; 
}
