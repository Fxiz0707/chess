#include "Application.h"

Application::Application() :
	mRenderWindow(sf::VideoMode(640, 640), "Chess", sf::Style::Default, sf::ContextSettings(0, 0, 8, 0, 2, 0)),
	mTimeframe(sf::seconds(1 / 144.f)),
	mGameArr(), 
	mCurrentGameState(), 
	mBackgroundBoard(sf::Quads, 64 * 4), 
	mPossibleMoveMarkings(), 
	mPieces(), 
	mWhiteWinsText("White WINS", Resources::getMonoSpacedFont(), 30),
	mBlackWinsText("Black WINS", Resources::getMonoSpacedFont(), 30),
	mClickSound(Resources::getClickSound()), 
	mPieceTakenSound(Resources::getPieceTakenSound()),
	mCurrentlyHeldPiece(), 
	mUserIsCurrentlyHoldingPiece(false)
{
	mGameArr = 
	{
		//       0   1   2   3   4   5   6   7		
		/*0*/	'R','N','B','Q','K','B','N','R',
		/*1*/	'P','P','P','P','P','P','P','P',
		/*2*/	'#','#','#','#','#','#','#','#',
		/*3*/	'#','#','#','#','#','#','#','#',
		/*4*/	'#','#','#','#','#','#','#','#',
		/*5*/	'#','#','#','#','#','#','#','#',
		/*6*/	'p','p','p','p','p','p','p','p',
		/*7*/	'r','n','b','q','k','b','n','r'
	};

	int count = 0; // used to determine the colour 
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			int index = i + 8 * j; 

			mBackgroundBoard[4 * index].position = {80.f * i, 80.f * j}; // top left
			mBackgroundBoard[4 * index + 1].position = { 80.f * i + 80.f, 80.f * j }; // top right
			mBackgroundBoard[4 * index + 2].position = { 80.f * i + 80.f, 80.f * j + 80.f}; // bottom right 
			mBackgroundBoard[4 * index + 3].position = { 80.f * i, 80.f * j + 80.f }; // bottom left 

			sf::Color color = (j % 2 == i % 2) ? sf::Color(96, 124, 143) : sf::Color(252, 237, 220);

			mBackgroundBoard[4 * index].color = color; // top left
			mBackgroundBoard[4 * index + 1].color = color; // top right
			mBackgroundBoard[4 * index + 2].color = color; // bottom right 
			mBackgroundBoard[4 * index + 3].color = color; // bottom left 
		}
	}

	mWhiteWinsText.setPosition(200, 300); 
	mBlackWinsText.setPosition(200, 300); 

	mWhiteWinsText.setFillColor(sf::Color(96, 124, 143));
	mBlackWinsText.setFillColor(sf::Color(222, 2, 195));

	mWhiteWinsText.setOutlineColor(sf::Color(252, 237, 220));
	mWhiteWinsText.setOutlineThickness(3); 

	updateDrawingComponents();  
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
		handleEvents(); 
		render(); 
	}
}


void Application::update(sf::Time dt)
{
	if (mCurrentGameState.currentSide == 1 && mCurrentGameState.whiteWon == false && mCurrentGameState.blackWon == false) // if it is blacks turn 
	{
		std::array<char, 64> minBoard; 
		int currentMin = INT_MAX; 
		// black is attempting to minimise
		for (std::array<char, 64>&possibleBoard : ChessGame::everyPosition(mCurrentGameState, mGameArr))
		{
			mCurrentGameState.currentSide = 0; 
			int potentialMin = ComputerPlayer::minimax(2, mCurrentGameState, possibleBoard); 
			if (potentialMin < currentMin)
			{
				currentMin = potentialMin; 
				minBoard = possibleBoard; 
			}
		}
		std::cout << "move made with eval: " << currentMin << std::endl; 

		mGameArr = minBoard; 

		updateDrawingComponents(); 
		mCurrentGameState.currentSide = 0; 

	}
}

void Application::render() 
{
	mRenderWindow.clear(); 

	mRenderWindow.draw(mBackgroundBoard); 

	if (mUserIsCurrentlyHoldingPiece)
	{
		for (sf::CircleShape shape : mPossibleMoveMarkings)
		{
			mRenderWindow.draw(shape);
		}
	}
	
	for (Piece piece : mPieces)
	{
		mRenderWindow.draw(piece); 
	}

	mRenderWindow.draw(mCurrentlyHeldPiece); 

	if (mCurrentGameState.whiteWon)
	{
		mRenderWindow.draw(mWhiteWinsText); 
	}
	if (mCurrentGameState.blackWon)
	{
		mRenderWindow.draw(mBlackWinsText); 
	}

	mRenderWindow.display(); 
}

void Application::handleEvents()
{
	sf::Event event; 
	while (mRenderWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mRenderWindow.close(); 
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			sf::Vector2i mousePosition = { event.mouseButton.x, event.mouseButton.y }; 
			
			int boardXPosition = mousePosition.x / 80; 
			int boardYPosition = mousePosition.y / 80; 

			if (!mUserIsCurrentlyHoldingPiece && mCurrentGameState.currentSide == 0)
			{
				for (auto it = mPieces.begin(); it != mPieces.end(); it++)
				{
					if ((*it).mBoardPosition == sf::Vector2i(boardXPosition, boardYPosition))
					{
						// check that the rigot player is being used right here 

						mCurrentlyHeldPiece = (*it);
						mCurrentlyHeldPiece.setPosition((sf::Vector2f)mousePosition);
						mCurrentlyHeldPiece.setOrigin({ 40.f, 40.f });

						mPieces.erase(it);
						mUserIsCurrentlyHoldingPiece = true;

						mPossibleMoveMarkings.clear(); 
						std::vector<sf::Vector2i> possiblePlaces = ChessGame::availablePositions({boardXPosition, boardYPosition}, mGameArr);
						std::vector<sf::Vector2i> possibleCastlingPositions = ChessGame::castlingPositions(mCurrentGameState, { boardXPosition, boardYPosition }, mGameArr); 
						
						possiblePlaces.insert(possiblePlaces.end(), possibleCastlingPositions.begin(), possibleCastlingPositions.end()); 

						for (sf::Vector2i pos : possiblePlaces)
						{
							sf::CircleShape shape = sf::CircleShape(20.f); 
							shape.setOrigin({20.f, 20.f});
							shape.setPosition({80 * pos.x + 40.f, 80 * pos.y + 40.f});
							shape.setFillColor(sf::Color(158, 158, 158, 100));
						
							mPossibleMoveMarkings.push_back(shape); 
						}
						break;
					}
				}
			}
		}

		else if (event.type == sf::Event::MouseButtonReleased)
		{
			sf::Vector2i mousePosition = { event.mouseButton.x, event.mouseButton.y }; 

			bool moveSuccessful = false; // so that unnecessary calls to checkCheckMate don't waste resources

			int boardXPosition = mousePosition.x / 80; 
			int boardYPosition = mousePosition.y / 80; 

			if (mUserIsCurrentlyHoldingPiece)
			{
				mUserIsCurrentlyHoldingPiece = false; 

				if (ChessGame::move(mCurrentGameState, mCurrentlyHeldPiece.mBoardPosition, {boardXPosition, boardYPosition}, mGameArr))
				{
					mClickSound.play(); 

					// only switch sides if the move was successful 
					mCurrentGameState.currentSide = !mCurrentGameState.currentSide;
					if (ChessGame::isCheckMate(mCurrentGameState.currentSide, mGameArr))
					{
						if (mCurrentGameState.currentSide == 1) // white won 
						{
							mCurrentGameState.whiteWon = true; 
						}
						else // black won 
						{
							mCurrentGameState.blackWon = true; 
						}
					}
					if (ChessGame::isCheck(mCurrentGameState.currentSide, mGameArr))
					{
						mPieceTakenSound.play(); 
					}
				}

				mCurrentlyHeldPiece = Piece(); 
				updateDrawingComponents(); 
			}

		}
		else if (event.type == sf::Event::MouseMoved)
		{
			sf::Vector2i mousePosition = { event.mouseMove.x, event.mouseMove.y }; 

			if (mUserIsCurrentlyHoldingPiece)
			{
				mCurrentlyHeldPiece.setPosition((sf::Vector2f)mousePosition); 
			}
		}
		else if (event.type == sf::Event::KeyPressed) // ENTER RESETS THE GAME 
		{
			if (event.key.code == sf::Keyboard::Enter)
			{
				mCurrentGameState.reset(); 
				resetBoard(); 
				updateDrawingComponents(); 
			}
		}
	}
}

void Application::updateDrawingComponents()
{
	mPieces = std::vector<Piece>(); 
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (mGameArr[i + 8 * j] != '#')
			{
				mPieces.push_back(Piece({i , j}, mGameArr[i + 8 * j]));
			}
		}
	}
}

void Application::resetBoard()
{
	mGameArr =
	{
		//       0   1   2   3   4   5   6   7		
		/*0*/	'R','#','#','#','K','#','#','R',
		/*1*/	'P','P','P','P','P','P','P','P',
		/*2*/	'#','#','#','#','#','#','#','#',
		/*3*/	'#','#','#','#','#','#','#','#',
		/*4*/	'#','#','#','#','#','#','#','#',
		/*5*/	'#','#','#','#','#','#','#','#',
		/*6*/	'q','q','q','q','p','p','p','p',
		/*7*/	'r','#','#','#','k','#','#','r'
	};
}

