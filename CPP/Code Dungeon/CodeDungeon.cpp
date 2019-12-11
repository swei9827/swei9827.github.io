#include <iostream>
#include "windows.h"
#include <vector>
#include <ctime>
#include <string>

using namespace std;

struct Hero
{
	string classString;
	int firewall;
	int viruses;
	int code;
	int system;
	int intelligence;
	int cash;
	int level;
	int XP;

	void Initialize();
};

void Hero::Initialize()
{
	firewall=0;
	viruses=0;
	code=0;
	system=0;
	intelligence=0;
	cash=0;
	level=0;
	XP=0;
}

static bool alive = true;
int room = 1;
vector<string> inventory; //declare the vecotor containner -> no size limit
Hero hero;
void purchase()
{

}

int mainOpt()
{
	int option = 0;
	do{
		cout<<"You arrive in room" + room <<" : "<<endl;
		cout<<"<1> Look around"<<endl;
		cout<<"<2> Talk to the Shady Dealer in the corner"<<endl;
		cout<<"<3> Inventory"<<endl;
		cout<<"<4> Stats"<<endl;
		cout<<"<5> Next room"<<endl;
		cout<<"<6> Use Item"<<endl;
		cout<<"Your option : ";
		cin>>option;
	}while(option<=0 || option>6);

	return option;
}

void classChoose()
{
	int select = 0;
	do
	{
		cout<<"Pick a Hero Class"<<endl;
		cout<<"<1> Hacker: Good with viruses and  pretty fine with code but has a weakness for firewalls. also low intelligence"<<endl;
		cout<<"<2> CEO: Very intelligence and lots of system space but not the best with the code"<<endl;
		cout<<"<1> Coder: Great woth code, kind bas system space, decent viruses and firewalls"<<endl;
		cout<<"Your choice: ";
		cin>>select;
	}while(select<=0 || select>6);

	switch(select)
	{
		case 1:
			hero.Initialize();
			hero.classString="Hacker";
			hero.firewall=1;
			hero.viruses = rand()%4+1;
			hero.code = rand()%3+1;
			hero.system = rand()%20+20;
			hero.intelligence = rand()%2+1;
		break;
		case 2:
			hero.Initialize();
			hero.classString="CEO";
			hero.firewall = rand()%2+1;
			hero.viruses = rand()%3+1;
			hero.code = rand()%2+1;
			hero.system = rand()%20+30;
			hero.intelligence = rand()%2+4;
		break;
		case 3:
			hero.Initialize();
			hero.classString="Coder";
			hero.firewall= rand()%3+1;
			hero.viruses = rand()%3+1;
			hero.code = rand()%4+1;
			hero.system = rand()%20+20;
			hero.intelligence = rand()%2+2;
		break;
		default:
			cout<<"Wrong hero selection!";
	}
}

void merchant()
{
	int itemSelect = 0;
	do
	{
		cout<<"Shady Merchant: But something?!?!"<<endl;
		cout<<"<1> USB - 10 Bitcoins"<<endl;
		cout<<"<2> Tech Support - 20 Bitcoins"<<endl;
		cout<<"<3> Trojan Virus - 30 Bitcoins"<<endl;
		cout<<"<4> Anti-virus - 15 Bitcoins"<<endl;
		cout<<"<5> Nothing thanks!"<<endl;
		cout<<"Your Bitcoins: "<<hero.cash<<endl;
		cout<<"Your choice: ";
		cin>>itemSelect;
	}while(itemSelect<=0 || itemSelect>5);

	switch(itemSelect)
	{
		case 1:
			if(hero.cash >= 10)
			{
				inventory.push_back("USB");
				hero.cash -= 10;
			}
			else
			{
				cout<<"You do not have enough bitcoins for that."<<endl;
			}
		break;
		case 2:
			if(hero.cash >= 20)
			{
				inventory.push_back("Tech Support");
				hero.cash -= 20;
			}
			else
			{
				cout<<"You do not have enough bitcoins for that."<<endl;
			}
		break;
		case 3:
			if(hero.cash >= 30)
			{
				inventory.push_back("Trojan Virus");
				hero.cash -= 30;
			}
			else
			{
				cout<<"You do not have enough bitcoins for that."<<endl;
			}
		break;
		case 4:
			if(hero.cash >= 15)
			{
				inventory.push_back("Anti-virus");
				hero.cash -= 15;
			}
			else
			{
				cout<<"You do not have enough bitcoins for that."<<endl;
			}
		break;
	}
}

void statRead()
{
	cout<<"---------Hero Stats---------"<<endl;
	cout<<"Firewall: "<<hero.firewall<<endl;
	cout<<"Viruses: "<<hero.viruses<<endl;
	cout<<"Code: "<<hero.code<<endl;
	cout<<"Intelligence: "<<hero.intelligence<<endl;
	cout<<"System: "<<hero.system<<endl;
	cout<<"Level: "<<hero.level<<endl;
	cout<<"XP: "<<hero.XP<<endl;
}

int invenAsk()
{
	for(int i=0; i<inventory.size(); i++)
	{
		cout<<"Item "<<i+1<<" : "<<inventory[i]<<endl;
	}

	int invenOption = 0;
	cout<<"Please Select Item: ";
	cin>>invenOption;

	return invenOption;
}

bool doBattle(Hero h)
{
	//! enemy
	int enemyHP = hero.system + (rand()%5+1);
	int enemyAttack = hero.firewall + (rand()%4+1);
	int enemyDefense = hero.intelligence + (rand()%3+1);
	int selectedItem=0;
	int myDefense = hero.firewall;

	int virusesMade = 0;
	int virusAttack = 0;

	while(hero.system > 0 && enemyHP >0)
	{
		int action = 0;
		do
		{
			cout<<"Action: "<<endl;
			cout<<"<1> Send out Virus!!!"<<endl;
			cout<<"<2> Build virus"<<endl;
			cout<<"<3> Work on system defense"<<endl;
			cout<<"<4> Repair System"<<endl;
			cout<<"<5> Use Item"<<endl;
			cout<<"<6> See Full Stats"<<endl;
			cout<<"Your Action: ";
			cin>>action;
		}while(action<=0 || action>6);

		switch(action)
		{
			case 1:
				if(virusesMade > 0)
				{
					if(virusAttack - enemyDefense > 0)
					{
						enemyHP -= virusAttack;
						virusesMade--;
					}
					else
					{
						cout<<"You virus too weak!!!"<<endl;
					}
				}
			break;
			case 2:
				virusesMade++;
				if(virusAttack>0)
				{
					virusAttack = hero.viruses + hero.code/2;
					virusAttack++;
				}
				else
				{
					virusAttack = hero.viruses + hero.code/2;
				}
			break;
			case 3:
				myDefense = myDefense+ (hero.code+hero.firewall)/2;
			break;
			case 4:
				hero.system = hero.system + hero.intelligence/2 + hero.code;
			break;
			case 5:
				selectedItem = invenAsk();
				if(inventory[selectedItem-1] == "USB")
				{
					hero.system += 15;
					inventory.erase(inventory.begin()+selectedItem);
					cout<<"You use USB and repaired your system by 15"<<endl;
				}
				else if(inventory[selectedItem-1] == "Tech Support")
				{
					cout<<"You get to leave battle!!!"<<endl;
					inventory.erase(inventory.begin()+selectedItem);
					return true;
				}
				else if(inventory[selectedItem-1] == "Trojan Virus")
				{
					virusAttack += 3;
					virusesMade += 2;
					inventory.erase(inventory.begin()+selectedItem);
				}
				else if(inventory[selectedItem-1] == "Anti-Virus")
				{
					myDefense +=5;
					inventory.erase(inventory.begin()+selectedItem);
				}
			break;
			case 6:
				statRead();
			break;
			default:
				cout<<"Wrong selection";
		}

		if(action !=6 || action !=7)
		{
			if(enemyAttack > myDefense)
			{
				hero.system = hero.system -(enemyAttack - myDefense);
			}
			else
			{
				hero.system = hero.system - enemyAttack;
			}
		}
	}
}

void invenRead()
{

}
int main()
{
	srand(time(NULL));
	classChoose();
	statRead();
	//! story telling
	cout<<"You are travelling on a long journey away from home in the land of C++"<<endl;
	cout<<"Villager: Greeting young "<<hero.classString<<endl;
	cout<<"My hometown - Macintosh has been terroized by Code Dungeon";
	cout<<"Viruses leak out and murder most of the villagers. It would be great a "<<hero.classString;
	cout<<" like you could help us!!!"<<endl;
	int opt = 0;
	cout<<"1. Accept"<<endl;
	cout<<"2. Get lost"<<endl;
	cin>>opt;
	if(opt ==1)
	{
		cout<<"Villager: Thank you so much (stupid......)"<<endl;
		cout<<"Come to my village we will equip you for your journey!(make sure you got enough bitcoins)"<<endl;

		purchase();

		cout<<"Villager: Please accept 20 bitcoins..."<<endl;
		hero.cash += 20;
		bool explored = false;
		room = 1;
		int mainOption =0;
		int itemUsed = 0;
		int randValue =0;

		do
		{
			if(hero.XP == hero.level*100)//!level up
			{
				cout<<"You are almost ready to level up ... BOSS FIGHT!"<<endl;
				if(doBattle(hero))
				{
					cout<<"You defeated the boss and leveled up!!!"<<endl;
				}
			}
			else
			{
				mainOption= mainOpt();
				switch(mainOption)
				{
					case 1:
						if(!explored)
						{
							explored = true;
							randValue = rand()%100;
							int open =0;
							cout<<"You explore the room"<<endl;
							if(randValue == 0)
							{
								//! got a mysterious looking computer possibly filled with bitcoins
								cout<<"You find a mysterious looking compuiter possibly filled with bitcoins. Open?";
								cout<<"1. Open $$$$$$$$"<<endl;
								cout<<"2. Ignore, i got enough bitcoins!!!"<<endl;
								cin>>open;
								int randNum = 0;
								if(open == 1)
								{
									randNum = rand()%100+1;
									if(randNum>=50)
									{
										cout<<"You finds load of 1000 Bitcoins!!!"<<endl;
									}
									else
									{
										cout<<"The chest was filled with malware thjat infiects your system"<<endl;
										hero.system = 0;
									}
								}
							}
							else if(randValue <=50)
							{
								//! fight !doBattle()
							}
							else if(randValue == 99)
							{
								//! get a mysterious looking bowl of guacamole
							}
							else if(randValue >= 85)
							{
								//! battle with mini boss
							}
						}
						else
						{
							cout<<"You already saw what was in this room"<<endl;
						}
					break;
					case 2:
						merchant();
					break;
					case 3:
						invenRead();
					break;
					case 4:
						statRead();
					break;
					case 5:

					break;
					case 6:

					break;
				}

			}
		}while(hero.system>0);
	}
	else
	{
		cout<<"Villager: Oh... That's okay..."<<endl;
		cout<<"The whole village of the macintosh will be slaugher later"<<endl;
	}

	system ("PAUSE");
	return 0;
}
