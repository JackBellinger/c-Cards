#include "Game.h"
#include "Deck.h"

Game::Game(){}
Poker::Poker()
{
	//playerHand.resize(5);
}
BlackJack::BlackJack()
{
	//playerHand.resize(2);
	//dealerHand.resize(2);
}
void Game::gameLoop()
{
	cout << "Enter an amount of money to play: ";
	cin >> playerMoney;
	
	//cout << "Do you want to play a round? (Y/N): ";
	char response = 'Y';
	//cin >> response;
	bool quit = (response == 'Y' || response == 'y')? false : true;
	if(response == 't')
		test();
	while(!quit)
	{
		string(5, '\n');
		quit = round();
	}
}
bool Game::round()
{
	cout << "How much do you want to bet? ";
	cin >> bet;
	while(bet > playerMoney)
	{
		cout << "Please bet an amount that is less than your total money: ";
		cin >> bet;
	}
	playerMoney -= bet;
	deck.shuffle();
	deal();
	int winnings = handValue();
	cout << "Your initial balance was: $" << playerMoney + bet << endl;
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
		Card dealt = deck.drawCard();
		cout << dealt << ": Hold (1) or Redraw (0)? ";
		bool response = true;
		cin >> response;
		if(response)
			playerHand.push_back(dealt);
		else
			playerHand.push_back(deck.drawCard());
	}
	sortHand();
	printHand();
}
void Poker::sortHand()
{
	for(int a = 0; a < 5; a++)
	{
		int min = a;
		for(int b = a + 1; b < 5; b++)
			if(playerHand[b] < playerHand[min])
				min = b;
		Card temp = playerHand[min];
		playerHand[min] = playerHand[a];
		playerHand[a] = temp;
		
	}
}
void Poker::printHand()
{
	cout << "Your hand: ";
	for(int i = 0; i < 5; i++)
		cout << playerHand[i] << " ";
	cout << endl;
}
int Poker::handValue()
{
	int reward = 0;

	int numRanks[14] = {0};
	int numSuits[4] = {0};
	bool highCard = 0, x2pair = 0, x3pair = 0, straight = 0, flush = 0, fullHouse = 0, x4pair = 0, straightFlush = 0, royalFlush = 0;

	for(int i = 0; i < 5; i++)//tally how many of each rank and suit there are in the hand
	{
		numRanks[playerHand[i].rank]++;
		numSuits[playerHand[i].suit]++;
	}
	//for(int i = 0; i < 14; i++)
		//cout << "number of " << i << " cards: " << numRanks[i] << endl;
	if(numRanks[11] >= 1 || numRanks[12] >= 1 || numRanks[13] >= 1)  //jack or higher
		highCard = true;

	for(int i = 0; i < 13; i++)
	{
		if(numRanks[i] == 2)  //2 pair
			x2pair = true;
		
		if(numRanks[i] == 3)  //3 pair
			x3pair = true;
		
		for(int s = 0; (s < 5) && (i+s <= 13); s++)  //straight
		{
			if(numRanks[i+s] != 1)  //if theres anything except 1 of each of the 5 ranks after then there can't be a straight
				break;
			else if(s == 4)
				straight = true;
		}
		
		if(numRanks[i] == 4) //4 pair
			x4pair = true;
	}
	for(int f = 0; f < 4; f++)  //flush
	{
		if(numSuits[f] == 5)
			flush = true;
	}
	if(x2pair && x3pair)  //full house
		fullHouse = true;

	if(straight && flush)  //straight flush
		straightFlush = true;

	if(straightFlush && numRanks[13] >= 1)  //royal flush
		royalFlush = true;

	//check which hands were found and set the correct reward
	string result = "no winning hand";
	if(highCard)
	{
		result = "face card";
		reward = 1;
	}
	if(x2pair)
	{
		result = "two pair";
		reward = 2;
	}
	if(x3pair)
	{
		result = "three pair";
		reward = 4;
	}
	if(straight)
	{
		result = "straight";
		reward = 6;
	}
	if(flush)
	{
		result = "flush";
		reward = 8;
	}
	if(fullHouse)
	{
		result = "full house";
		reward = 10;
	}
	if(x4pair)
	{
		result = "four pair";
		reward = 20;
	}
	if(straightFlush)
	{
		result = "straight flush";
		reward = 1000;
	}
	if(royalFlush)
	{
		result = "royal flush";
		reward = 10000;
	}
	cout << "You got a " << result << endl;
	return bet * reward;
		
}

void Poker::test()
{
	bet = 1;

	//high card
	playerHand.push_back(Card(1, 0));
	playerHand.push_back(Card(3, 1));
	playerHand.push_back(Card(7, 2));
	playerHand.push_back(Card(9, 3));
	playerHand.push_back(Card(11, 3));
	printHand();
	cout << "reward: x" << handValue() << endl << endl;
	playerHand.clear();

	//2 pair
	playerHand.push_back(Card(1, 0));
	playerHand.push_back(Card(1, 1));
	playerHand.push_back(Card(2, 2));
	playerHand.push_back(Card(3, 3));
	playerHand.push_back(Card(13, 3));
	printHand();
	cout << "reward: x" << handValue() << endl << endl;
	playerHand.clear();


	//3 pair
	playerHand.push_back(Card(1, 1));
	playerHand.push_back(Card(1, 2));
	playerHand.push_back(Card(1, 3));
	playerHand.push_back(Card(3, 3));
	playerHand.push_back(Card(12, 3));
	printHand();
	cout << "reward: x" << handValue() << endl << endl;
	playerHand.clear();


	//straight
	playerHand.push_back(Card(1, 1));
	playerHand.push_back(Card(2, 2));
	playerHand.push_back(Card(3, 3));
	playerHand.push_back(Card(4, 0));
	playerHand.push_back(Card(5, 3));
	printHand();
	cout << "reward: x" << handValue() << endl << endl;
	playerHand.clear();


	//flush
	playerHand.push_back(Card(1, 3));
	playerHand.push_back(Card(2, 3));
	playerHand.push_back(Card(7, 3));
	playerHand.push_back(Card(9, 3));
	playerHand.push_back(Card(10, 3));
	printHand();
	cout << "reward: x" << handValue() << endl << endl;
	playerHand.clear();


	//full house
	playerHand.push_back(Card(1, 1));
	playerHand.push_back(Card(1, 2));
	playerHand.push_back(Card(1, 3));
	playerHand.push_back(Card(2, 2));
	playerHand.push_back(Card(2, 3));
	printHand();
	cout << "reward: x" << handValue() << endl << endl;
	playerHand.clear();


	//4 pair
	playerHand.push_back(Card(1, 0));
	playerHand.push_back(Card(1, 1));
	playerHand.push_back(Card(1, 2));
	playerHand.push_back(Card(1, 3));
	playerHand.push_back(Card(11, 3));
	printHand();
	cout << "reward: x" << handValue() << endl << endl;
	playerHand.clear();


	//straight flush
	playerHand.push_back(Card(1, 0));
	playerHand.push_back(Card(2, 0));
	playerHand.push_back(Card(3, 0));
	playerHand.push_back(Card(4, 0));
	playerHand.push_back(Card(5, 0));
	printHand();
	cout << "reward: x" << handValue() << endl << endl;
	playerHand.clear();


	//royal flush
	playerHand.push_back(Card(9, 1));
	playerHand.push_back(Card(10, 1));
	playerHand.push_back(Card(11, 1));
	playerHand.push_back(Card(12, 1));
	playerHand.push_back(Card(13, 1));
	printHand();
	cout << "reward: x" << handValue() << endl << endl;
	playerHand.clear();



}

void BlackJack::deal()
{
	playerHand.clear();
	playerSum = 0;
	dealerHand.clear();
	dealerSum = 0;

	dealerHand.push_back(deck.drawCard());
	dealerHand.push_back(deck.drawCard());
	dealerSum += dealerHand[0].rank + dealerHand[1].rank;
	
	playerHand.push_back(deck.drawCard());
	playerHand.push_back(deck.drawCard());
	playerSum += playerHand[0].rank + playerHand[1].rank;
	
	cout << "Dealer's first card: " << dealerHand[0] << endl;	
	if(dealerHand[0].rank == 1)
	{
		cout << "You need to bet insurance" << endl;
		insurance = bet / 2;
		cout << "Dealer's second card: " << dealerHand[1] << endl;
		if(dealerSum == 21 || dealerHand[1].rank == 10)
		{
			cout << "BlackJack! " << endl;
			playerMoney += 2 * insurance;
		}
	}
	
	printPlayerHand();
	if(playerSum == 21 || ( playerSum == 11 && (playerHand[0].rank == 1 || playerHand[1].rank == 1)))
		cout << "BlackJack! " << endl;
	else if(dealerSum != 21)
	{
		bool hold = false;
		
		cout << "Would you like to hit(0) or hold(1)? : ";
		cin >> hold;
		while(!hold && playerSum < 21)
		{
			Card dealt = deck.drawCard();
			playerHand.push_back(dealt);
			playerSum += dealt.rank;
			printPlayerHand();
			if(playerSum > 21)
			{
				cout << "Bust! You lose" << endl;
				return;
			}
			cout << "hit(0) or hold(1)? : ";
			cin >> hold;
		}
		while(dealerSum <= 16)
		{
			Card dealt = deck.drawCard();
			dealerHand.push_back(dealt);
			dealerSum += dealt.rank;
			printDealerHand();
			if(dealerSum > 21)
			{
				cout << "Bust! You win" << endl;
				dealerSum = 0;
				return;
			}
		}
			
	}
	
}
void BlackJack::printDealerHand()
{
	cout << endl << "Dealer's total: " << dealerSum << " | Hand: ";
	vector<Card>::iterator it;
	for(it = dealerHand.begin(); it != dealerHand.end(); it++)
		cout << *it << " ";
	cout << endl;
}
void BlackJack::printPlayerHand()
{
	cout << endl << "Your total: " << playerSum << " | Hand: ";
	vector<Card>::iterator it;
	for(it = playerHand.begin(); it != playerHand.end(); it++)
		cout << *it << " ";
	cout << endl;
}
int BlackJack::handValue()
{
	int reward = 0;
	if(playerSum <= 21)
	{								//the player gets blackjack on ace + 10
		if(playerSum == 21 || ( playerSum == 11 && (playerHand[0].rank == 1 || playerHand[1].rank == 1)))
			reward = bet * 2.5;
		if(playerSum > dealerSum)
			reward = bet * 2;
		if(playerSum == dealerSum)
			reward = bet;
	}
	if(reward > 0)
		cout << "You won $" << reward << endl;
	else
		cout << "You lost" << endl;
	return reward;
}

void BlackJack::test()
{

}












