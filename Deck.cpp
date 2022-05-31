#include <string>
#include "Deck.h"
#include "TextureManager.h"
#include "Random.h"
using std::to_string;
using std::string;

Deck::Deck()
{
	Reset();
}

void Deck::Display(sf::RenderWindow& window)
{
	for (int i = 0; i < 52; i++)
	{
		cards[i].SetPosition(i * 40, i * 20);
		cards[i].Display(window);
	}
}

void Deck::Shuffle()
{
	// Randomize the cards
	for (int i = 0; i < 52; i++)
	{
		// Get two random card locations
		int card1 = Random::Int(0, 51); // 51 because that's the last index of the array
		int card2 = Random::Int(0, 51);

		// Swap the two cards!
		Card temp = cards[card1];
		cards[card1] = cards[card2];
		cards[card2] = temp;

	}
}

void Deck::Reset()
{
	int index = 0; // location of the first card
	string suits[4] = { "hearts", "diamonds", "clubs", "spades" };

	for (int suit = 0; suit < 4; suit++)
	{
		for (int i = 2; i <= 10; i++)
		{
			string cardName = "cards/" + to_string(i);
			cardName += "_of_";
			cardName += suits[suit];

			cards[index] = Card(cardName);
			index++; // Move to the next spot
		}
		// Jack through Ace?
		string cardName = "cards/jack_of_" + suits[suit];
		cards[index++] = Card(cardName);

		cardName = "cards/queen_of_" + suits[suit];
		cards[index++] = Card(cardName);

		cardName = "cards/king_of_" + suits[suit];
		cards[index++] = Card(cardName);

		cardName = "cards/ace_of_" + suits[suit];
		cards[index++] = Card(cardName);
	}
}

Card Deck::Draw()
{
	if (topCard >= 0)
		return cards[topCard--];
}