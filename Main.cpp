#include "Game.h"
#include "Deck.h"

using namespace std;

int main()
{
	Poker* game = new Poker();
	game->gameLoop();
	return 0;
}
