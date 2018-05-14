#include "Game.h"
#include "Deck.h"
Game::Game(){}
Poker::Poker()
{
	
}
BlackJack::BlackJack()
{
	
}
int Game::gameLoop(int money)
{
	playerMoney = money;
	cout << "Current balance: $" << playerMoney << endl;
	cout << "Enter an amount to deposit if you would like: ";
	int deposit = 0;
	cin >> deposit;
	playerMoney += deposit;
	cout << "Do you want to play a round? (Y/N): ";
	char response = 'Y';
	cin >> response;
	bool quit = (response == 'Y' || response == 'y')? false : true;
	if(response == 't')
		test();
	while(!quit)
	{
		string(50, '\n');
		quit = round();
	}
	return playerMoney;
}
bool Game::round()
{
	clearScreen(1);
	cout << "How much do you want to bet? ";
	bet = 100;	
	cin >> bet;
	while(bet > playerMoney)
	{
		cout << "Please bet an amount that is less than your total money: ";
		cin >> bet;
	}
	playerMoney -= bet;
	deck.shuffle();
	
	deal();
	int winnings = reward();
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
	playerHand.clear();
	for(int i = 0; i < 5; i++)
		playerHand.push_back(deck.drawCard());
	clearScreen(13);
	printHand(playerHand);
	for(int i = 0; i < 5; i++)
	{
		cout << "Card #" << i + 1 << ": Hold (0) or Redraw (1)? ";
		bool response = false;
		cin >> response;
		if(response)
		{
			playerHand[i]=deck.drawCard();
		}
	}
	clearScreen(13);
	printHand(playerHand);
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
int Poker::reward()
{
	int reward = 0;

	int numRanks[14] = {0};
	int numSuits[4] = {0};
	bool highPair = 0, x1pair = 0, x2pair = 0, x3pair = 0, straight = 0, flush = 0, fullHouse = 0, x4pair = 0, straightFlush = 0, royalFlush = 0;

	for(int i = 0; i < 5; i++)//tally how many of each rank and suit there are in the hand
	{
		numRanks[playerHand[i].rank]++;
		numSuits[playerHand[i].suit]++;
	}
	//for(int i = 0; i < 14; i++)
		//cout << "number of " << i << " cards: " << numRanks[i] << endl;
	if(numRanks[1] >= 2 || numRanks[11] >= 2 || numRanks[12] >= 2 || numRanks[13] >= 2)  //jack or better
		highPair = true;
	
	for(int i = 0; i < 13; i++)
	{
		if(numRanks[i] == 2 && x1pair)  //2 pair
			x2pair = true;
		if(numRanks[i] == 2)
			x1pair = true;
		if(numRanks[i] == 3)  //3 pair
			x3pair = true;
		
		for(int s = 0; (s < 5) && (i+s <= 14); s++)  //straight
		{
			if(numRanks[((i+s-1)%14)+1] != 1)//if theres anything except 1 of each of the 5 ranks after then there can't be a straight
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
	if(highPair)
	{
		result = "a jack or better pair";
		reward = 1;
	}
	if(x2pair)
	{
		result = "a two pair";
		reward = 2;
	}
	if(x3pair)
	{
		result = "a triple";
		reward = 4;
	}
	if(straight)
	{
		result = "a straight";
		reward = 6;
	}
	if(flush)
	{
		result = "a flush";
		reward = 8;
	}
	if(fullHouse)
	{
		result = "a full house";
		reward = 10;
	}
	if(x4pair)
	{
		result = "a four pair";
		reward = 20;
	}
	if(straightFlush)
	{
		result = "a straight flush";
		reward = 1000;
	}
	if(royalFlush)
	{
		result = "a royal flush";
		reward = 10000;
	}
	cout << "You got " << result << endl;
	return bet * reward;
		
}

void Poker::test()
{
	bet = 1;

	//jack or better pair
	playerHand.push_back(Card(1, 0));
	playerHand.push_back(Card(3, 1));
	playerHand.push_back(Card(7, 2));
	playerHand.push_back(Card(11, 0));
	playerHand.push_back(Card(11, 3));
	printHand(playerHand);
	cout << "reward: x" << reward() << endl << endl;
	playerHand.clear();

	//2 pair
	playerHand.push_back(Card(1, 0));
	playerHand.push_back(Card(1, 1));
	playerHand.push_back(Card(2, 2));
	playerHand.push_back(Card(2, 3));
	playerHand.push_back(Card(13, 3));
	printHand(playerHand);
	cout << "reward: x" << reward() << endl << endl;
	playerHand.clear();


	//3 pair
	playerHand.push_back(Card(1, 1));
	playerHand.push_back(Card(1, 2));
	playerHand.push_back(Card(1, 3));
	playerHand.push_back(Card(3, 3));
	playerHand.push_back(Card(12, 3));
	printHand(playerHand);
	cout << "reward: x" << reward() << endl << endl;
	playerHand.clear();


	//straight
	playerHand.push_back(Card(1, 1));
	playerHand.push_back(Card(2, 2));
	playerHand.push_back(Card(3, 3));
	playerHand.push_back(Card(4, 0));
	playerHand.push_back(Card(5, 3));
	printHand(playerHand);
	cout << "reward: x" << reward() << endl << endl;
	playerHand.clear();


	//flush
	playerHand.push_back(Card(1, 3));
	playerHand.push_back(Card(2, 3));
	playerHand.push_back(Card(7, 3));
	playerHand.push_back(Card(9, 3));
	playerHand.push_back(Card(10, 3));
	printHand(playerHand);
	cout << "reward: x" << reward() << endl << endl;
	playerHand.clear();


	//full house
	playerHand.push_back(Card(1, 1));
	playerHand.push_back(Card(1, 2));
	playerHand.push_back(Card(1, 3));
	playerHand.push_back(Card(2, 2));
	playerHand.push_back(Card(2, 3));
	printHand(playerHand);
	cout << "reward: x" << reward() << endl << endl;
	playerHand.clear();


	//4 pair
	playerHand.push_back(Card(1, 0));
	playerHand.push_back(Card(1, 1));
	playerHand.push_back(Card(1, 2));
	playerHand.push_back(Card(1, 3));
	playerHand.push_back(Card(11, 3));
	printHand(playerHand);
	cout << "reward: x" << reward() << endl << endl;
	playerHand.clear();


	//straight flush
	playerHand.push_back(Card(1, 0));
	playerHand.push_back(Card(2, 0));
	playerHand.push_back(Card(3, 0));
	playerHand.push_back(Card(4, 0));
	playerHand.push_back(Card(5, 0));
	printHand(playerHand);
	cout << "reward: x" << reward() << endl << endl;
	playerHand.clear();


	//royal flush
	playerHand.push_back(Card(9, 1));
	playerHand.push_back(Card(10, 1));
	playerHand.push_back(Card(11, 1));
	playerHand.push_back(Card(12, 1));
	playerHand.push_back(Card(13, 1));
	printHand(playerHand);
	cout << "reward: x" << reward() << endl << endl;
	playerHand.clear();



}

void BlackJack::deal()
{
	playerHand.clear();
	playerSum = 0;
	dealerHand.clear();
	dealerSum = 0;
	
	Card dealt;
	for(int i = 0; i < 4; i++)
	{
		dealt = deck.drawCard();
		if(i < 2)
			dealerHand.push_back(dealt);
		else
			playerHand.push_back(dealt);
	}
	playerSum = handSum(playerHand);
	dealerSum = handSum(dealerHand);
	clearScreen(26);
	printDealerHand(1);
	bool dealerBlackJack = false;
	if(dealerHand[1].rank == 1)
	{
		clearScreen(13);
		printDealerHand(1);
		cout << "Would you like to bet insurance? Y(1) / N(0) : " << endl;
		bool response = 1;
		cin >> response;
		if(response)
		{
			insurance = bet / 2;
			playerMoney -= insurance;
			cout << "Insurance: " << insurance << endl;
		}
		if(dealerSum == 21)
		{
			printDealerHand();
			cout << "BlackJack! " << endl;
			playerMoney += 2 * insurance;
			dealerBlackJack = true;
		}
	}
	
	printPlayerHand();
	if(playerSum == 21)
		cout << "BlackJack! " << endl;
	else if(!dealerBlackJack)
	{
		bool hold = false;
		
		cout << "Would you like to hit(0) or hold(1)? : ";
		cin >> hold;
		while(!hold && playerSum < 21)
		{
			clearScreen(28);
			Card dealt = deck.drawCard();
			playerHand.push_back(dealt);
			playerSum = handSum(playerHand);

			printDealerHand(1);
			printPlayerHand();
			if(playerSum > 21)
			{
				cout << "Bust! You lose" << endl;
				return;
			}
			cout << "hit(0) or hold(1)? : ";
			cin >> hold;
		}
		clearScreen(29);
		printPlayerHand();
		while(dealerSum <= 16)
		{
			Card dealt = deck.drawCard();
			dealerHand.push_back(dealt);
			dealerSum = handSum(dealerHand);
		}
		printDealerHand();
		if(dealerSum > 21)
		{
			cout << "Dealer bust! You win" << endl;
			dealerSum = 0;
			return;
		}
			
	}		
	else
	{
		printDealerHand();
		cout << "Dealer got blackjack";
	}
	
}
void BlackJack::printDealerHand(int hidden)
{
	cout << endl << "Dealer's Hand | ";
	if(hidden == 0)
		cout << "Total: " << dealerSum << endl;
	else
		cout << endl;
	printHand(dealerHand, hidden);
}
void BlackJack::printPlayerHand()
{
	cout << endl << "Your Hand | Total: " << playerSum << endl;
	printHand(playerHand);
}
int BlackJack::reward()
{
	int reward = 0;
	if(playerSum <= 21)
	{
		if(playerSum > dealerSum)
			reward = bet * 2;
		if(playerSum == 21)
			reward = bet * 2.5;
		if(playerSum == dealerSum)
			reward = 1;
	}
	if(reward > 0)
		cout << "You won $" << reward << endl;
	else
		cout << "You lost" << endl;
	return bet * reward;
}
int BlackJack::handSum(vector<Card> hand)
{
	vector<Card>::iterator it;
	int sum = 0;
	int ace = false;
	for(it = hand.begin(); it != hand.end(); it++)
	{
		if(it->rank == 1)
			ace ++;
		else if(it->rank >= 10)
			sum += 10;
		else
			sum += it->rank;	
	}	
	for(int i = 0; i < ace; i ++)
		sum += (sum <=10)? 11 : 1;
	return sum;
}
void BlackJack::test()
{

}

void Game::printHand(vector<Card> hand, int numHidden)
{
	vector<Card>::iterator it;
	for(int r = 0; r < 11; r ++)
	{
		string line = Card::startColor;
		for(it = hand.begin(); it != hand.end(); it++)
		{
			int dis = distance(hand.begin(), it);
			if(dis < numHidden)
			{
				if(r == 0)
					line += "┌─────────┐";
				else if(r == 10)
					line += "└─────────┘";
				else if(r % 2 == 0)
					line += "│ $  $  $ │";
				else
					line += "│   $ $   │";
				line += Card::endColor + "   " + Card::startColor;
			}
			else
				line += it->getRow(r) + Card::endColor + "   " + Card::startColor;
		}
		line += Card::endColor + "\n";
		cout << line;
	}
			
}
inline int pow(int base, int exponent)
{
	int product = 1;
	for(int i = 0; i < exponent; i++)
		product *= base;
	return product;
}
void Poker::clearScreen(int height)
{
	cout << "clear" << string(10, '\n');
	int moneyDigits = 0;
	while(pow(10, moneyDigits) <= playerMoney)
		moneyDigits++;
	cout << "┌───────────────────────────────────────┐" << endl;
	cout << "│       Casino Game: Poker Table        │" << endl;
	cout << "│Your current balance is $" << playerMoney;cout << "." << string( (13 - moneyDigits), ' ') << "│ " << endl;
	cout << "└───────────────────────────────────────┘" << endl;
	cout << string(30 - height, '\n');
}

void BlackJack::clearScreen(int height)
{
	cout << "clear" << string(10, '\n');
	int moneyDigits = 0;
	while(pow(10, moneyDigits) < playerMoney)
		moneyDigits++;
	cout << "┌───────────────────────────────────────┐" << endl;
	cout << "│     Casino Game: BlackJack Table      │" << endl;
	cout << "│Your current balance is $" << playerMoney;cout << "." << string( (13 - moneyDigits), ' ') << "│ " << endl;
	cout << "└───────────────────────────────────────┘" << endl;
	cout << string(30 - height, '\n');
}





