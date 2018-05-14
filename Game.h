#ifndef GAME_H
#define GAME_H
#include "Deck.h"
#include <vector>
#include <string>
class Game
{
	protected:
		int playerMoney;
		vector<Card> playerHand;
		int bet;
		Deck deck;
		void printHand(vector<Card>, int = 0);
		bool round();
		virtual void deal() = 0;
		virtual int reward() = 0;
		virtual void test() = 0;
		virtual void clearScreen(int = 40) = 0;

	public:	
		Game();
		int gameLoop(int = 1000);	
};

class Poker: public Game
{
	public:
		Poker();
	private:
		vector<Card> playerHand;
		void deal();
		void sortHand();
		int reward();
		void test();
		void clearScreen(int = 40);
};

class BlackJack : public Game
{
	public:
		BlackJack();
	private:
		int insurance;
		vector<Card> dealerHand;
		int dealerSum;
		vector<Card> playerHand;
		int playerSum;

		void printDealerHand(int = 0);
		void printPlayerHand();

		void deal();
		int handSum(vector<Card>);
		int reward();
		void test();
		void clearScreen(int = 40);
};
#endif
