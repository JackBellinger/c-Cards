#ifndef GAME_H
#define GAME_H
#include "Deck.h"
class Game
{
protected:
	char* welcomeMessage;
	int playerMoney;
	Deck deck;

public:	
	Game();
	virtual void gameLoop() = 0;
	virtual bool round() = 0;
	virtual void deal() = 0;
	
};

class Poker: public Game
{

private:
	Card* playerHand[5];
	int bet;
	
public:
	Poker();
	void gameLoop();
	bool round();
	void deal();
	void sortHand();
	int handValue();
};
#endif
