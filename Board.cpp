#include <string>
#include <iostream>
#include <algorithm>
#include "Board.h"
#include "Random.h"
using std::string;
using std::cout;
using std::endl;

Board::Board()
{
	numColumns = 0;
	numRows = 0;
	numMines = 0;
	numFlags = 0;
}

void Board::displayBoard(sf::RenderWindow& window)
{
	for (unsigned int row = 0; row < numRows; row++)
	{
		for (unsigned int col = 0; col < numColumns; col++)
			boardTiles[row][col].displayTile(window);
	}
}

void Board::setAdjNumMines()
{
	for (unsigned int row = 0; row < numRows; row++)
	{
		for (unsigned int col = 0; col < numColumns; col++)
		{
			if (boardTiles[row][col].isTileMine)
				continue;
			
			unsigned int num = 0;
			vector<vector<unsigned int>> nearbyTiles = getNearestNeighbors(row, col);

			for (unsigned int i = 0; i < nearbyTiles.size(); i++)
			{
				unsigned int nearbyRow = nearbyTiles[i][0];
				unsigned int nearbyCol = nearbyTiles[i][1];
				num += boardTiles[nearbyRow][nearbyCol].isTileMine;
			}

			boardTiles[row][col].tileNumber = num;
			if (num == 0)
			{
				vector<unsigned int> zeroLocation{ row, col };
				zeroMineNearby.push_back(zeroLocation);
			}
		}
	}
}

vector<vector<unsigned int>> Board::getNearestNeighbors(unsigned int row, unsigned int col)
{
	vector<vector<unsigned int>> nearestNeighbors;

	if (row == 0 && col == 0)
	{
		nearestNeighbors.push_back({ row, col + 1 });
		nearestNeighbors.push_back({ row + 1, col + 1 });
		nearestNeighbors.push_back({ row + 1, col });
	}

	else if (row == 0 && col == numColumns - 1)
	{
		nearestNeighbors.push_back({ row, col - 1 });
		nearestNeighbors.push_back({ row + 1, col - 1 });
		nearestNeighbors.push_back({ row + 1, col });
	}

	else if (row == numRows - 1 && col == numColumns - 1)
	{
		nearestNeighbors.push_back({ row - 1, col });
		nearestNeighbors.push_back({ row - 1, col - 1 });
		nearestNeighbors.push_back({ row, col - 1 });
	}

	else if (row == numRows - 1 && col == 0)
	{
		nearestNeighbors.push_back({ row - 1, col });
		nearestNeighbors.push_back({ row - 1, col + 1 });
		nearestNeighbors.push_back({ row, col + 1 });
	}

	else if (row == 0)
	{
		nearestNeighbors.push_back({ row, col - 1 });
		nearestNeighbors.push_back({ row, col + 1 });
		nearestNeighbors.push_back({ row + 1, col - 1 });
		nearestNeighbors.push_back({ row + 1, col });
		nearestNeighbors.push_back({ row + 1, col + 1 });
	}

	else if (row == numRows - 1)
	{
		nearestNeighbors.push_back({ row, col - 1 });
		nearestNeighbors.push_back({ row, col + 1 });
		nearestNeighbors.push_back({ row - 1, col - 1 });
		nearestNeighbors.push_back({ row - 1, col });
		nearestNeighbors.push_back({ row - 1, col + 1 });
	}

	else if (col == 0)
	{
		nearestNeighbors.push_back({ row, col + 1 });
		nearestNeighbors.push_back({ row - 1, col + 1 });
		nearestNeighbors.push_back({ row - 1, col });
		nearestNeighbors.push_back({ row + 1, col });
		nearestNeighbors.push_back({ row + 1, col + 1 });
	}

	else if (col == numColumns - 1)
	{
		nearestNeighbors.push_back({ row, col - 1 });
		nearestNeighbors.push_back({ row - 1, col - 1 });
		nearestNeighbors.push_back({ row - 1, col });
		nearestNeighbors.push_back({ row + 1, col });
		nearestNeighbors.push_back({ row + 1, col - 1 });
	}

	else
	{
		nearestNeighbors.push_back({ row, col - 1 });
		nearestNeighbors.push_back({ row - 1, col - 1 });
		nearestNeighbors.push_back({ row - 1, col });
		nearestNeighbors.push_back({ row + 1, col });
		nearestNeighbors.push_back({ row + 1, col - 1 });
		nearestNeighbors.push_back({ row + 1, col + 1 });
		nearestNeighbors.push_back({ row, col + 1 });
		nearestNeighbors.push_back({ row - 1, col + 1 });
	}
	return nearestNeighbors;
}