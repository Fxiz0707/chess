#include "Application.h"

Application::Application() :
	mRenderWindow_(sf::VideoMode(640, 640), "Chess", sf::Style::Default, sf::ContextSettings(0, 0, 8, 0, 2, 0)),
	mTimeFrame_(sf::seconds(1 / 144.f)),
	mBackgroundBoard_(sf::Quads, 64 * 4),
	mWhiteWinsText_("White WINS", Resources::getMonoSpacedFont(), 30),
	mBlackWinsText_("Black WINS", Resources::getMonoSpacedFont(), 30),
	mPieceMovedSound_(Resources::getClickSound()),
	mCheckSound_(Resources::getPieceTakenSound()),
	mUserIsCurrentlyHoldingPiece_(false)
{

	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			const int index = i + 8 * j;

			mBackgroundBoard_[4 * index].position = { 80.f * i, 80.f * j }; // top left
			mBackgroundBoard_[4 * index + 1].position = { 80.f * i + 80.f, 80.f * j }; // top right
			mBackgroundBoard_[4 * index + 2].position = { 80.f * i + 80.f, 80.f * j + 80.f }; // bottom right 
			mBackgroundBoard_[4 * index + 3].position = { 80.f * i, 80.f * j + 80.f }; // bottom left 

			const sf::Color color = (j % 2 == i % 2) ? sf::Color(96, 124, 143) : sf::Color(252, 237, 220);

			mBackgroundBoard_[4 * index].color = color; // top left
			mBackgroundBoard_[4 * index + 1].color = color; // top right
			mBackgroundBoard_[4 * index + 2].color = color; // bottom right 
			mBackgroundBoard_[4 * index + 3].color = color; // bottom left 
		}
	}

	mWhiteWinsText_.setPosition(200, 300);
	mBlackWinsText_.setPosition(200, 300);

	mWhiteWinsText_.setFillColor(sf::Color(96, 124, 143));
	mBlackWinsText_.setFillColor(sf::Color(96, 124, 143));

	mWhiteWinsText_.setOutlineColor(sf::Color(252, 237, 220));
	mBlackWinsText_.setOutlineColor(sf::Color(252, 237, 220));

	mWhiteWinsText_.setOutlineThickness(3);
	mBlackWinsText_.setOutlineThickness(3);

	update_drawing_components();
}

void Application::run()
{
	sf::Clock clock;
	sf::Time elapsedTime;

	while (true)
	{
		elapsedTime += clock.restart();
		if (elapsedTime > sf::seconds(1 / 144.f))
		{
			elapsedTime -= sf::seconds(1 / 144.f);
			update(sf::seconds(1 / 144.f));
		}
		handle_events();
		render();
	}
}


void Application::update(sf::Time dt)
{
	// TRASH RIGHT NOW FOR TESTING 

	if (mChessGame_.get_current_side() == SIDE::BLACK)
	{
		ComputerPlayer::do_computer_move(3, mChessGame_);

		mPieceMovedSound_.play();

		if (mChessGame_.is_check())
		{
			mCheckSound_.play();
		}

		if (mChessGame_.is_checkmate())
		{
			if (mChessGame_.get_current_side() == SIDE::BLACK) mWhiteWon_ = true;
			if (mChessGame_.get_current_side() == SIDE::WHITE) mBlackWon_ = true;
		}

		update_drawing_components();
	}
}

void Application::render()
{
	mRenderWindow_.clear();

	mRenderWindow_.draw(mBackgroundBoard_);

	if (mUserIsCurrentlyHoldingPiece_)
	{
		for (sf::CircleShape shape : mPossibleMoveMarkings_)
		{
			mRenderWindow_.draw(shape);
		}
	}

	for (Piece piece : mGamePieces_)
	{
		mRenderWindow_.draw(piece);
	}

	for (sf::CircleShape marking : mPossibleMoveMarkings_)
	{
		mRenderWindow_.draw(marking); 
	}

	if (mUserIsCurrentlyHoldingPiece_)
	{
		mRenderWindow_.draw(mCurrentlyHeldPiece_);
	}

	if (mWhiteWon_) 
				
	{
		mRenderWindow_.draw(mWhiteWinsText_); 
	}
	else if (mBlackWon_)
	{
		mRenderWindow_.draw(mBlackWinsText_); 
	}

	mRenderWindow_.display();
}

void Application::handle_events()
{
	sf::Event event;
	while (mRenderWindow_.pollEvent(event))
	{
		switch (event.type)
		{
		case(sf::Event::Closed):
		{
			mRenderWindow_.close();

			break;
		}
		case(sf::Event::MouseButtonPressed):
		{
			handle_mouse_press({ event.mouseButton.x, event.mouseButton.y });

			break;
		}
		case(sf::Event::MouseButtonReleased):
		{

			handle_mouse_release({ event.mouseButton.x, event.mouseButton.y });

			break;
		}
		case(sf::Event::MouseMoved):
		{

			handle_mouse_moved({event.mouseMove.x, event.mouseMove.y}); 

			break;
		}
		default:
			// does nothing 
			break;
		}


	}

}

void Application::update_drawing_components()
{
	const std::array<char, 64>& gameBoard = mChessGame_.get_game_board();

	mGamePieces_ = std::vector<Piece>(); 

	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (gameBoard[i + 8 * j] != '#')
				mGamePieces_.emplace_back(sf::Vector2f(80.f * i, 80.f * j), gameBoard[i + 8 * j]);
		}
	}
}

void Application::reset_board()
{
	mChessGame_ = ChessGame();
}

void Application::handle_mouse_press(sf::Vector2i mousePos)
{
	if (mChessGame_.get_current_side() == SIDE::BLACK) return; 

	const int clickedBoardX = mousePos.x / 80;
	const int clickedBoardY = mousePos.y / 80;

	const char piece = mChessGame_.get_game_board()[clickedBoardX + 8 * clickedBoardY];

	if (piece != '#')
	{
		updatePossibleMarkings(sf::Vector2i(clickedBoardX, clickedBoardY)); 

		mCurrentlyHeldPiece_ = Piece(sf::Vector2f(mousePos.x, mousePos.y), piece);
		mCurrentlyHeldPiece_.setOrigin(40.f, 40.f);
		mUserIsCurrentlyHoldingPiece_ = true;
		mCurrentlyHeldPiecePos_ = sf::Vector2i(clickedBoardX, clickedBoardY); 

		// removing the duplicated piece from mGamePieces_

		for (auto it = mGamePieces_.begin(); it != mGamePieces_.end(); it++)
		{
			const int boardPieceX = it->getPosition().x / 80;
			const int boardPieceY = it->getPosition().y / 80; 

			if (boardPieceX == clickedBoardX && boardPieceY == clickedBoardY)
			{
				mGamePieces_.erase(it);
				return; 
			}
		}
	}
}

void Application::updatePossibleMarkings(sf::Vector2i boardPos)
{
	mPossibleMoveMarkings_.clear(); 

	std::vector<sf::Vector2i> possiblePositions = mChessGame_.get_available_positions(boardPos);

	for (sf::Vector2i pos : possiblePositions)
	{
		sf::CircleShape marking(20.f);
		marking.setOrigin(20.f, 20.f); 
		marking.setFillColor(sf::Color(132, 135, 140, 120));
		marking.setPosition(pos.x * 80 + 40, pos.y * 80 + 40);

		mPossibleMoveMarkings_.push_back(marking); 
	}
}


void Application::handle_mouse_release(sf::Vector2i mousePos)
{
	int boardXPosition = mousePos.x / 80;
	int boardYPosition = mousePos.y / 80;

	if (mUserIsCurrentlyHoldingPiece_)
	{

		if (mChessGame_.move(mCurrentlyHeldPiecePos_, { boardXPosition, boardYPosition })) // user moved piece to a valid location 
		{
			mPieceMovedSound_.play();

			if (mChessGame_.is_check())
			{
				mCheckSound_.play();
			}

			if (mChessGame_.is_checkmate())
			{
				if (mChessGame_.get_current_side() == SIDE::BLACK) mWhiteWon_ = true;
				if (mChessGame_.get_current_side() == SIDE::WHITE) mBlackWon_ = true; 
			}

			mPossibleMoveMarkings_.clear();
		}

		mCurrentlyHeldPiece_ = Piece();
		mUserIsCurrentlyHoldingPiece_ = false; // the piece has been released
		mCurrentlyHeldPiecePos_ = sf::Vector2i();

		update_drawing_components(); 
	}
}

void Application::handle_mouse_moved(sf::Vector2i mousePos)
{
	if (mUserIsCurrentlyHoldingPiece_)
	{
		mCurrentlyHeldPiece_.setPosition(sf::Vector2f(mousePos.x, mousePos.y));
	}
}
