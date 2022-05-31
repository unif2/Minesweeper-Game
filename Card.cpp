#include "Card.h"
#include "TextureManager.h"

Card::Card(string cardName)
{
    cardFaceup.setTexture(TextureManager::GetTexture(cardName));
    cardFacedown.setTexture(TextureManager::GetTexture("cards/card_back"));
    isFaceup = true;
}

void Card::SetPosition(float x, float y)
{
    cardFaceup.setPosition(x, y);
    cardFacedown.setPosition(x, y);

}

void Card::SetPosition(sf::Vector2f position)
{
    cardFaceup.setPosition(position);
    cardFacedown.setPosition(position);
}

sf::FloatRect Card::GetSpriteRect()
{
    return (isFaceup) ? cardFaceup.getGlobalBounds() : cardFacedown.getGlobalBounds();
}

void Card::Display(sf::RenderWindow& window)
{
    (isFaceup) ? window.draw(cardFaceup) : window.draw(cardFacedown);
}