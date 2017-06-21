#ifndef GAME_H
#define GAME_H

#include <list>

#include "deck.h"

class Game
{
public:
	Game();
	void setup();
	void run();
	void printMenu();
	void printBoard();
	void printField();
	void printDeckAndDiscard();
	bool fieldToDiscard(char* src, char* dst);
	bool fieldToField(char* src, char* dst, char* num);
	bool deckToDiscard(char* dst);
	bool deckToField(char* dst);
	bool handleInput();

private:
	list<Card> field[7];
	list<Card> discard[4];
	Deck deck;
	int fieldSize = 0;
	unsigned int maxColumn = 7;
	Card drawnCard;

};

#endif