#include <string>
#include "Tile.h"
using std::to_string;

Tile::Tile()
{
	isTileHidden = true;
	isTileMine = false;
	isTileFlagged = false;
	isTileRevealed = false;
	tileNumber = -1;
	tileHidden.setTexture(TextureManager::GetTexture("tile_hidden"));
	tileRevealed.setTexture(TextureManager::GetTexture("tile_revealed"));
	flag.setTexture(TextureManager::GetTexture("flag"));
	mine.setTexture(TextureManager::GetTexture("mine"));
	numbers[0] = tileRevealed;
	for (unsigned int i = 1; i <= 8; i++)
		numbers[i].setTexture(TextureManager::GetTexture("number_" + to_string(i)));
}

void Tile::setPosition(float x, float y)
{
	tileHidden.setPosition(x, y);
	tileRevealed.setPosition(x, y);
	flag.setPosition(x, y);
	mine.setPosition(x, y);
	
	for (unsigned int i = 0; i < 9; i++)
		numbers[i].setPosition(x, y);
}

void Tile::displayTile(sf::RenderWindow& window)
{
	if (isTileHidden && !isTileFlagged && !isTileRevealed)
	{
		window.draw(tileHidden);
	}
	else if (isTileMine && isTileRevealed && !isTileFlagged)
	{
		window.draw(tileRevealed);
		window.draw(mine);
	}
	else if (isTileHidden && isTileFlagged && !isTileRevealed)
	{
		window.draw(tileHidden);
		window.draw(flag);
	}
	else if (!isTileMine && isTileRevealed && !isTileFlagged)
	{
		window.draw(tileRevealed);
		window.draw(numbers[tileNumber]);
	}
}

void Tile::setMineStatus(bool isMine)
{
	isTileMine = isMine;
}