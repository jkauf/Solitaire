#include "deck.h"

Deck::Deck()
{
	buildDeck();
	shuffleDeck();
}

void Deck::buildDeck()
{
	Card aCard;

	for (int i = 1; i <= 13; i++)
	{
		for (st suit = clubs; suit <= spades; suit = static_cast<st>(suit + 1))
		{
			if (suit == diamonds || suit == hearts)
				deck.push_back(Card(i, suit, red));
			else
				deck.push_back(Card(i, suit, black));
		}
	}
}

void Deck::popFront()
{
	deck.pop_front();
}

void Deck::printDeck()
{
	Card aCard;
	for (auto itr = deck.begin(); itr != deck.end(); itr++)
	{
		aCard = *itr;
		cout << aCard;
	}
}

int Deck::getSize()
{
	return deck.size();
}

Card Deck::newCard()
{
	Card aCard = *deck.begin();
	deck.push_back(aCard);
	deck.pop_front();
	return deck.front();
}

void Deck::shuffleDeck()
{
	//random_shuffle(deck.begin(), deck.end());
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}

Card Deck::deal()
{
	deck.pop_front();
	Card aCard = deck.front();
	//deck.pop_front();
	return aCard;
}