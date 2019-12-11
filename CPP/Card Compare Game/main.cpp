#include <iostream>
#include <ctime>
#include "windows.h"
#include "CardDeck.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;
int player1point = 0 , player2point = 0;
void CardDeck::Initialize()
{
	static string suit[SUIT] = {"Hearts","Diamonds","Clubs","Spades"};
	static string face[FACES] = {"Ace","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King"};
	static int value[VALUE] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
	for(int i=0; i<NUMBEROFCARDS; i++)
	{
		deck[i].face = face[i%FACES];
		deck[i].suit = suit[i/FACES];
		deck[i].value = value[i%VALUE];
	}
	srand(time(NULL));
}

void CardDeck::shuffle()
{
	for(int i=0; i<NUMBEROFCARDS; i++)
	{
		int rd=i+rand()%52-i;
		Card temp = deck[i];
		deck[i]= deck[rd];
		deck[rd] = temp;
	}
}
void CardDeck::deal()
{
	for(int i = 0; i<NUMBEROFCARDS; i++)
	{
		cout<<i+1<<". "<<deck[i].face<<" of "<<deck[i].suit<<" value :"<<deck[i].value<<endl;
	}
}

void CardDeck::PickACard()
{
	cout<<"============================"<<endl;
	for(int i=0; i<5; i++)
	{
		player1Deck[i] = deck[i];
		player2Deck[i] = deck[i+5];
	}
}

void CardDeck::compare()
{
	cout<<"============================================================"<<endl;
	for(int i=0; i<5; i++)
	{
		cout<<player1Deck[i].face<<" of "<<player1Deck[i].suit<<" value :"<<player1Deck[i].value<<"  VS  "<<player2Deck[i].face<<" of "<<player2Deck[i].suit<<" value :"<<player2Deck[i].value<<endl;
	}
	cout<<"============================================================"<<endl;
	for(int i=0; i<5; i++)
	{
		if(player1Deck[i].value > player2Deck[i].value)
		{
			player1point += 1;
		}
		else if(player1Deck[i].value < player2Deck[i].value)
		{
			player2point += 1;
		}
		else
		{
			
		}
	}
	cout<<"Player 1 Point: "<<player1point<<"	Player 2 Point: "<<player2point<<endl;
	if(player1point > player2point)
	{
		cout<<"Player 1 won"<<endl;;
	}
	else if(player2point>player1point)
	{
		cout<<"Player 2 won"<<endl;
	}
	else
	{
		cout<<"Tie"<<endl;
	}
}

int main(int argc, char** argv) {
	
	CardDeck box;
	box.Initialize();
	box.shuffle();
	box.deal();
	box.PickACard();	
	box.compare();
	
	
	system("PAUSE");
	return 0;
}
