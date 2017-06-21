#include "card.h"

Card::Card() :
value{ 0 },
suit{ clubs },
color{ red },
show{ false }

{}

Card::Card(int value, st suit, clr color) :
value{ value },
suit{ suit },
color{ color },
show{ false }
{}

void Card::flipCard()
{
	show = true;
}

int Card::getVal()
{
	return value;
}

st Card::getSuit()
{
	return suit;
}

clr Card::getColor()
{
	return color;
}

bool Card::getShow()
{
	return show;
}

ostream& operator<<(ostream& out, const Card& card)
{
	if (card.show == false)
	{
		out << left << setw(18) << "xx ";
		return out;
	}

	out << left << setw(3);
	switch (card.value)
	{
	case 1: out << "Ace";
		break;
	case 2: out << "2";
		break;
	case 3: out << "3";
		break;
	case 4: out << "4";
		break;
	case 5: out << "5";
		break;
	case 6: out << "6";
		break;
	case 7: out << "7";
		break;
	case 8: out << "8";
		break;
	case 9: out << "9";
		break;
	case 10: out << "10";
		break;
	case 11: out << "J";
		break;
	case 12: out << "Q";
		break;
	case 13: out << "K";
		break;
	}
	out << setw(9);
	switch (card.suit)
	{
	case clubs: out << " club ";
		break;
	case diamonds: out << " diamond ";
		break;
	case hearts: out << " heart ";
		break;
	case spades: out << " spade ";
		break;
	}

	out << setw(6);
	switch (card.color)
	{
	case red: out << "red ";
		break;
	case black: out << "black ";
		break;
	}
	return out;
}

bool operator==(const Card& card1, const Card& card2)
{
	return (card1.value == card2.value && card1.suit == card2.suit && card1.color == card2.color);
}
