#include "Game.h"
#include "Deck.h"

using namespace std;

inline int pow(int base, int exponent)
{
	int product = 1;
	for(int i = 0; i < exponent; i++)
		product *= base;
	return product;
}
char clearScreen(int money)
{
	cout << "clear" << string(10, '\n');
	int moneyDigits = 0;
	while(pow(10, moneyDigits) <= money)
		moneyDigits++;
	cout << "┌───────────────────────────────────────┐" << endl;
	cout << "│Welcome to Jackson's Casino Game!      │" << endl;
	cout << "│Your current balance is $" << money; cout << "." << string( (13 - moneyDigits), ' ') << "│ " << endl;
	cout << "└───────────────────────────────────────┘" << endl;
	cout << string(27, '\n');
	cout << "Please make sure your terminal window is tall enough" << endl;
	cout << "Play Poker or BlackJack?" << endl;
	cout << "Poker (P), BlackJack (B), Quit(Q) : ";
	char response;
	cin >> response;
	return response;
}

int main()
{
	Poker p = Poker();
	BlackJack b = BlackJack();

	bool quit = false;
	int money = 100;
	while(!quit)
	{
		char response = clearScreen(money);
		bool playPoker = (response == 'P' || response == 'p')? true : false;
		bool playBlackJack = (response == 'B' || response == 'b')? true : false;
		quit = (response == 'Q' || response == 'q')? true : false;
		if(playPoker)
			money = p.gameLoop(money);
		else if(playBlackJack)
			money = b.gameLoop(money);
	}
	return 0;
}

