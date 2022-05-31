#pragma once
#include <SFML/Graphics.hpp>
#include "Card.h"
class Deck
{
    Card cards[52]; // 4 suits x 13 cards in each suit
    
    int topCard = 51;

public:
    Deck(); // number between 1 and 13
    void Display(sf::RenderWindow& window);
    void Shuffle();
    void Reset();

    Card Draw();


};

    /*sf::RenderWindow* theWindow;
    sf::Sprite someCardToDraw;

public:
    void DisplayAllCards(sf::RenderWindow& window)
    {
        window.draw(someCardToDraw);
    }*/