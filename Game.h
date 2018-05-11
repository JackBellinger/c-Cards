#ifndef GAME_H
#define GAME_H
#include "Deck.h"
#include <vector>
#include <string>
class Game
{
protected:
	int playerMoney;
	int bet;
	Deck deck;
public:	
	Game();
	void gameLoop();
	bool round();
	virtual void deal() = 0;
	virtual int handValue() = 0;
	virtual void test() = 0;
	
};

class Poker: public Game
{
private:
	vector<Card> playerHand;
	
public:
	Poker();

	void deal();
	void sortHand();
	int handValue();
	void test();
	void printHand();
};

class BlackJack : public Game
{
private:
	int insurance;
	vector<Card> dealerHand;
	int dealerSum;
	vector<Card> playerHand;
	int playerSum;

	void printDealerHand();
	void printPlayerHand();

public:
	BlackJack();

	void deal();
	int handValue();
	void test();
};
#endif
