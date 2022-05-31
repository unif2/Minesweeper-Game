#include "Game.h"
#include <algorithm>

bool myfunction0(vector<unsigned int> v1, vector<unsigned int> v2)
{
	return (v1[0] < v2[0]);
}

bool myfunction1(vector<unsigned int> v1, vector<unsigned int> v2)
{
	if (v1[0] < v2[0])
		return v1[0] < v2[0];
	else if (v1[0] == v2[0])
		return v1[1] < v2[1];
}

Game::Game()
{
	resetBoard();
	setTextures();
}

void Game::loadBoard(string filename)
{
	board.numRows = 0;
	board.numColumns = 0;
	board.numMines = 0;
	board.minePositions.clear();
	board.boardTiles.clear();
	board.zeroMineNearby.clear();
	isDebugOn = false;
	smileyOn = true;
	loseOn = false;
	winOn = false;
	gameOver = false;
	numRevealed = 0;

	ifstream inputFile("boards/" + filename + ".brd");
	if (inputFile.is_open())
	{
		string line;
		while (getline(inputFile, line))
		{
			board.numColumns = line.length();
			board.numRows++;

			for (unsigned int i = 0; i < board.numColumns; i++)
			{
				short val = line[i] - '0';
				if (val == 1)
				{
					board.numMines++;
					vector<unsigned int> mineLocation;
					mineLocation.push_back(board.numRows - 1);
					mineLocation.push_back(i);
					board.minePositions.push_back(mineLocation);
				}
			}
		}
	}
	board.numFlags = board.numMines;
	unsigned int mineCounter = 0;

	for (unsigned int row = 0; row < board.numRows; row++)
	{
		vector<Tile> rowTiles;
		for (unsigned int col = 0; col < board.numColumns; col++)
		{
			Tile tile;
			if ((mineCounter != board.numMines) && (row == board.minePositions[mineCounter][0]) && (col == board.minePositions[mineCounter][1]))
			{
				tile.setMineStatus(true);
				mineCounter++;
			}
			tile.setPosition(col * 32, row * 32);
			rowTiles.push_back(tile);
		}
		board.boardTiles.push_back(rowTiles);
	}
	board.setAdjNumMines();
}

void Game::resetBoard()
{
	board.numRows = 0;
	board.numColumns = 0;
	board.numMines = 0;
	board.minePositions.clear();
	board.boardTiles.clear();
	board.zeroMineNearby.clear();
	isDebugOn = false;
	smileyOn = true;
	loseOn = false;
	winOn = false;
	gameOver = false;
	numRevealed = 0;

	ifstream inputFile("boards/config.cfg");

	inputFile >> board.numColumns;
	inputFile >> board.numRows;
	inputFile >> board.numMines;
	board.numFlags = board.numMines;
	setTextures();

	unsigned int minesAdded = 0;
	while (minesAdded != board.numMines)
	{
		int randomX = Random::Int(0, board.numRows - 1);
		int randomY = Random::Int(0, board.numColumns - 1);

		vector<unsigned int> mineLocation;
		unsigned int j;
		for (j = 0; j < board.minePositions.size(); j++)
		{
			if (randomX != board.minePositions[j][0] || randomY != board.minePositions[j][1])
				continue;
			else
				break;
		}

		if (j == board.minePositions.size())
		{
			mineLocation.push_back(randomX);
			mineLocation.push_back(randomY);
			board.minePositions.push_back(mineLocation);
			minesAdded++;
		}

		else
			continue;
	}

	std::sort(board.minePositions.begin(), board.minePositions.end(), myfunction0);
	std::sort(board.minePositions.begin(), board.minePositions.end(), myfunction1);
	
	unsigned int mineCounter = 0;

	for (unsigned int row = 0; row < board.numRows; row++)
	{
		vector<Tile> rowTiles;
		for (unsigned int col = 0; col < board.numColumns; col++)
		{
			Tile tile;
			if ((mineCounter != board.numMines) && (row == board.minePositions[mineCounter][0]) && (col == board.minePositions[mineCounter][1]))
			{
				tile.setMineStatus(true);
				mineCounter++;
			}
			tile.setPosition(col * 32, row * 32);
			rowTiles.push_back(tile);
		}
		board.boardTiles.push_back(rowTiles);
	}
	board.setAdjNumMines();
}

void Game::displayGame(sf::RenderWindow& window)
{
	board.displayBoard(window);
	if (smileyOn)
		window.draw(smiley);
	else if (winOn)
		window.draw(win);
	else if (loseOn)
		window.draw(lose);
	window.draw(debug);
	window.draw(test1);
	window.draw(test2);
	window.draw(test3);
	if (board.numFlags < 0)
		window.draw(minus);
	setDigits();
	window.draw(digit1);
	window.draw(digit2);
	window.draw(digit3);
}

void Game::setTextures()
{
	smiley.setTexture(TextureManager::GetTexture("face_happy"));
	lose.setTexture(TextureManager::GetTexture("face_lose"));
	win.setTexture(TextureManager::GetTexture("face_win"));
	debug.setTexture(TextureManager::GetTexture("debug"));
	test1.setTexture(TextureManager::GetTexture("test_1"));
	test2.setTexture(TextureManager::GetTexture("test_2"));
	test3.setTexture(TextureManager::GetTexture("test_3"));
	for (unsigned int i = 0; i < 11; i++)
	{
		sf::Sprite digit;
		digit.setTexture(numsTexture);
		digit.setTextureRect(sf::IntRect(i * 21, 0, 21, 32));
		singleDigits.push_back(digit);
	}
	smiley.setPosition((board.numColumns - 2) * 32 / 2, board.numRows * 32);
	win.setPosition((board.numColumns - 2) * 32 / 2, board.numRows * 32);
	lose.setPosition((board.numColumns - 2) * 32 / 2, board.numRows * 32);
	debug.setPosition(((board.numColumns - 2) / 2.0f + 4) * 32, board.numRows * 32);
	test1.setPosition(((board.numColumns - 2) / 2.0f + 6) * 32, board.numRows * 32);
	test2.setPosition(((board.numColumns - 2) / 2.0f + 8) * 32, board.numRows * 32);
	test3.setPosition(((board.numColumns - 2) / 2.0f + 10) * 32, board.numRows * 32);
	digit1 = singleDigits[0];
	digit2 = singleDigits[0];
	digit3 = singleDigits[0];
	minus = singleDigits[10];
	minus.setPosition(0, board.numRows * 32);
}

void Game::setDigits()
{
	unsigned int first;
	unsigned int second;
	unsigned int third;
	int val = abs(board.numFlags);
	first = val % 10;
	second = (val / 10) % 10;
	third = (val / 100) % 10;
	digit1 = singleDigits[third];
	digit2 = singleDigits[second];
	digit3 = singleDigits[first];
	digit1.setPosition(1 * 21, board.numRows * 32);
	digit2.setPosition(2 * 21, board.numRows * 32);
	digit3.setPosition(3 * 21, board.numRows * 32);
}

void Game::recursiveReveal(unsigned int row, unsigned int col, vector<vector<Tile>>& tiles)
{
	if (tiles[row][col].tileNumber > 0 && !tiles[row][col].isTileFlagged && !tiles[row][col].isTileRevealed)
	{
		tiles[row][col].isTileRevealed = true;
		numRevealed++;
	}

	else if (tiles[row][col].isTileFlagged)
		tiles[row][col].isTileRevealed = false;

	else if (tiles[row][col].isTileMine)
		tiles[row][col].isTileRevealed = false;

	else
	{
		tiles[row][col].isTileRevealed = true;
		numRevealed++;
		vector<vector<unsigned int>> nearbyTiles = board.getNearestNeighbors(row, col);

		for (unsigned int i = 0; i < nearbyTiles.size(); i++)
		{
			unsigned int nearbyRow = nearbyTiles[i][0];
			unsigned int nearbyCol = nearbyTiles[i][1];
			if (tiles[nearbyRow][nearbyCol].tileNumber == 0 && !tiles[nearbyRow][nearbyCol].isTileRevealed)
				recursiveReveal(nearbyRow, nearbyCol, tiles);
		}
	}
}