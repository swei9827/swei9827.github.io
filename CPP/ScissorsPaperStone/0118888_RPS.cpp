#include <iostream>
#include "windows.h"
#include <ctime>
#include <string.h>

using namespace std;

bool isGameEnd = false;
int p1Input = 0, p2Input = 0;

struct Player
{
	int winCount = 0;
	string item;
};

Player p1;
Player p2;

void playerInput()
{
	do
	{
		cout<<"Player 1 please choice your item: "<<endl;
		cout<<"1. Scissors"<<endl;
		cout<<"2. Rock"<<endl;
		cout<<"3. Paper"<<endl;
		cin>>p1Input;
	}while(p1Input<1 || p1Input>3);
	
	if(p1Input == 1)
	{
		p1.item = "Scissors";
	}
	else if(p1Input == 2)
	{
		p1.item = "Rock";
	}
	else if(p1Input == 3)
	{
		p1.item = "Paper";
	}
	
	system("CLS");
	
	do
	{
		cout<<"Player 2 please choice your item: "<<endl;
		cout<<"1. Scissors"<<endl;
		cout<<"2. Rock"<<endl;
		cout<<"3. Paper"<<endl;
		cin>>p2Input;
	}while(p2Input<1 || p2Input>3);
	
	if(p2Input == 1)
	{
		p2.item = "Scissors";
	}
	else if(p2Input == 2)
	{
		p2.item = "Rock";
	}
	else if(p2Input == 3)
	{
		p2.item = "Paper";
	}
	system("CLS");
	
}

void playerBattle()
{
	if(p1.item == "Scissors" && p2.item == "Rock")
	{
		cout<<"Player 2 win this round"<<endl;
		p2.winCount++;
	}
	else if(p1.item == "Scissors" && p2.item == "Paper")
	{
		cout<<"Player 1 win this round"<<endl;
		p1.winCount++;
	}
	else if(p1.item == "Rock" && p2.item == "Paper")
	{
		cout<<"Player 2 win this round"<<endl;
		p2.winCount++;
	}
	else if(p1.item == "Rock" && p2.item == "Scissors")
	{
		cout<<"Player 1 win this round"<<endl;
		p1.winCount++;
	}
	else if(p1.item == "Paper" && p2.item == "Scissors")
	{
		cout<<"Player 2 win this round"<<endl;
		p2.winCount++;
	}
	else if(p1.item == "Paper" && p2.item == "Rock")
	{
		cout<<"Player 1 win this round"<<endl;
		p1.winCount++;
	}
	else if(p1.item == p2.item)
	{
		cout<<"Tie"<<endl;
	}
}

int main()
{	
	do
	{
		playerInput();
		cout<<"Player 1: "<<p1.item<<"   Player 2: "<<p2.item<<endl;
		playerBattle();	
		cout<<"continue?"<<endl;
		cout<<"1. Continue"<<endl;
		cout<<"2. Exit"<<endl;
		int input;
		cin>>input;
		if(input == 1)
		{
			system("CLS");
		}
		else if(input == 2)
		{
			isGameEnd = true;
		}
	}while(!isGameEnd);
	cout<<"Player 1 Win Count: "<<p1.winCount<<"     "<<"Player 2 Win Count: "<<p2.winCount<<endl;
	system("PAUSE");
	return 0;
}
