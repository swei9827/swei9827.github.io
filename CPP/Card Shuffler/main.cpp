#include <iostream>
#include <ctime>
#include "windows.h"
#include "CardDeck.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

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
	for(int i= 0; i<NUMBEROFCARDS; i++)
	{
		cout<<deck[i].face<<" of "<<deck[i].suit<<" value :"<<deck[i].value<<endl;
	}
}

void CardDeck::PickACard()
{
	PlayerDeck p1;
	PlayerDeck p2;
	for(int i=0; i<5; i++)
	{
		p1.playerdeck[i] = deck[i];
		p2.playerdeck[i] = deck[i+5];
	}
}

void PlayerDeck::compare()
{
	cout<<"============================"<<endl;
	for(int i=0; i<5; i++)
	{
		cout<<p1.playerdeck[i].face<<" of "<<p1.playerdeck[i].suit<<" value :"<<p1.playerdeck[i].value<<endl;
	}
	cout<<"============================"<<endl;
	for(int i=0; i<5; i++)
	{
		cout<<p2.playerdeck[i].face<<" of "<<p2.playerdeck[i].suit<<" value :"<<p2.playerdeck[i].value<<endl;
	}
}


int main(int argc, char** argv) {
	
	CardDeck box;
	box.Initialize();
	box.shuffle();
	box.deal();
	box.PickACard();
	box.compare()
	
	system("PAUSE");
	
	return 0;
}
