#ifndef CARDS_H
#define CARDS_H
#include <vector>
using namespace std;

struct Card
{
	int num;
	int suit;
	Card(int n = 0, int s = 0){num = n; suit = s;}
};

class Deck
{
private:
	vector<Card> cards;
	int nextCard;
public:
	Deck();
	void shuffle();
	Card getCard();
	void drawCard();
	void printDeck();
	
	const char spade[4] = "\xe2\x99\xa0";
	const char club[4] = "\xe2\x99\xa3";
	const char heart[4] = "\xe2\x99\xa5";
	const char diamond[4] = "\xe2\x99\xa6";

};
#endif
