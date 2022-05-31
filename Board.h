#pragma once
#include <vector>
#include <fstream>
#include <string>
#include "Tile.h"
using std::vector;
using std::string;
using std::ifstream;

class Board
{
public:
	vector<vector<Tile>> boardTiles;
	vector<vector<unsigned int>> minePositions;
	vector<vector<unsigned int>> zeroMineNearby;
	unsigned int numRows;
	unsigned int numColumns;
	unsigned int numMines;
	int numFlags;

public:
	Board();
	void displayBoard(sf::RenderWindow& window);
	void setAdjNumMines();
	vector<vector<unsigned int>> getNearestNeighbors(unsigned int row, unsigned int col);
};