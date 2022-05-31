#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using std::string;

class Card
{
public:
    sf::Sprite cardFaceup; // What to draw
    sf::Sprite cardFacedown; // What to draw
    bool isFaceup; // face up, or face down?
    Card(string cardName = "ace_of_spades");
    void SetPosition(float x, float y);
    void SetPosition(sf::Vector2f position);
    sf::FloatRect GetSpriteRect();
    void Display(sf::RenderWindow& window);
};