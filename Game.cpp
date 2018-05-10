#include "Game.h"
#include "Deck.h"
#include <iostream>

Game::Game()
{
	welcomeMessage = "";
	playerMoney = 0;
	deck = Deck();
}
Poker::Poker()
{
	//Game();
	welcomeMessage = (char*)"Welcome to Casino Poker Game!";
	deck = Deck();
}

void Poker::gameLoop()
{
	cout << welcomeMessage << endl;
	cout << "Enter an amount of money to play: ";
	cin >> playerMoney;
	
	cout << "Do you want to play a round? (Y/N): ";
	char response = 'Y';
	cin >> response;
	bool quit = (response == 'Y' || response == 'y')? false : true;

	while(!quit)
	{
		string(5, '\n');
		quit = round();
	}
}
bool Poker::round()
{
	cout << "How much do you want to bet? " << endl;
	cin >> bet;
	deck.shuffle();
	deal();
	int winnings = bet * handValue();
	if(winnings > 0)
		cout << "You win! : $" << winnings << endl;
	else if(winnings < 0)
		cout << "You lost :( $" << winnings << endl;

	cout << "Your initial balance was: $" << playerMoney << endl;
	playerMoney += winnings;
	cout << "Your current balance is: $" << playerMoney << endl;

	cout << "Would you like to play again? (Y/N) : ";
	char response = 'Y';
	cin >> response;
	return (response == 'Y' || response == 'y')? false : true;
	 
}
void Poker::deal()
{
	for(int i = 0; i < 5; i++)
	{
		Card* dealt = deck.drawCard();
		cout << *dealt << ": Hold (1) or Redraw (0)? ";
		bool response = true;
		cin >> response;
		if(response)
			playerHand[i] = dealt;
		else
			playerHand[i] = deck.drawCard();
	}
	sortHand();
	cout << "Your hand: ";
	for(int i = 0; i < 5; i++)
		cout << *playerHand[i] << ", ";
	cout << endl;
}
void Poker::sortHand()
{
	for(int a = 0; a < 5; a++)
	{
		int min = a;
		for(int b = a + 1; b < 5; b++)
			if(*playerHand[b] < *playerHand[min])
				min = b;
		Card* temp = playerHand[min];
		playerHand[min] = playerHand[a];
		playerHand[a] = temp;	
		
	}
}
int Poker::handValue()
{
	int reward = -1; // this is -1 so that if there is no hand found the player loses the bet money

	int numRanks[13] = {0};
	int numSuits[4] = {0};
	bool foundHands[9] = {false};

	for(int i = 0; i < 5; i++)//tally how many of each rank and suit there are in the hand
	{
		numRanks[playerHand[i]->rank]++;
		numSuits[playerHand[i]->suit]++;
	}

	if(numRanks[11] >= 1 || numRanks[12] >= 1 || numRanks[13] >= 1)  //jack or higher
		foundHands[0] = true;

	for(int i = 0; i < 13; i++)
	{
		if(numRanks[i] == 2)  //2 pair
			foundHands[1] = true;
		
		if(numRanks[i] == 3)  //3 pair
			foundHands[2] = true;
		
		for(int s = 0; (s < 5) && (i+s < 13); s++)  //straight
		{
			if(numRanks[i+s] != 1)  //if theres anything except 1 of each of the 5 ranks after then there can't be a straight
				break;
			else if(s == 4)
				foundHands[3] = true;
		}
		
		if(numRanks[i] == 4) //4 pair
			foundHands[6] = true;
	}
	for(int f = 0; f < 4; f++)  //flush
	{
		if(numSuits[f] == 5)
			foundHands[4] = true;
	}
	if(foundHands[1] && foundHands[2])  //full house
		foundHands[5] = true;

	if(foundHands[3] && foundHands[4])  //straight flush
		foundHands[7] = true;

	if(foundHands[7] && numRanks[13] == 1)  //royal flush
		foundHands[8] = true;

	//check which hands were found and set the correct reward
	if(foundHands[0])
	{
		cout << "You have a face card" << endl;
		reward = 1;
	}
	if(foundHands[1])
	{
		cout << "You have a two pair" << endl;
		reward = 2;
	}
	if(foundHands[2])
	{
		cout << "You have a three pair" << endl;
		reward = 4;
	}
	if(foundHands[3])
	{
		cout << "You have a straight" << endl;
		reward = 6;
	}
	if(foundHands[4])
	{
		cout << "You have a flush" << endl;
		reward = 8;
	}
	if(foundHands[5])
	{
		cout << "You have a full house" << endl;
		reward = 10;
	}
	if(foundHands[6])
	{
		cout << "You have a four pair" << endl;
		reward = 20;
	}
	if(foundHands[7])
	{
		cout << "You have a straight flush!" << endl;
		reward = 1000;
	}
	if(foundHands[8])
	{
		cout << "You have a ROYAL FLUSH!" << endl;
		reward = 10000;
	}
	
	return reward;
		
}





















