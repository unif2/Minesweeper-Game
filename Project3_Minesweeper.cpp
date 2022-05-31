#include "Game.h"

int main()
{
    Game game;
    sf::RenderWindow window(sf::VideoMode(game.board.numColumns * 32, (game.board.numRows * 32) + 88), "Vince Velocci's Minesweeper (UFID: 50682042)");

    while (window.isOpen())
    {
        sf::Event event;
        vector<vector<Tile>> flagPositions;
        int sum1 = game.board.numMines;
        for (unsigned int row = 0; row < game.board.numRows; row++)
        {
            for (unsigned int col = 0; col < game.board.numColumns; col++)
            {
                if (game.board.boardTiles[row][col].isTileFlagged)
                {
                    sum1--;
                }
            }
        }
        game.board.numFlags = sum1;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            else if (event.type == sf::Event::MouseButtonPressed && !game.gameOver)
            {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (game.smiley.getGlobalBounds().contains(position.x, position.y))
                    {
                        game.resetBoard();
                    }
                    else if (game.debug.getGlobalBounds().contains(position.x, position.y))
                    {
                        game.isDebugOn = !game.isDebugOn;
                        for (unsigned int row = 0; row < game.board.numRows; row++)
                        {
                            for (unsigned int col = 0; col < game.board.numColumns; col++)
                            {
                                if (game.board.boardTiles[row][col].isTileMine)
                                {
                                    bool origFlagged = game.board.boardTiles[row][col].isTileFlagged;
                                    game.board.boardTiles[row][col].isTileRevealed = !game.board.boardTiles[row][col].isTileRevealed;
                                    if (game.isDebugOn && origFlagged)
                                    {
                                        game.board.boardTiles[row][col].isTileFlagged = false;
                                    }
                                    else if (!game.isDebugOn && origFlagged)
                                    {
                                        game.board.boardTiles[row][col].isTileFlagged = true;
                                    }
                                }
                            }
                        }
                    }
                    else if (game.test1.getGlobalBounds().contains(position.x, position.y))
                    {
                        game.loadBoard("testboard1");
                    }
                    else if (game.test2.getGlobalBounds().contains(position.x, position.y))
                    {
                        game.loadBoard("testboard2");
                    }
                    else if (game.test3.getGlobalBounds().contains(position.x, position.y))
                    {
                        game.loadBoard("testboard3");
                    }
                    else if (position.y <= game.board.numRows * 32 && !game.isDebugOn)
                    {
                        unsigned int rowClicked = position.y / 32;
                        unsigned int colClicked = position.x / 32;
                        bool revealed = game.board.boardTiles[rowClicked][colClicked].isTileRevealed;
                        if (!revealed && !game.board.boardTiles[rowClicked][colClicked].isTileFlagged)
                        {
                            game.board.boardTiles[rowClicked][colClicked].isTileRevealed = true;
                            if (game.board.boardTiles[rowClicked][colClicked].isTileMine)
                            {
                                game.gameOver = true;
                                game.loseOn = true;
                                game.smileyOn = false;
                                for (unsigned int i = 0; i < game.board.minePositions.size(); i++)
                                {
                                    unsigned int row = game.board.minePositions[i][0];
                                    unsigned int col = game.board.minePositions[i][1];
                                    game.board.boardTiles[row][col].isTileFlagged = false;
                                    game.board.boardTiles[row][col].isTileRevealed = true;
                                    game.board.numFlags = game.board.numMines;
                                }
                            }
                            else
                            {
                                game.recursiveReveal(rowClicked, colClicked, game.board.boardTiles);
                                for (unsigned int i = 0; i < game.board.zeroMineNearby.size(); i++)
                                {
                                    unsigned int row = game.board.zeroMineNearby[i][0];
                                    unsigned int col = game.board.zeroMineNearby[i][1];
                                    if (game.board.boardTiles[row][col].isTileRevealed)
                                    {
                                        vector<vector<unsigned int>> nearest = game.board.getNearestNeighbors(row, col);
                                        for (unsigned int t = 0; t < nearest.size(); t++)
                                        {
                                            if (!game.board.boardTiles[nearest[t][0]][nearest[t][1]].isTileRevealed && !game.board.boardTiles[nearest[t][0]][nearest[t][1]].isTileFlagged)
                                            {
                                                game.board.boardTiles[nearest[t][0]][nearest[t][1]].isTileRevealed = true;
                                                game.numRevealed++;
                                            }
                                        }
                                    }
                                }
                                if (game.numRevealed == game.board.numRows * game.board.numColumns - game.board.numMines)
                                {
                                    game.gameOver = true;
                                    game.winOn = true;
                                    game.smileyOn = false;
                                    for (unsigned int i = 0; i < game.board.minePositions.size(); i++)
                                    {
                                        unsigned int row = game.board.minePositions[i][0];
                                        unsigned int col = game.board.minePositions[i][1];
                                        game.board.boardTiles[row][col].isTileFlagged = true;
                                        game.board.numFlags = 0;
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    if (position.y <= game.board.numRows * 32 && !game.isDebugOn)
                    {
                        unsigned int rowClicked = position.y / 32;
                        unsigned int colClicked = position.x / 32;
                        bool flagged = game.board.boardTiles[rowClicked][colClicked].isTileFlagged;
                        bool revealed = game.board.boardTiles[rowClicked][colClicked].isTileRevealed;
                        if (!revealed)
                        {
                            if (flagged)
                            {
                                game.board.numFlags++;
                            }
                            else
                            {
                                game.board.numFlags--;
                            }
                            game.board.boardTiles[position.y / 32][position.x / 32].isTileFlagged = !game.board.boardTiles[position.y / 32][position.x / 32].isTileFlagged;
                        }
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && game.gameOver)
            {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                if (game.win.getGlobalBounds().contains(position.x, position.y) || game.lose.getGlobalBounds().contains(position.x, position.y))
                {
                    game.resetBoard();
                }
                else if (game.test1.getGlobalBounds().contains(position.x, position.y))
                {
                    game.loadBoard("testboard1");
                }
                else if (game.test2.getGlobalBounds().contains(position.x, position.y))
                {
                    game.loadBoard("testboard2");
                }
                else if (game.test3.getGlobalBounds().contains(position.x, position.y))
                {
                    game.loadBoard("testboard3");
                }
            }
        }
        window.clear();
        game.displayGame(window);
        window.display();
    }
    TextureManager::Clear();
    return 0;
}