#include "Deck.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const char Card::spade[4] = "\xe2\x99\xa0";
const char Card::club[4] = "\xe2\x99\xa3";
const char Card::heart[4] = "\xe2\x99\xa5";
const char Card::diamond[4] = "\xe2\x99\xa6";
const char* Card::pics[4] = {Card::spade, Card::heart, Card::diamond, Card::club};

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
		rnum = rand() % 52 + 1;
		swap(i, rnum);
	}
	nextCard = 0;
}

void Deck::printDeck()
{
	cout << sizeof(cards) / sizeof(cards[0]) << endl;
	for(int i = 0; i < 52; i++)
		cout << "card #" << i + 1 << " = " << cards[i]<< endl;
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

