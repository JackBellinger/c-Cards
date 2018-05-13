#include "Deck.h"

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

const string Card::spade = "\xe2\x99\xa0";
const string Card::club = "\xe2\x99\xa3";
const string Card::heart = "\xe2\x99\xa5";
const string Card::diamond = "\xe2\x99\xa6";
const string Card::pics[4] = {Card::spade, Card::heart, Card::diamond, Card::club};

const string Card::startColor = "\033[1;30;47m";
const string Card::endColor = "\033[0m";
const string Card::blankLine = "│         │";

Card::Card(int r, int s)
{
	rank = r;
	suit = s;
	oneSuitLine = "│    " + pics[suit] + "    │";
	twoSuitLine = "│  " + pics[suit] + "   " + pics[suit] + "  │";
}
string Card::getRow(int row)
{
	string rankStr = " " + std::to_string(rank);
	if(rank == 1) rankStr = pics[suit] + "A";
	if(rank == 10) rankStr = "10";//need to do this so an extra space doesn't get added
	if(rank == 11) rankStr = pics[suit] + "J";
	if(rank == 12) rankStr = pics[suit] + "Q";
	if(rank == 13) rankStr = pics[suit] + "K";

	switch(row)
	{
		case 0: 
			return "┌─────────┐";
		case 1: 
			return string("│") + rankStr + string("       │");
		case 2: 
			if(rank == 3)
				return oneSuitLine;
			if(rank >= 4 && rank <= 10)
				return twoSuitLine;
			else
				return blankLine;
		case 3:
			if(rank == 2 || (rank >= 7 && rank <= 10))
				return oneSuitLine;
			else
				return blankLine;
		case 4:
			if(rank == 9 || rank == 10)
				return twoSuitLine;
			else
				return blankLine;
		case 5:
			if(rank == 1 || rank == 3 || rank == 5)
				return oneSuitLine;
			if(rank == 6 || rank == 7 || rank == 8)
				return twoSuitLine;
			else
				return blankLine;
		case 6:
			if(rank == 9 || rank == 10)
				return twoSuitLine;
			else
				return blankLine;
		case 7:
			if(rank == 2 || rank == 8 || rank == 10)
				return oneSuitLine;
			else
				return blankLine;
		case 8:
			if(rank == 3)
				return oneSuitLine;
			if(rank >= 4 && rank <= 10)
				return twoSuitLine;
			else
				return blankLine;
		case 9:
			return string("│       ") + rankStr + string("│");
		case 10:
			return "└─────────┘";
	}
}
Deck::Deck()
{
	for(int i = 0; i < 52; i++)
	{
		Card newCard = Card((i%13)+1, (i/13));
		cards[i] = newCard;
	}
}

Card Deck::drawCard()
{
	Card rCard = cards[nextCard];
	nextCard++;
	if(nextCard == 52)
		cout << "Last Card" << endl;
	return rCard;
}

void Deck::shuffle()
{
	int rnum;
	srand(time(0));
	srand( (unsigned)time(NULL));
	for(int i = 0; i < 52; i++)
	{
		rnum = (rand() % 51) + 1;
		//cout << "swapping " << i << " and " << rnum << endl;
		swap(i, rnum);
	}
	nextCard = 0;
}

void Deck::printDeck()
{
	cout << sizeof(cards) / sizeof(cards[0]) << endl;
	for(int i = 0; i < 52; i++)
		cout << "card #" << i + 1 << " = " << cards[i]<< endl;
	cout << "done" << endl;
}

void Deck::swap(int x, int y)
{
		Card temp = cards[x];
		cards[x] = cards[y];
		cards[y] = temp;
}
ostream& operator << (ostream& os, Card const& card)
{
	
	if(card.rank == 1)
		os << "A" << card.pics[card.suit];
	else if(card.rank == 11)
		os << "J" << card.pics[card.suit];
	else if(card.rank == 12)
		os << "Q" << card.pics[card.suit];
	else if(card.rank == 13)
		os << "K" << card.pics[card.suit];
	else
    	os << card.rank << card.pics[card.suit];
	return os;
}

bool Card::operator < (const Card compare)
{
	if(suit <= compare.suit)
		return (rank < compare.rank || suit < compare.suit);
	else
		return false;
}
bool Card::operator > (const Card compare)
{
	if(suit >= compare.suit)
		return (rank > compare.rank || suit > compare.suit);
	else
		return false;
}
bool Card::operator <= (const Card compare)
{
	if(suit <= compare.suit)
		return (rank <= compare.rank || suit < compare.suit);
	else
		return false;
}
bool Card::operator >= (const Card compare)
{
	if(suit >= compare.suit)
		return (rank >= compare.rank || suit > compare.suit);
	else
		return false;
}
bool Card::operator == (const Card compare)
{
	return (suit == compare.suit) && (rank == compare.rank);
}
bool Card::operator != (const Card compare)
{
	return !((suit == compare.suit) && (rank == compare.rank));
}
//Card Card::operator [] (int at){return cards[at];}

