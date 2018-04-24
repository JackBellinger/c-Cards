#include "Deck.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

Deck::Deck()
{
	for(int i = 0; i < 52; i++)
	{
		Card newCard = Card((i%13)+1, (i/13)+1);
		cards.push_back(newCard);
		cout << i << " suit: " << newCard.suit << ", value: " << newCard.num << endl;
	}
}

Card* Deck::drawCard()
{
	Card rCard = cards[nextCard];
	nextCard++;
	return rCard;
}

void Deck::shuffle()
{
	for(int i = 0; i < 52; i++)
	{
		int rnum;
		srand(time(0));
		srand( (unsigned)time(NULL));
		rnum = rand() % 52 + 1;
		Card temp = cards[rnum];
		cards[rnum] = cards[i];
		cards[i] = temp;
	}
	nextCard = 0;
}

void Deck::printDeck()
{
	for(int i = 0; i < 52; i++)
		cout << cards[1].suit << " " << cards[i].num << endl;
}

