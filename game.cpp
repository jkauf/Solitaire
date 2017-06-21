#include "game.h"

Game::Game()
{
	setup();
}

void Game::setup()
{

	int columnSize = 0;
	int arrSize = 7;
	Card aCard;
	drawnCard = deck.deal();
	drawnCard.flipCard();
	for (int i = 0; i < arrSize; ++i)
	{
		++columnSize;
		for (int j = 0; j < columnSize; ++j)
		{
			if (!field[i].empty())
			{
				for (auto itr = field[i].begin(); itr != field[i].end(); ++itr)
				{
					aCard = *itr;
				}

				while (drawnCard.getColor() == aCard.getColor())
				{
					drawnCard = deck.newCard();
				}
				field[i].push_back(drawnCard);
				deck.popFront();
				drawnCard = deck.newCard();
				++fieldSize;
			}
			else if(field[i].empty())
			{
				if (columnSize == (j + 1))
					drawnCard.flipCard();
				field[i].push_back(drawnCard);
				deck.popFront();
				drawnCard = deck.newCard();
				++fieldSize;
			}
		}
	}

}

void Game::run()
{
	bool finished = false;
	while (!finished)
	{ 
		printBoard();
		finished = handleInput();
		system("cls");
	}
}



bool Game::handleInput()
{
	int select = 0;
	bool status = false;
	int i = 0;
	cin >> select;
	if (!cin)
	{
		cin.clear();
		cin.ignore();
		return false;
	}
	if (select < 0 || select > 6)
		return false;
	char src[5];
	char dst[5];
	char val[5];
	cin.ignore(8192, '\n');

	switch (select)
	{ 
		case 1: drawnCard = deck.newCard();
			return false;
			break;
		case 2: //deck to field
			cout << "\nEnter Destination Column(1-7): ";
			cin.get(dst, 8192, '\n');
			cin.ignore(8192, '\n');
			status = deckToField(dst);
			return false;
			break;
		case 3: //deck to discard
			cout << "\nEnter Destination Column(A-D): ";
			cin.get(dst, 8192, '\n');
			cin.ignore(8192, '\n');
			i = 0;
			/*
			while (dst[i])
			{
				tolower(dst[i]);
				++i;
			}
			*/

			status = deckToDiscard(dst);
			return false;
			break;
		case 4: //field to discard
			cout << "Enter Source Column(1-7): ";
			cin.get(src, 8192, '\n');
			cin.ignore(8192, '\n');
			cout << "\nEnter Destination Column(A-D): ";
			cin.get(dst, 8192, '\n');
			cin.ignore(8192, '\n');
			i = 0;
			while (dst[i])
			{
				tolower(dst[i]);
				++i;
			}
			status = fieldToDiscard(src, dst);
			if (!status)
			{
				cout << "Can't place that there" << endl;
			}
			return false;
			break;
		case 5: //field to field
			cout << "Enter Source Column(1-7): ";
			cin.get(src, 8192, '\n');
			cin.ignore(8192, '\n');
			cout << "Enter value to move: ";
			cin.get(val, 8192, '\n');
			cin.ignore(8192, '\n');
			cout << "Enter Destination Column(1-7): ";
			cin.get(dst, 8192, '\n');
			cin.ignore(8192, '\n');
			i = 0;
			while (val[i])
			{
				tolower(val[i]);
				++i;
			}
			i = 0;
			while (dst[i])
			{
				tolower(dst[i]);
				++i;
			}
			status = fieldToField(src, dst, val);
			return false;
			break;
		case 6: //quit
			return true;
			break;
		default: 
			return false;
			break;

	}
		

}

bool Game::fieldToField(char* src, char* dst, char* num)
{
	int source = atoi(src) - 1;
	int dest = atoi(dst) - 1;
	int val = 0;
	if (strcmp(num, "k") == 0 || strcmp(num, "K") == 0)
		val = 13;
	else if (strcmp(num, "q") == 0 || strcmp(num, "Q") == 0)
		val = 12;
	else if (strcmp(num, "j") == 0 || strcmp(num, "J") == 0)
		val = 11;
	else if (strcmp(num, "ace") == 0)
		val = 1;
	else
		val = atoi(num);

	if (source < 0 || source > 6 || dest < 0 || source > 6 || val < 1 || val > 13)
		return false;

	Card srcCard;
	Card dstCard;
	if (!field[dest].empty())
		dstCard = field[dest].back();
	auto itr = field[source].begin();
	for (; itr != field[source].end() && srcCard.getVal() != val; ++itr)
	{
			srcCard = *itr;
			if (srcCard.getVal() == val && srcCard.getShow() == false)
			{
				++itr;
				srcCard = *itr;
			}
	}
	--itr;

	//king to empty column
	if (srcCard.getVal() == 13 && field[dest].empty())
	{
		field[dest].splice(field[dest].begin(), field[source], itr, field[source].end());
		if (field[dest].size() > maxColumn)
			maxColumn = field[dest].size() + 1;
		return true;
	}
	else if (srcCard.getVal() == (dstCard.getVal() - 1) && srcCard.getSuit() != dstCard.getSuit())
	{
		field[dest].splice(field[dest].end(), field[source], itr, field[source].end());
		if (field[dest].size() > maxColumn)
			maxColumn = field[dest].size() + 1;
		return true;
	}

	return false;
}

bool Game::fieldToDiscard(char* src, char* dst)
{
	int source = atoi(src) - 1;
	if (source < 0 || source > 6)
		return false;
	int dest = 0;
	Card srcCard;
	Card dstCard;

	for (auto itr = field[source].begin(); itr != field[source].end(); ++itr)
	{
		srcCard = *itr;
	}

	if (strcmp(dst, "a") == 0 || strcmp(dst, "A") == 0)
		dest = 0;
	else if (strcmp(dst, "b") == 0 || strcmp(dst, "B") == 0)
		dest = 1;
	else if (strcmp(dst, "c") == 0 || strcmp(dst, "C") == 0)
		dest = 2;
	else if (strcmp(dst, "d") == 0 || strcmp(dst, "D") == 0)
		dest = 3;
	else
		return false;

	if (discard[dest].empty() && srcCard.getVal() == 1)
	{
		discard[dest].push_back(srcCard);
		field[source].pop_back();
		if (!field[source].empty())
		{
			for (auto itr = field[source].begin(); itr != field[source].end(); ++itr)
			{
				srcCard = *itr;
			}
			srcCard.flipCard();
		}
		return true;
	}

	for (auto itr = discard[dest].begin(); itr != discard[dest].end(); ++itr)
	{
		dstCard = *itr;
	}

	if (srcCard.getSuit() == dstCard.getSuit() && srcCard.getVal() == (dstCard.getVal() + 1))
	{
		discard[dest].push_back(srcCard);
		field[source].pop_back();
		if (!field[source].empty())
		{
			for (auto itr = field[source].begin(); itr != field[source].end(); ++itr)
			{
				srcCard = *itr;
			}
			srcCard.flipCard();
		}
		return true;
	}


	return false;
}

bool Game::deckToDiscard(char* dst)
{
	Card aCard = drawnCard;
	int dest = 0;
	if (strcmp(dst, "a") == 0 || strcmp(dst, "A") == 0)
		dest = 0;
	else if (strcmp(dst, "b") == 0 || strcmp(dst, "B") == 0)
		dest = 1;
	else if (strcmp(dst, "c") == 0 || strcmp(dst, "C") == 0)
		dest = 2;
	else if (strcmp(dst, "d") == 0 || strcmp(dst, "D") == 0)
		dest = 3;
	else
		return false;

	if (discard[dest].empty() && drawnCard.getVal() == 1)
	{
		discard[dest].push_back(aCard);
		//deck.popFront();
		drawnCard = deck.deal();
		return true;
	}
	else if (!discard[dest].empty() && drawnCard.getVal() == (discard[dest].back().getVal() + 1) && discard[dest].back().getSuit() == aCard.getSuit())
	{
		discard[dest].push_back(aCard);
		//deck.popFront();
		drawnCard = deck.deal();
		return true;
	}
	else
		return false;
}

void Game::printMenu()
{
	cout << endl << "Options" << endl
		<< "1. Draw another card" << endl
		<< "2. Move from deck to field" << endl
		<< "3. Move from deck to discard" << endl
		<< "4. Move from field to discard" << endl
		<< "5. Move from field to field" << endl
		<< "6. Quit" << endl
		<< "Selection: ";
}

bool Game::deckToField(char* dst)
{
	Card srcCard = drawnCard;
	Card dstCard;
	int dest = atoi(dst) - 1;
	if (dest < 0 || dest > 6)
		return false;

	for (auto itr = field[dest].begin(); itr != field[dest].end(); ++itr)
	{
		dstCard = *itr;
	}

	if (dstCard.getColor() != srcCard.getColor() && srcCard.getVal() == (dstCard.getVal() - 1))
	{
		field[dest].push_back(srcCard);
		//deck.popFront();
		drawnCard = deck.deal();
		if (field[dest].size() > maxColumn)
			maxColumn = field[dest].size();

		return true;
	}
	//empty column and source card is a king
	else if (field[dest].empty() && srcCard.getVal() == 13)
	{
		field[dest].push_back(srcCard);
		//deck.popFront();
		drawnCard = deck.deal();
		return true;
	}

	return false;
}
void Game::printDeckAndDiscard()
{
	Card aCard;
	cout << left << setw(18) << "DECK" << "\tDISCARD "
		<< setw(18) << "A"
		<< setw(18) << "B"
		<< setw(18) << "C"
		<< setw(18) << "D"
		<< endl;
	drawnCard.flipCard();
	cout << setw(18) << drawnCard << "\t\t";

	for (int i = 0; i < 4; i++)
	{
		if (discard[i].empty())
			cout << setw(18) << "Empty";
		else
		{
			//auto itr = discard[i].end();
			for (auto itr = discard[i].begin(); itr != discard[i].end(); ++itr)
			{
				aCard = *itr;
				
			}
			cout << setw(18) << aCard;
		}
	}

	cout << endl << endl;

}

void Game::printBoard()
{
	printDeckAndDiscard();
	printField();
	printMenu();

}

void Game::printField()
{
	Card aCard;
	//int arrSize = 10;
	auto itr0 = field[0].begin();
	auto itr1 = field[1].begin();
	auto itr2 = field[2].begin();
	auto itr3 = field[3].begin();
	auto itr4 = field[4].begin();
	auto itr5 = field[5].begin();
	auto itr6 = field[6].begin();

	cout << "FIELD" << endl
		<< setw(18) << left << "1"
		<< setw(18) << left << "2"
		<< setw(18) << left << "3"
		<< setw(18) << left << "4"
		<< setw(18) << left << "5"
		<< setw(18) << left << "6"
		<< setw(18) << left << "7"
		<< endl;


	for (unsigned int i = 0; i < maxColumn; ++i)
	{
		if (itr0 != field[0].end())
		{
			aCard = *itr0;
			if (aCard == field[0].back())
			{
				field[0].back().flipCard();
				aCard.flipCard();
			}
			cout << aCard;
			itr0++;
		}
		else
			cout << setw(18) << setfill(' ') << "";
		if (itr1 != field[1].end())
		{
			aCard = *itr1;
			if (aCard == field[1].back()) 
			{
				field[1].back().flipCard();
				aCard.flipCard();
			}
			cout << aCard;
			itr1++;
		}
		else
			cout << setw(18) << setfill(' ') << "";

		if (itr2 != field[2].end())
		{
			aCard = *itr2;
			if (aCard == field[2].back()) 
			{
				field[2].back().flipCard();
				aCard.flipCard();
			}
			cout << aCard;
			itr2++;
		}
		else
			cout << setw(18) << setfill(' ') << "";

		if (itr3 != field[3].end())
		{
			aCard = *itr3;
			if (aCard == field[3].back()) 
			{
				field[3].back().flipCard();
				aCard.flipCard();
			}
			cout << aCard;
			itr3++;
		}
		else
			cout << setw(18) << setfill(' ') << "";

		if (itr4 != field[4].end())
		{
			aCard = *itr4;
			if (aCard == field[4].back()) 
			{
				field[4].back().flipCard();
				aCard.flipCard();
			}
			cout << aCard;
			itr4++;
		}
		else
			cout << setw(18) << setfill(' ') << "";

		if (itr5 != field[5].end())
		{
			aCard = *itr5;
			if (aCard == field[5].back()) 
			{
				field[5].back().flipCard();
				aCard.flipCard();
			}
			cout << aCard;
			itr5++;
		}
		else
			cout << setw(18) << setfill(' ') << "";

		if (itr6 != field[6].end())
		{
			aCard = *itr6;
			if (aCard == field[6].back()) 
			{
				field[6].back().flipCard();
				aCard.flipCard();
			}
			cout << aCard;
			itr6++;
		}
		else
			cout << setw(18) << setfill(' ') << "";

		cout << endl;
	}

}

