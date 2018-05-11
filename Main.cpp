#include "Game.h"
#include "Deck.h"

using namespace std;

int main()
{
	Poker p = Poker();
	BlackJack b = BlackJack();

	cout << "Welcome to Casino Game!" << endl;
	cout << "Play Poker or BlackJack?" << endl;
	cout << "Poker (P), BlackJack (B)" << endl << ": ";
	char response;
	cin >> response;
	bool playPoker = (response == 'P' || response == 'p')? true : false;
	if(playPoker)
		p.gameLoop();
	else
		b.gameLoop();
	return 0;
}
