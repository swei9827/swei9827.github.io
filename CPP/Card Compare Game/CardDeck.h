#include <iostream>
#include <string>
#include <vector> //!similar like an array container, but no size limit
#include "windows.h"

using namespace std;

struct Card
{
	string face;
	string suit;
	int value;
};

struct CardDeck
{
	static const int NUMBEROFCARDS = 52;
	static const int FACES = 13;
	static const int SUIT = 4;
	static const int VALUE = 13;
	//! an array container - Card
	Card deck[NUMBEROFCARDS];
	Card player1Deck[5];
	Card player2Deck[5];
	// function header
	void Initialize();
	void shuffle();
	void deal();
	void PickACard();
	void compare();
	
};
