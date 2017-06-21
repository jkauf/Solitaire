#ifndef DECK_H
#define DECK_h

#include <deque>
#include <algorithm>
#include <random>
#include <chrono>
#include "card.h"


class Deck
{
public:
	Deck();
	void buildDeck();
	void printDeck();
	void shuffleDeck();
	void popFront();
	Card newCard();
	Card deal();
	int getSize();
private:
	deque<Card> deck;
};

#endif