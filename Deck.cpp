#include "Deck.h"
#include <iostream>
#include <cstring>

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

void Deck::printDeck()
{
	for(int i = 0; i < 52; i++)
		cout << cards[1].suit << " " << cards[i].num << endl;
}
