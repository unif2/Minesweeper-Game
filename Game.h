#pragma once
#include "Board.h"
#include "Random.h"
class Game
{
public:
	Board board;
	bool isDebugOn = false;
	bool smileyOn = true;
	bool loseOn = false;
	bool winOn = false;
	bool gameOver = false;
	sf::Sprite smiley;
	sf::Sprite lose;
	sf::Sprite win;
	sf::Sprite flagCounter;
	sf::Sprite debug;
	sf::Sprite test1;
	sf::Sprite test2;
	sf::Sprite test3;
	vector<sf::Sprite> singleDigits;
	sf::Texture numsTexture = TextureManager::GetTexture("digits");
	sf::Sprite digit1;
	sf::Sprite digit2;
	sf::Sprite digit3;
	sf::Sprite minus;
	unsigned int numRevealed;
	Game();
	void loadBoard(string filename);
	void resetBoard();
	void displayGame(sf::RenderWindow& window);
	void setTextures();
	void setDigits();
	void recursiveReveal(unsigned int row, unsigned int col, vector<vector<Tile>>& tiles);
};