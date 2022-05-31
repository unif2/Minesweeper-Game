#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Tile
{
public:
	sf::Sprite tileHidden;
	sf::Sprite tileRevealed;
	sf::Sprite flag;
	sf::Sprite mine;
	sf::Sprite numbers[9];
	bool isTileHidden;
	bool isTileRevealed;
	bool isTileMine;
	bool isTileFlagged;
	short tileNumber;
	Tile();
	void setPosition(float x, float y);
	void displayTile(sf::RenderWindow& window);
	void setMineStatus(bool isMine);
};