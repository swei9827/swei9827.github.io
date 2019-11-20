#include <iostream>
#include "windows.h"
#include <stdlib.h>
#include "conio_yp.h"
#include <ctime>
#include <vector>

using namespace std;

//!global variables
const int mapRow = 27;
const int mapCol = 36;
char map[mapRow][mapCol];
bool isExit = false;


int startPosX = 2;
int startPosY = 2;
int mapOffsetX = 4;
int mapOffsetY = 4;
int step = 200;

#define tree 5
#define wall 219
#define traps 21
#define guard 71
#define dog 68
#define resident 82
#define chimney 127
#define treasure 36
#define portal 63

//! enumeration - > to define new / customize data type

enum TYPE
{
	SANTA = 0,
	CONAN,
	BOLT,
	TOTAL
};
enum TYPE2
{
	GUARD = 0,
	DOG,
	RESIDENT
};

struct Hero
{
	TYPE  heroType;
	char avatar;
	int row;
	int column;
	int rowOld;
	int columnOld;
	int health;
	int attack;
	int speech;
	int agility;
	int strength;
	int karma;
	int gold;
	int deathcount;
	int step;
	void Initialize(TYPE v);
};

struct Item
{
	int axeDurability;
	bool trapDetection ;
	bool treasureHunter ;
	vector<string> inventory;
	void Initialize();
};


void Hero::Initialize(TYPE v)
{
	heroType = v;
	deathcount=0;
	if(heroType == SANTA)
	{
		avatar = 'S';
		row = startPosX;
		column = startPosY;
		health = 150;
		attack = 30;
		strength = 70;
		speech = 60;
		agility = 20;
		karma = 0;
		gold = 60;
		step = 200;
	}
	else if(heroType == CONAN)
	{
		avatar = 'C';
		row = startPosX;
		column = startPosY;
		health = 130;
		attack = 35;
		strength = 50;
		speech = 70;
		agility = 30;
		karma = 0;
		gold = 60;
		step = 230;
	}
	else if(heroType == BOLT)
	{
		avatar = 'B';
		row = startPosX;
		column = startPosY;
		health = 150;
		attack = 25;
		strength = 40;
		speech = 10;
		agility = 100;	
		karma = 0;
		gold = 60;
		step = 270;
	}	
}

void Item::Initialize()
{
	axeDurability = 2;
	trapDetection=false;
	treasureHunter=false;
}

Hero player;
Item item;

struct Enemy
{
	TYPE2 enemyType;
	char avatar;
	int health;
	int attack;
	int speech;
	int agility;
	int strength;
	int enemyRow;
	int enemyColumn;
	void Initialize();
};

void Enemy::Initialize()
{
	enemyRow = 0;
	enemyColumn = 0;
	if(enemyType == GUARD)
	{
		avatar = 'G';
		health = 150;
		attack = 35;
		strength = 100;
		speech = 40;
		agility = 40;
		
	}
	else if(enemyType == DOG)
	{
		avatar = 'D';
		health = 80;
		attack = 25;
		strength = 30;
		speech = 50;
		agility = 70;
	}
	else if(enemyType == RESIDENT)
	{
		avatar = 'G';
		health = 70;
		attack = 30;
		strength = 50;
		speech = 50;
		agility = 50;
	}
}

Enemy theEnemy;

void InitializeMap()
{
	char tempMap[mapRow][mapCol] = {
	{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
	{'#','.','.','.',tree,'.',tree,'.','.',tree,tree,tree,treasure,'.','.',tree,treasure,tree,tree,tree,tree,'.','.','.','.','.',tree,tree,tree,tree,tree,tree,tree,tree,treasure,'#'},
	{'#','.','.','.','.','.','.','.',tree,tree,tree,tree,tree,tree,'.','.','.',tree,tree,treasure,'.',tree,tree,traps,tree,'.',tree,tree,tree,tree,tree,tree,traps,'.','.','#'},
	{'#','.','.','.','.','.','.','.',tree,tree,tree,tree,tree,'.','.',tree,tree,tree,tree,tree,tree,tree,tree,'.','.','.',tree,tree,treasure,'.',tree,tree,'.',tree,tree,'#'},
	{'#','.','.','.',tree,tree,'.',tree,tree,'.','.',tree,'.','.','.',tree,tree,tree,tree,tree,'.',tree,tree,'.',traps,tree,tree,tree,'.',tree,tree,tree,'.',tree,tree,'#'},
	{'#','.','.','.',tree,'.','.','.',tree,tree,'.','.',traps,'.','.','.',tree,tree,tree,'.',tree,tree,tree,'.',dog,tree,tree,'.',portal,tree,tree,tree,'.',tree,tree,'#'},
	{'#','.','.',tree,tree,'.','.','.','.',tree,'.','.','.','.','.','.','.',tree,tree,tree,tree,tree,'.','.',tree,tree,tree,'.','.','.',tree,tree,'.','.',tree,'#'},
	{'#','.','.',tree,'.','.','.','.','.','.','.','.',chimney,'.','.','.','.','.','.',tree,tree,'.','.',tree,tree,tree,'.','.',tree,'.',tree,tree,tree,'.',tree,'#'},
	{'#','.','.','.','.','.','.','.','.','.',wall,wall,wall,tree,'.','.','.','.','.','.','.','.','.',tree,tree,tree,'.','.',tree,'.','.','.',tree,'.',tree,'#'},
	{'#',tree,'.',tree,tree,traps,tree,'.','.','.',wall,wall,wall,tree,'.','.','.',chimney,'.','.','.','.','.',tree,tree,'.',treasure,tree,tree,tree,tree,'.',tree,'.',tree,'#'},
	{'#',tree,'.','.',tree,treasure,tree,tree,'.','.','.','.','.','.','.',wall,wall,wall,tree,'.','.','.','.','.',tree,tree,tree,tree,tree,'.','.','.','.','.',tree,'#'},
	{'#','.','.','.',tree,tree,tree,tree,'.','.','.','.',tree,'.','.',wall,wall,wall,tree,'.','.','.','.','.',tree,tree,tree,'.','.',traps,tree,tree,'.',tree,tree,'#'},
	{'#','.',tree,tree,tree,tree,tree,tree,tree,tree,'.',tree,tree,'.','.','.','.','.','.','.',tree,tree,'.','.',tree,tree,tree,tree,tree,tree,tree,tree,'.',tree,tree,'#'},
	{'#','.',tree,tree,tree,tree,tree,tree,'.','.',tree,'.','.',tree,'.',traps,'.','.','.','.',traps,tree,'.','.','.','.',tree,tree,tree,tree,tree,tree,'.',tree,tree,'#'},
	{'#','.','.','.',treasure,tree,tree,'.','.','.','.','.',chimney,'.','.','.','.','.',chimney,'.','.','.','.','.',tree,tree,tree,tree,tree,tree,tree,tree,'.','.',tree,'#'},
	{'#',traps,'.','.','.','.','.',traps,'.','.',wall,wall,wall,tree,'.','.',wall,wall,wall,tree,'.','.','.','.',tree,tree,tree,tree,tree,tree,tree,tree,tree,dog,tree,'#'},
	{'#','.',traps,'.','.','.','.','.','.','.',wall,wall,wall,tree,'.','.',wall,wall,wall,tree,'.',traps,'.',tree,'.','.','.',tree,tree,tree,tree,tree,tree,'.',tree,'#'},
	{'#','.','.',traps,'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.',tree,'.','.','.',tree,tree,tree,'.','.','#'},
	{'#','.','.',tree,tree,tree,'.','.','.','.','.',tree,'.','.','.','.','.','.',chimney,'.','.','.',tree,tree,'.','.','.','.','.','.','.','.',tree,tree,'.','#'},
	{'#','.',tree,tree,tree,tree,tree,'.','.',tree,tree,tree,'.',traps,'.','.',tree,wall,wall,wall,'.','.',tree,'.','.',traps,'.','.','.','.','.','.',tree,tree,'.','#'},
	{'#',tree,tree,tree,'.','.','.','.',chimney,'.',tree,'.','.','.','.','.',tree,wall,wall,wall,'.','.','.','.','.','.',tree,tree,tree,guard,guard,tree,tree,'.','.','#'},
	{'#',tree,'.','.','.',chimney,wall,wall,wall,'.',tree,'.','.','.','.','.','.','.','.','.','.','.','.',tree,tree,tree,tree,'.','.','.','.','.',tree,'.',tree,'#'},
	{'#',tree,'.',wall,wall,wall,wall,wall,wall,'.',tree,tree,'.',tree,tree,tree,'.','.',tree,'.','.','.','.',tree,'.','.','.','.','.',chimney,'.','.','.','.',tree,'#'},
	{'#',tree,tree,wall,wall,wall,wall,wall,wall,'.',tree,tree,'.',tree,tree,'.','.',tree,'.','.',tree,'.',tree,tree,'.',chimney,'.',wall,wall,wall,'.','.',chimney,'.',tree,'#'},
	{'#',tree,tree,tree,treasure,'.',traps,'.','.','.',tree,tree,treasure,'.',tree,tree,tree,'.',tree,'.','.',tree,tree,tree,'.',wall,wall,wall,wall,wall,wall,wall,wall,'.',tree,'#'},
	{'#',tree,tree,tree,tree,tree,tree,tree,tree,tree,tree,tree,tree,tree,tree,tree,tree,'.',tree,tree,'.','.',tree,tree,treasure,wall,wall,wall,wall,wall,wall,wall,wall,'.',tree,'#'},
	{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
	};
	
	for(int i=0; i<mapRow; i++)
	{
		for(int j=0; j<mapCol; j++)
		{
			map[i][j] = tempMap[i][j];
		}
	}
	int randomSpawn = 5;
	do
	{
		int randRow = rand()%mapRow+1;
		int randCol = rand()%mapCol+1;
		if(map[randRow][randCol] == '.')
		{
			map[randRow][randCol] == dog;
			randomSpawn--;
		}
	}while(randomSpawn > 0);
}

void ShowMap()
{
	for(int i=0; i<mapRow; i++)
	{
		for(int j=0; j<mapCol; j++)
		{
			gotoxy(mapOffsetX+j,mapOffsetY+i);
			
			if(i<player.row - 5 ||
				i>player.row + 5 ||
				j<player.column - 5 ||
				j>player.column + 5)
			{
				cout<" ";
				textcolor(WHITE);
				continue;		
			}

			if(map[i][j] == '#')
			{
				textcolor(YELLOW);
				cout<<map[i][j];
				textcolor(WHITE);
			}
			else if(map[i][j] == tree)
			{
				textcolor(GREEN);
				cout<<map[i][j];
				textcolor(WHITE);
			}
			else if(map[i][j] == traps)
			{
				if(item.trapDetection == false)
				{
					cout<<'.';
				}
				else if(item.trapDetection == true)
				{
					if(i<player.row - 1 || i>player.row + 1 || j<player.column - 1 || j>player.column + 1)
					{
						cout<<'.';
					}
					else
					{
						textcolor(RED);
						cout<<map[i][j];
						textcolor(WHITE);
					}					
				}
			}
			else if(map[i][j] == treasure)
			{
				if(item.treasureHunter == false)
				{
					if(i<player.row - 1 || i>player.row + 1 || j<player.column - 1 || j>player.column + 1)
					{
						cout<<'.';
					}
					else
					{
						textcolor(YELLOW);
						cout<<map[i][j];
						textcolor(WHITE);
					}
				}
				else if(item.treasureHunter == true)
				{
					if(i<player.row - 3 || i>player.row + 3 || j<player.column - 3 || j>player.column + 3)
					{
						cout<<'.';
					}
					else
					{
						textcolor(YELLOW);
						cout<<map[i][j];
						textcolor(WHITE);
					}					
				}
			}
			else if(map[i][j] == wall)
			{
				textcolor(BROWN);
				cout<<map[i][j];
				textcolor(WHITE);
			}
			else if(map[i][j] == portal)
			{
				textcolor(CYAN);
				cout<<map[i][j];
				textcolor(WHITE);
			}
			else if(map[i][j] == chimney)
			{
				textcolor(LIGHTGRAY);
				cout<<map[i][j];
				textcolor(WHITE);
			}
			else if((map[i][j] == (char)dog) || (map[i][j] == (char)guard) || (map[i][j] == (char)resident))
			{
				textcolor(LIGHTBLUE);
				cout<<map[i][j];
				textcolor(WHITE);
			}
			else
			{
				gotoxy(mapOffsetX+j,mapOffsetY+i);
				textcolor(WHITE);
				cout<<map[i][j];
			}
		}
		cout<<endl;
	}
	gotoxy(mapOffsetX+player.column, mapOffsetY+player.row);
	textcolor(LIGHTGREEN);
	cout<<player.avatar;
	textcolor(WHITE);
}


void StartMenu()
{
	cout<<"	                                                          *           "<<endl;
	cout<<"                         *        /)___________/)                      "<<endl;
	cout<<"                                 / ,--o ______/ /       *         *    "<<endl;
	cout<<"                                / /__\\       / |               *       "<<endl;
	cout<<"             *                 /  {''}]     /  |                       "<<endl;
	cout<<"                               .--{~`/--.   )  \\__              *      "<<endl;
	cout<<"                              /   { }    \\ /     /                     "<<endl;
	cout<<"                   *         /_/   ~   /_//'  / /                      "<<endl;
	cout<<"                           .-''='==''= '' |   / /                      "<<endl;
	cout<<"                          /  |-(__)(__)/__| /_/                        "<<endl;
	cout<<"                         /   | \\  |\\  |__ ) /                          "<<endl;
	cout<<"                        /   / //_/ /_/   / /                           "<<endl;
	cout<<"                       /  _/_/________  / /                            "<<endl;
	cout<<"                     /  (            (/ /                             "<<endl;
	cout<<"                    /    \\==========   /                              "<<endl;
	cout<<"                    /      (___________/                               "<<endl;
	cout<<"                   /      _/ /     _/ /                                "<<endl;
	cout<<"           |\\/|   /      \\\\_/     \\\\_/                                 "<<endl; 
	cout<<"           00 | _/________ |\\/|    /                                   "<<endl;
	cout<<"          /_/|_\\/          00 |  _/                                    "<<endl;
	cout<<"           __/ )|         /_/|_\\//                                     "<<endl;
	cout<<"          VV--   \\         __/ )|                                      "<<endl;
	cout<<"             |_   |       VV--   \\                                     "<<endl;
	cout<<"             / / / )          |_   |                                    "<<endl; 
	cout<<"           |_|_/\\_ \\____    / / / )                                    "<<endl;
	cout<<"            ////  '-----`  |_|_/\\_ \\____                               "<<endl;
	cout<<"           ////             ////  '-----`                              "<<endl;
	cout<<"           ^ ^             ////                                        "<<endl;
	cout<<"                           ^ ^                                         "<<endl;
	textcolor(MAGENTA);
	cout<<" _   .-')     ('-.        .-') _              .-') _   _  .-')    ('-. _ .-') _  "<<endl;
	cout<<"( '.( OO )_  ( OO ).-.   ( OO ) )            ( OO ) ) ( \( -O ) _(  OO( (  OO) ) "<<endl;
	cout<<" ,--.   ,--.)/ . --. ,--./ ,--,'   ,-.-'),--./ ,--,'   ,------.(,------\\     .'_ "<<endl;
	cout<<" |   `.'   | | \\-.  \\|   \\ |  |\\   |  |OO|   \\ |  |\\   |   /`. '|  .---,`'--..._)"<<endl;
	cout<<" |         .-'-'  |  |    \\|  | )  |  |  |    \\|  | )  |  /  | ||  |   |  |  \\  '"<<endl;
	cout<<" |  |'.'|  |\\| |_.'  |  .     |/   |  |(_|  .     |/   |  |_.' (|  '--.|  |   ' |"<<endl;
	cout<<" |  |   |  | |  .-.  |  |\\    |   ,|  |_.|  |\\    |    |  .  '.'|  .--'|  |   / :"<<endl;
	cout<<" |  |   |  | |  | |  |  | \\   |  (_|  |  |  | \\   |    |  |\\  \\ |  `---|  '--'  /"<<endl;
	cout<<" `--'   `--' `--' `--`--'  `--'    `--'  `--'  `--'    `--' '--'`------`-------' "<<endl;
	textcolor(CYAN);
	gotoxy(30,70);
	cout<<"Christmas Eve, the night before Christmas "<<endl;
	textcolor(RED);
	gotoxy(30,71);
	cout<<"There is a man wearing in red, sneak on the rooftop"<<endl;
	textcolor(BROWN);
	gotoxy(30,72);
	cout<<"What action will he take, and what is the outcome"<<endl;
	textcolor(WHITE);
}


void PlayerSelection()
{
	int choice = 0;
	textcolor(GREEN);
	cout<<"Please select a character from below: "<<endl;
	cout<<"1. Santa"<<endl;
	cout<<"2. Conan"<<endl;
	cout<<"3. Bolt"<<endl;
	textcolor(WHITE);
	cin>>choice;
	if(choice == 1)
	{
		player.Initialize(SANTA);
	}
	if(choice == 2)
	{
		player.Initialize(CONAN);
	}
	if(choice == 3)
	{
		player.Initialize(BOLT);
	}
	system("CLS");
}

int invenAsk()
{
	for(int i=0; i<item.inventory.size(); i++)
	{
		cout<<"Item "<<i+1<<" : "<<item.inventory[i]<<endl;
	}
	
	int invenOption =0;
	cout<<"Please Select item: ";
	cin>>invenOption;
	
	return invenOption;
}

void ShowPlayerInfo()
{
	textcolor(BLUE);
	gotoxy(42,2);
	cout<<"Player Info"<<endl;
	gotoxy(42,3);
	cout<<"==========="<<endl;
	textcolor(WHITE);
	gotoxy(42,5);
	cout<<"Health: "<<player.health;
	gotoxy(42,6);
	cout<<"Attack: "<<player.attack;
	gotoxy(42,7);
	cout<<"Strength: "<<player.strength;
	gotoxy(42,8);
	cout<<"Speech: "<<player.speech;
	gotoxy(42,9);
	cout<<"Agility: "<<player.agility;
	gotoxy(42,10);
	cout<<"Karma: "<<player.karma;
	textcolor(LIGHTGRAY);
	gotoxy(85,2);
	cout<<"Steps left: "<<player.step;
	textcolor(WHITE);
}

void ShowPlayerItem()
{
	textcolor(BLUE);
	gotoxy(42,12);
	cout<<"Player Item";
	gotoxy(42,13);
	cout<<"===========";
	textcolor(WHITE);
	gotoxy(42,14);
	if(item.axeDurability > 0)
	{
		cout<<"Axe Durability: "<<item.axeDurability;
	}
	else
	{
		textcolor(DARKGRAY);
		cout<<"Axe Durability:"<<item.axeDurability;
		textcolor(WHITE);
	}
	
	gotoxy(42,15);
	if(item.trapDetection == false)
	{
		textcolor(DARKGRAY);
		cout<<"Metal Detector";
		textcolor(WHITE);
	}
	else
	{
		cout<<"Metal Detector";
	}
	
	gotoxy(42,16);
	if(item.treasureHunter == false)
	{
		textcolor(DARKGRAY);
		cout<<"Treasure Map";
		textcolor(WHITE);
	}
	else
	{
		cout<<"Treasure Map";
	}
	
}

void ShowEnemyInfo()
{
	textcolor(RED);
	gotoxy(42,23);
	cout<<"Enemy Info"<<endl;
	gotoxy(42,24);
	cout<<"==========="<<endl;
	textcolor(WHITE);
	gotoxy(42,25);
	cout<<"Enemy Avatar"<<theEnemy.avatar;
	gotoxy(42,26);
	cout<<"Health: "<<theEnemy.health;
	gotoxy(42,27);
	cout<<"Attack: "<<theEnemy.attack;
	gotoxy(42,28);
	cout<<"Strength: "<<theEnemy.strength;
	gotoxy(42,29);
	cout<<"Speech: "<<theEnemy.speech;
	gotoxy(42,30);
	cout<<"Agility: "<<theEnemy.agility;
	
}

void UpdateInput()
{
	//store the old position before input
	player.rowOld = player.row;	
	player.columnOld = player.column;

	if(GetAsyncKeyState(VK_LEFT))
	{
		if(player.column>1)
		{
			player.column--;
			player.step--;
		}
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		if(player.column<mapCol-2)
		{
			player.column++;
			player.step--;
		}
	}
	
	if(GetAsyncKeyState(VK_UP))
	{
		if(player.row>1)
		{
			player.row--;
			player.step--;
		}
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		if(player.row<mapRow-2)
		{
			player.row++;
			player.step--;
		}
	}
	
	if(GetAsyncKeyState(VK_ESCAPE))
	{
		if(!item.inventory.empty())
		{
			int selectedItem=0;
			gotoxy(mapOffsetX, mapOffsetY+mapRow +2);
			selectedItem = invenAsk();
			if(item.inventory[selectedItem-1] == "skill magazine")
			{
				player.strength += 10;
				player.speech += 10;
				player.agility += 10;
				item.inventory.erase(item.inventory.begin()+selectedItem);
				cout<<"You use skill magazine you gain 10 stats for strength, agility and speech"<<endl;
			}
			else if(item.inventory[selectedItem-1] == "teleport potion")
			{
				for(int i=0; i<mapRow; i++)
				{
					for(int j=0; j<mapCol; j++)
					{
						if(map[i][j] == char(portal))
						{
							player.column = j;
							player.row = i;
						}
					}
				}
				item.inventory.erase(item.inventory.begin()+selectedItem);
				cout<<"You used teleport potion, you have been teleport another portal"<<endl;
				system("PAUSE");
				system("CLS");
			}		
		}
		else
		{
			gotoxy(mapOffsetX, mapOffsetY+mapRow +2);
			cout<<"Your inventory is empty";
		}
	}
}

void ClearMenuArea()
{
	for(int i=0; i<10; i++)
	{			//3				4+27+i+1
		gotoxy(mapOffsetX, mapOffsetY+mapRow + i+1);
		cout<<"                                                                                                 ";
	}
}

void BattleSimulation()
{
	bool isBattleEnded = false;
	do
	{	
		system("CLS");
		ShowPlayerInfo();
		ShowEnemyInfo();
		gotoxy(mapOffsetX, mapOffsetY+mapRow +1);
		cout<<"Battle Simulation";
		gotoxy(mapOffsetX, mapOffsetY+mapRow +2);
		cout<<"=================";
		gotoxy(mapOffsetX, mapOffsetY+mapRow +3);
		cout<<"1. Attack";
		gotoxy(mapOffsetX, mapOffsetY+mapRow +4);
		cout<<"2. Counter Attack";
		gotoxy(mapOffsetX, mapOffsetY+mapRow +5);
		cout<<"3. Convince";
		gotoxy(mapOffsetX, mapOffsetY+mapRow +6);
		cout<<"4. Flee";
		gotoxy(mapOffsetX, mapOffsetY+mapRow +7);
		cout<<"Your Choice: ";
		int choice;
		cin>>choice;
		if(choice == 1)
		{
			theEnemy.health -= player.attack;
			gotoxy(mapOffsetX, mapOffsetY+mapRow +10);
			cout<<"You inflict "<<player.attack<<" damage to the enemy";
			if(theEnemy.health <=0)
			{
				map[theEnemy.enemyRow][theEnemy.enemyColumn] = '.';
				isBattleEnded = true;
			}
			else
			{
				player.health -= theEnemy.attack;
				gotoxy(mapOffsetX, mapOffsetY+mapRow +11);
				cout<<"Enemy inflict "<<theEnemy.attack<<" damage to yourself";
				if(player.health <= 0)
				{
					player.deathcount++;
					gotoxy(mapOffsetX, mapOffsetY+mapRow +9);			
					cout<<"You were beaten, the reindeer saved you and send you back here";
					player.row = startPosX;
					player.column = startPosY;
					player.health = 100;
				}
			}
			system("PAUSE");
			system("CLS");
		}
		else if(choice == 2)
		{
			if(rand()%5 == 0)
			{
				player.health -= theEnemy.attack;
				gotoxy(mapOffsetX, mapOffsetY+mapRow +10);
				cout<<"You does'nt counter the attack, enemy inflict "<<theEnemy.attack<<" damage to yourself";
				system("PAUSE");
				if(player.health <= 0)
				{
					player.deathcount++;
					gotoxy(mapOffsetX, mapOffsetY+mapRow +9);			
					cout<<"You were beaten, the village saved you and send you back home";
					player.row = startPosX;
					player.column = startPosY;
					player.health = 100;
				}
			}
			else
			{
				double dmgrec = (((100-(double)player.strength)/100)*(double)theEnemy.attack);
				player.health -= (int)dmgrec;
				theEnemy.health -= player.strength/theEnemy.strength*((player.attack+theEnemy.attack)/2);
				gotoxy(mapOffsetX, mapOffsetY+mapRow +10);
				cout<<"Counter successful, you receive "<<dmgrec<<" damage and inflict "<<(player.strength/theEnemy.strength*((player.attack+theEnemy.attack)/2))<<" damage to the enemy"; ;
				system("PAUSE");
				if(theEnemy.health <=0)
				{
					map[theEnemy.enemyRow][theEnemy.enemyColumn] = '.';
					isBattleEnded = true;
				}			
			}
		}
		else if(choice == 3)
		{
			if(player.speech > theEnemy.speech)
			{
				int probability = rand()%40+1;
				if( probability > (player.speech - theEnemy.speech))
				{
					player.health -= theEnemy.attack;
					cout<<"Convience failed! You received "<<theEnemy.attack<<" damages";
					if(player.health <= 0)
					{
						player.deathcount++;
						gotoxy(mapOffsetX, mapOffsetY+mapRow +9);			
						cout<<"You were beaten, the reindeer saved you and send you back here";
						player.row = startPosX;
						player.column = startPosY;
						player.health = 100;
					}
				}
				else
				{
					if(theEnemy.enemyType == GUARD)
					{
						gotoxy(mapOffsetX,mapOffsetY+mapRow+1);
						cout<<"OH! IS YOU, MAN!............... (the guard leave)";
						map[theEnemy.enemyRow][theEnemy.enemyColumn] = '.';
						isBattleEnded = true;
					}
					else if(theEnemy.enemyType == DOG)
					{
						gotoxy(mapOffsetX,mapOffsetY+mapRow+1);
						cout<<"OOAH.................. (you couldn't understand animal langangue";
						gotoxy(mapOffsetX,mapOffsetY+mapRow+2);
						cout<<"Anyway, the dog doesn't like to attack you";
						map[theEnemy.enemyRow][theEnemy.enemyColumn] = '.';
						isBattleEnded = true;
					}
					else if(theEnemy.enemyType == RESIDENT)
					{
						gotoxy(mapOffsetX,mapOffsetY+mapRow+1);
						cout<<"Hey Darling, did you invite someone cos Santa Claus?";
						gotoxy(mapOffsetX,mapOffsetY+mapRow+2);
						cout<<"Wait! Is David really come? That's just a joke, I don't know he will take it serious";
						gotoxy(mapOffsetX,mapOffsetY+mapRow+3);
						cout<<"She already slept just now. So please lower your voice, I doesn't want to comfort him again";
						gotoxy(mapOffsetX,mapOffsetY+mapRow+4);
						cout<<"(They walk away from you......)";
						map[theEnemy.enemyRow][theEnemy.enemyColumn] = '.';
						isBattleEnded = true;
					}
					system("PAUSE");
					system("CLS");
				}
			}
			else
			{
				player.health -= theEnemy.attack;
				cout<<"Convience failed! You received "<<theEnemy.attack<<" damages";
				if(player.health <= 0)
				{
					player.deathcount++;
					gotoxy(mapOffsetX, mapOffsetY+mapRow +9);			
					cout<<"You were beaten, the village saved you and send you back home";
					player.row = startPosX;
					player.column = startPosY;
					player.health = 100;
				}
			}
			system("PAUSE");
			system("CLS");	
		}
		else if(choice == 4)
		{
			if(player.agility <= theEnemy.agility)
			{
				gotoxy(mapOffsetX,mapOffsetY+mapRow+2);
				cout<<"Fail to flee, you received "<<theEnemy.attack<<" damages";
				player.health -= theEnemy.health;
				if(player.health <= 0)
				{
					player.deathcount++;
					gotoxy(mapOffsetX, mapOffsetY+mapRow +9);			
					cout<<"You were beaten, the village saved you and send you back home";
					player.row = startPosX;
					player.column = startPosY;
					player.health = 100;
				}
			}
			else
			{
				gotoxy(mapOffsetX,mapOffsetY+mapRow+2);
				cout<<"Your enemy trying to chase you, but he failed";
				isBattleEnded = true;
			}
			system("PAUSE");
			system("CLS");
		}
	}while(!isBattleEnded);
	if(player.health <= 0)
	{
		player.deathcount ++;
		gotoxy(mapOffsetX, mapOffsetY+mapRow +9);			
		cout<<"You were beaten, the village saved you and send you back home";
		player.row = startPosX;
		player.column = startPosY;
		player.health = 100;
	}

	map[player.row][player.column] = '.';
	gotoxy(mapOffsetX, mapOffsetY+mapRow +13);
	system("PAUSE");
}

void BattleMenu()
{
	gotoxy(mapOffsetX, mapOffsetY+mapRow+1);
	cout<<"Battle Menu";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
	cout<<"===========";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
	cout<<"1. FIGHT";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
	cout<<"2. RUN";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
	cout<<"Your Choice: ";
	int choice;
	cin>>choice;
	ClearMenuArea();
	if(choice == 1)
	{
		BattleSimulation();
	}
	else if(choice == 2)
	{
		player.row = player.rowOld;
		player.column = player.columnOld;
	}
}

void gameplay()
{
	int random = rand()%7+1;
	int input = 0;
	if(random == 1 )
	{
		gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
		cout<<"The family is sleeping right now, there is a stocking right behind a children bed.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
		cout<<"What should you do?";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
		cout<<"1. Open the safe that hidden under bed, and steal all valueble things";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
		cout<<"2. Put a latest disney barbie doll into the stocking";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+6);
		cout<<"Your choice: ";
		cin>>input;
		ClearMenuArea();
		if(input == 1)
		{
			
			player.karma -= 30;
			player.gold += 70;
			gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
			cout<<"You found some gold bar inside the safe and you take all of them, left nothing for the family.";
		}
		else if(input == 2)
		{
			int random2 = rand()%2+1;
			if(random2 == 1)
			{
				player.karma += 15;
				player.gold -= 30;
				gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
				cout<<"Besides barbie doll, you also give the child chocolat bar";
			}
			else if(random2 == 2)
			{
				player.karma +=10;
				player.gold -=20;
				gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
				cout<<"You gift the child a barbie doll";
			}
		}
	}
	if(random == 2)
	{
		gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
		cout<<"The family is sleeping right now, there is a stocking right behind a children bed.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
		cout<<"What should you do?";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
		cout<<"1. Steal the metal detector";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
		cout<<"2. Put a latest transformer robot into the stocking";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+6);
		cout<<"Your choice: ";
		cin>>input;
		ClearMenuArea();
		if(input == 1)
		{
			
			player.karma -= 20;
			item.trapDetection = true;
			gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
			cout<<"You take the metal detector. (Now you can detect nearly traps)";
		}
		else if(input == 2)
		{
			int random2 = rand()%2+1;
			if(random2 == 1)
			{
				player.karma += 15;
				player.gold -= 30;
				gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
				cout<<"Besides barbie doll, you also give the child chocolat bar";
			}
			else if(random2 == 2)
			{
				player.karma +=10;
				player.gold -=20;
				gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
				cout<<"You gift the child a barbie doll";
			}
		}
	}
	if(random == 3)
	{
		gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
		cout<<"The family is sleeping right now, there is a stocking right behind a children bed.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
		cout<<"What should you do?";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
		cout<<"1. Steal the treasure map";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
		cout<<"2. Put a latest transformer robot into the stocking";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+6);
		cout<<"Your choice: ";
		cin>>input;
		ClearMenuArea();
		if(input == 1)
		{
			
			player.karma -= 30;
			item.treasureHunter = true;
			gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
			cout<<"You take the treasure map. (nearly treasures will be show in your map)";
		}
		else if(input == 2)
		{
			int random2 = rand()%2+1;
			if(random2 == 1)
			{
				player.karma += 15;
				player.gold -= 30;
				gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
				cout<<"Besides barbie doll, you also give the child chocolat bar";
			}
			else if(random2 == 2)
			{
				player.karma +=10;
				player.gold -=20;
				gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
				cout<<"You gift the child a barbie doll";
			}
		}
	}
	else if(random == 4)
	{
		gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
		cout<<"Opps, you wake the watchdog";
		theEnemy.enemyType = DOG;
		theEnemy.Initialize();
		BattleSimulation( );
		gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
		cout<<"The family is sleeping right now, there is a stocking right behind a children bed.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
		cout<<"What should you do?";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
		cout<<"1. Open the safe that hidden under bed, and steal all valueble things";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
		cout<<"2. Put a latest disney barbie doll into the stocking";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+6);
		cout<<"Your choice: ";
		cin>>input;
		ClearMenuArea();
		if(input == 1)
		{
			
			player.karma -= 30;
			player.gold += 70;
			gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
			cout<<"You found some gold bar inside the safe and you take all of them, left nothing for the family.";
		}
		else if(input == 2)
		{
			int random2 = rand()%2+1;
			if(random2 == 1)
			{
				player.karma += 15;
				player.gold -= 30;
				gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
				cout<<"Besides barbie doll, you also give the child chocolat bar";
			}
			else if(random2 == 2)
			{
				player.karma +=10;
				player.gold -=20;
				gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
				cout<<"You gift the child a barbie doll";
			}
		}
	}
	else if(random == 5)
	{
		gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
		cout<<"A Guard spot you!!!";
		theEnemy.enemyType = GUARD;
		theEnemy.Initialize();
		BattleSimulation( );
		gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
		cout<<"The family is sleeping right now, there is a stocking right behind a children bed.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
		cout<<"What should you do?";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
		cout<<"1. Open the safe that hidden under bed, and steal all valueble things";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
		cout<<"2. Put a latest disney barbie doll into the stocking";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+6);
		cout<<"Your choice: ";
		cin>>input;
		ClearMenuArea();
		if(input == 1)
		{
			
			player.karma -= 30;
			player.gold += 70;
			gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
			cout<<"You found some gold bar inside the safe and you take all of them, left nothing for the family.";
		}
		else if(input == 2)
		{
			int random2 = rand()%2+1;
			if(random2 == 1)
			{
				player.karma += 15;
				player.gold -= 30;
				gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
				cout<<"Besides barbie doll, you also give the child chocolat bar";
			}
			else if(random2 == 2)
			{
				player.karma +=10;
				player.gold -=20;
				gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
				cout<<"You gift the child a barbie doll";
			}
		}
	}
	else if(random == 6)
	{
		gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
		cout<<"The Resident hear some suspicious sound and wake up";
		theEnemy.enemyType = RESIDENT;
		theEnemy.Initialize();
		BattleSimulation( );
		gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
		cout<<"The family is sleeping right now, there is a stocking right behind a children bed.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
		cout<<"What should you do?";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
		cout<<"1. Open the safe that hidden under bed, and steal all valueble things";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
		cout<<"2. Put a latest disney barbie doll into the stocking";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+6);
		cout<<"Your choice: ";
		cin>>input;
		ClearMenuArea();
		if(input == 1)
		{
			
			player.karma -= 30;
			player.gold += 70;
			gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
			cout<<"You found some gold bar inside the safe and you take all of them, left nothing for the family.";
		}
		else if(input == 2)
		{
			int random2 = rand()%2+1;
			if(random2 == 1)
			{
				player.karma += 15;
				player.gold -= 30;
				gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
				cout<<"Besides barbie doll, you also give the child chocolat bar";
			}
			else if(random2 == 2)
			{
				player.karma +=10;
				player.gold -=20;
				gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
				cout<<"You gift the child a barbie doll";
			}
		}
	}
	else if(random == 7)
	{
		gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
		cout<<"The Resident hear some suspicious sound and wake up";
		theEnemy.enemyType = RESIDENT;
		theEnemy.Initialize();
		BattleSimulation( );
		gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
		cout<<"A gaint stocking appear infront of you, it have been fill with some gift";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
		cout<<"What should you do?";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
		cout<<"1. Broke the gaint stocking, take all the gift inside then escape";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
		cout<<"2. Randomly put a gift into it";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+6);
		cout<<"Your choice: ";
		cin>>input;
		ClearMenuArea();
		if(input == 1)
		{
			
			player.karma -= 50;
			player.gold += 100;
			gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
			cout<<"Around 10 gifts inside the gaint stocking, but you can only carry half of them to escape";
		}
		else if(input == 2)
		{
			int random2 = rand()%2+1;
			if(random2 == 1)
			{
				player.karma += 30;
				player.gold -= 80;
				gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
				cout<<"The random gift you put is an apple watch";
			}
			else if(random2 == 2)
			{
				player.karma +=50;
				player.gold -=10;
				gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
				cout<<"The random gift you put is a box of tissue";
			}
		}
	}
}

void trap()
{
	gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
	if(player.karma == 0)
	{
		cout<<"You step on a trap, received 20 damaage";
		player.health -= 20;
	}
	else if(player.karma > 0)
	{
		cout<<"You pushed by a mysterious force after trigger the trap, received 12 damage";
		player.health -= 12;
	}
	else if(player.karma < 0)
	{
		cout<<"Unfortunately, the trap hit your weak point, received 30 damage";
		player.health -= 30;
	}
	map[player.row][player.column] = '*';
	system("PAUSE");
	if(player.health <= 0)
	{
		player.deathcount ++;
		gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
		cout<<"Reindeers found you, they save you from traps and send you here.";
		player.row = startPosX;
		player.column = startPosY;
		player.health = 100;
	}
}
 
void SneakIn()
{
	gotoxy(mapOffsetX, mapOffsetY+mapRow+1);
	cout<<"Do you want to sneak into the house?";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
	cout<<"=====================================";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
	cout<<"1. YES";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
	cout<<"2. NO";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
	cout<<"Your Choice: ";
	int choice;
	cin>>choice;
	if(choice == 1)
	{
		map[player.row][player.column] = '.';
		gameplay();
	}
	else if(choice == 2)
	{
		player.row = player.rowOld;
		player.column = player.columnOld;
	}
}

void cutTree() 
{
	gotoxy(mapOffsetX, mapOffsetY+mapRow+1);
	cout<<"Remove the tree? (Axe durability -1)";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
	cout<<"=====================================";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
	cout<<"1. YES";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
	cout<<"2. NO";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
	cout<<"Your Choice: ";
	int choice;
	cin>>choice;
	if(choice == 1)
	{
		map[player.row][player.column] = '.';
		item.axeDurability -= 1;
	}
	else if(choice == 2)
	{
		player.row = player.rowOld;
		player.column = player.columnOld;
	}
	
}
void treasureMenu()
{
	int random;
	if(player.karma == 0) 
	{
		random = rand()%5+1;
		if(random == 1)
		{
			gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
			cout<<"You found some foods and drinks!";
			gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
			cout<<"(After having those food, you gain some health and now you have travel longer)";
			gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
			cout<<"( health + 20    steps + 20 )";
			player.health += 20;
			player.step += 20;
		}
		else if(random >=2 && random<= 3)
		{
			gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
			cout<<"You fall down, look like there is something in the ground";
			int random = rand()%3+1;
			switch (random)
			{
				case 1:
				{
					gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
					cout<<"You found a rusty axe, this axe may only be use for once";
					item.axeDurability += random;
				}
				case 2:
				{
					gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
					cout<<"There is an iron axe down here, the blade is still new but the handle seem will break after few use";
					item.axeDurability += random;
				}
				case 3:
				{
					gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
					cout<<"You found an axe, and it still in great condition";
					item.axeDurability += random;
				}
			}
		}
		else if(random == 4)
		{
			gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
			cout<<"You found a teleport potion!";
			gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
			cout<<"( after used, you will be teleport to the portal )";
			item.inventory.push_back("teleport potion");
		}	
		else if(random == 5)
		{
			gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
			cout<<"You found a magazine!";
			gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
			cout<<"( magazine can enchance your player stat for a limited turn)";
			item.inventory.push_back("skill magazine");
		}
	}
	else if(player.karma < 0)
	{
		random = rand()%5+1;
		if(random == 1)
		{
			gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
			cout<<"You found some foods and drinks!";
			gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
			cout<<"(After having those food, you gain some health and can travel longer)";
			gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
			cout<<"( health + 20    steps + 20 )";
			player.health += 20;
			player.step += 20;
		}
		else if(random == 2)
		{
			gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
			cout<<"You found some drinks!";
			gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
			cout<<"(After having those food, you gain some health and can travel longer)";
			gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
			cout<<"( health + 10    steps + 10 )";
			player.health += 10;
			player.step += 10;
		}
		else if(random >=3 && random<=4)
		{
			gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
			cout<<"You fall down, look like there is something in the ground";
			int random = rand()%3+1;
			switch (random)
			{
				case 1:
				{
					gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
					cout<<"You found a rusty axe, this axe may only be use for once";
					item.axeDurability += random;
				}
				case 2:
				{
					gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
					cout<<"There is an iron axe down here, the blade is still new but the handle seem will break after few use";
					item.axeDurability += random;
				}
				case 3:
				{
					gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
					cout<<"You found an axe, and it still in great condition";
					item.axeDurability += random;
				}
			}
		}	
		else if(random == 5)
		{
			gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
			cout<<"You found a magazine!";
			gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
			cout<<"( magazine can enchance your player stat for a limited turn)";
			item.inventory.push_back("skill magazine");
		}
	}
	else if(player.karma > 0)
	{
		random = rand()%9+1;
		if(random == 1)
		{
			gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
			cout<<"You found some foods and drinks!";
			gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
			cout<<"(After having those food, you gain some health and now you have travel longer)";
			gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
			cout<<"( health + 20    steps + 20 )";
			player.health += 20;
			player.step += 20;
		}
		else if(random == 2)
		{
			gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
			cout<<"You found some goods, foods and drinks!";
			gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
			cout<<"(After having those foods and drinks, you gain some health and now you have travel longer)";
			gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
			cout<<"( health + 30    steps + 30 )";
			player.health += 30;
			player.step += 30;
		}
		else if(random >=3 && random<= 4)
		{
			gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
			cout<<"You fall down, look like there is something on the ground";
			int random = rand()%3+1;
			switch (random)
			{
				case 1:
				{
					gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
					cout<<"You found a rusty axe, this axe may only be use for once";
					item.axeDurability += random;
				}
				case 2:
				{
					gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
					cout<<"There is an iron axe down here, the blade is still new but the handle seem will break after few use";
					item.axeDurability += random;
				}
				case 3:
				{
					gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
					cout<<"You found an axe, and it still in great condition";
					item.axeDurability += random;
				}
			}
		}	
		else if(random == 5)
		{
			gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
			cout<<"You found a magazine!";
			gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
			cout<<"( magazine can enchance your player stat for a limited turn)";
			item.inventory.push_back("skill magazine");
			
		}
		else if(random >=6 && random <= 8 )
		{
			gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
			cout<<"You found some jewelry and gold";
			gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
			cout<<"( gold + 30 )";
			player.gold += 30;
		}
		else if(random == 9)
		{
			gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
			cout<<"You found a treasure case that fill with a lot of jewelry and gold ";
			gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
			cout<<"( gold + 100 )";
			player.gold += 100;
		}
	}
	map[player.row][player.column] = '.';
}

void CollisionDetection()
{
	if(map[player.row][player.column] == (char)tree)
	{
		if(item.axeDurability > 0)
		{
			cutTree();
		}
		else
		{
			player.row = player.rowOld;
			player.column = player.columnOld;
		}
	}
	else if(map[player.row][player.column] == (char)guard)
	{
		theEnemy.enemyType = GUARD;
		theEnemy.Initialize();
		theEnemy.enemyRow = player.row;
		theEnemy.enemyColumn = player.column;
		player.row = player.rowOld;
		player.column = player.columnOld;
		BattleMenu();
	}
	else if(map[player.row][player.column] == (char)dog)
	{
		theEnemy.enemyType = DOG;
		theEnemy.Initialize();
		theEnemy.enemyRow = player.row;
		theEnemy.enemyColumn = player.column;
		player.row = player.rowOld;
		player.column = player.columnOld;
		BattleMenu();
	}
	else if(map[player.row][player.column] == (char)resident)
	{
		theEnemy.enemyType = RESIDENT;
		theEnemy.Initialize();
		theEnemy.enemyRow = player.row;
		theEnemy.enemyColumn = player.column;
		player.row = player.rowOld;
		player.column = player.columnOld;
		BattleMenu();
	}
	else if(map[player.row][player.column] == (char)wall)
	{
		player.row = player.rowOld;
		player.column = player.columnOld;
	}
	else if(map[player.row][player.column] == (char)chimney)
	{
		SneakIn();
	}
	else if(map[player.row][player.column] == (char)treasure)
	{
		treasureMenu();
	}
	else if(map[player.row][player.column] == traps)
	{
		trap();
	}
}

void ShowPlayerAvatar()
{
	if(player.heroType == SANTA)
	{
		gotoxy(62,3);
		cout<<"       (_)";
		gotoxy(62,4);
		cout<<"       / \\";
		gotoxy(62,5);
		cout<<"      /   \\";
		gotoxy(62,6);
		cout<<"     /_____\\";
		gotoxy(62,7);
		cout<<"   (`_______`)";
		gotoxy(62,8);
		cout<<"    // 0 0 \\";
		gotoxy(62,9);
		cout<<"   (/(__7__)\\)";
		gotoxy(62,10);
		cout<<"   |'-' = `-'|";
		gotoxy(62,11);
		cout<<"   |         |";
		gotoxy(62,12);
		cout<<"   /\\       /\\";
		gotoxy(62,13);
		cout<<"  /  '.   .'  \\";
		gotoxy(62,14);
		cout<<" /_/   ` `   \\_\\";
		gotoxy(62,15);
		cout<<"{__}###[_]###{__}";
		gotoxy(62,16);
		cout<<"(_/\\_________/\\_)";
		gotoxy(62,17);
		cout<<"    |___|___|";
		gotoxy(62,18);
		cout<<"     |--|--|";
		gotoxy(62,19);
		cout<<"    (__)`(__)"; 
	}
	else if(player.heroType == CONAN)
	{
		gotoxy(62,3);
		cout<<"       (_)";
		gotoxy(62,4);
		cout<<"       / \\";
		gotoxy(62,5);
		cout<<"      /   \\";
		gotoxy(62,6);
		cout<<"     /_____\\";
		gotoxy(62,7);
		cout<<"   (`_______`)";
		gotoxy(62,8);
		cout<<"    // @ @ \\";
		gotoxy(62,9);
		cout<<"   (/(__7__)\\)";
		gotoxy(62,10);
		cout<<"   |'-|===|-'|";
		gotoxy(62,11);
		cout<<"   |         |";
		gotoxy(62,12);
		cout<<"   /\\       /\\";
		gotoxy(62,13);
		cout<<"  /  '.   .'  \\";
		gotoxy(62,14);
		cout<<" /_/   ` `   \\_\\";
		gotoxy(62,15);
		cout<<"{__}###[_]###{__}";
		gotoxy(62,16);
		cout<<"(_/\\_________/\\_)";
		gotoxy(62,17);
		cout<<"    |___|___|";
		gotoxy(62,18);
		cout<<"     |--|--|";
		gotoxy(62,19);
		cout<<"    (__)`(__)"; 
	}
	else if(player.heroType == BOLT)
	{
		gotoxy(62,3);
		cout<<"       (_)";
		gotoxy(62,4);
		cout<<"       / \\";
		gotoxy(62,5);
		cout<<"      /   \\";
		gotoxy(62,6);
		cout<<"     /_____\\";
		gotoxy(62,7);
		cout<<"   (`_______`)";
		gotoxy(62,8);
		cout<<"    // . . \\";
		gotoxy(62,9);
		cout<<"   (/(__7__)\\)";
		gotoxy(62,10);
		cout<<"   |'-' = `-'|";
		gotoxy(62,11);
		cout<<"   |         |";
		gotoxy(62,12);
		cout<<"   /\\       /\\";
		gotoxy(62,13);
		cout<<"  /  '.   .'  \\";
		gotoxy(62,14);
		cout<<" /_/   ` `   \\_\\";
		gotoxy(62,15);
		cout<<"{__}###[_]###{__}";
		gotoxy(62,16);
		cout<<"(_/\\_________/\\_)";
		gotoxy(62,17);
		cout<<"    |___|___|";
		gotoxy(62,18);
		cout<<"     |--|--|";
		gotoxy(62,19);
		cout<<"    (__)`(__)"; 
	}
}

void bagStatus()
{
	textcolor(YELLOW);
	gotoxy(85,14);
	cout<<"Gold: "<<player.gold;
	textcolor(WHITE);
	if(player.gold <= 60 )
	{
		textcolor(RED);
		gotoxy(80,5);
		cout<<"    _....._";
		gotoxy(80,6);
		cout<<"   ';-.--';'";
		gotoxy(80,7);
		cout<<"     }";
		textcolor(WHITE);
		cout<<"====";
		textcolor(RED);
		cout<<"{ ";
		gotoxy(80,8);
		cout<<"   .'      '.  ";
		gotoxy(80,9);
		cout<<"  /::        \\  ";
		gotoxy(80,10);
		cout<<" |::          | ";
		gotoxy(80,11);
		cout<<"  \\::.        /";
		gotoxy(80,12);
		cout<<"   ':_    -_.'";
		gotoxy(80,13);
		cout<<"     `````  ";
		textcolor(WHITE);
	}
	else if(player.gold >60 && player.gold <= 150)
	{
		textcolor(RED);
		gotoxy(80,5);
		cout<<"    _....._";
		gotoxy(80,6);
		cout<<"   ';-.--';'";
		gotoxy(80,7);
		cout<<"     }";
		textcolor(WHITE);
		cout<<"====";
		textcolor(RED);
		cout<<"{ ";
		gotoxy(80,8);
		cout<<"   .'      '.  ";
		gotoxy(80,9);
		cout<<"  /::        \\  ";
		gotoxy(80,10);
		cout<<" |::          | ";
		gotoxy(80,11);
		cout<<"  \\:##########/";
		gotoxy(80,12);
		cout<<"   ':_####-_.'";
		gotoxy(80,13);
		cout<<"     `````  ";
		textcolor(WHITE);
	}
	else if(player.gold > 150 && player.gold <= 250)
	{
		textcolor(RED);
		gotoxy(80,5);
		cout<<"    _....._";
		gotoxy(80,6);
		cout<<"   ';-.--';'";
		gotoxy(80,7);
		cout<<"     }";
		textcolor(WHITE);
		cout<<"====";
		textcolor(RED);
		cout<<"{ ";
		gotoxy(80,8);
		cout<<"   .'      '.  ";
		gotoxy(80,9);
		cout<<"  /:#########\\  ";
		gotoxy(80,10);
		cout<<" |:###########| ";
		gotoxy(80,11);
		cout<<"  \\:##########/";
		gotoxy(80,12);
		cout<<"   ':_####-_.'";
		gotoxy(80,13);
		cout<<"     `````  ";
		textcolor(WHITE);
	}
	else if(player.gold > 250)
	{
		textcolor(RED);
		gotoxy(80,5);
		cout<<"    _....._";
		gotoxy(80,6);
		cout<<"   ';-.--';'";
		gotoxy(80,7);
		cout<<"     }";
		textcolor(WHITE);
		cout<<"====";
		textcolor(RED);
		cout<<"{ ";
		gotoxy(80,8);
		cout<<"   .'######'.  ";
		gotoxy(80,9);
		cout<<"  /:#########\\  ";
		gotoxy(80,10);
		cout<<" |:###########| ";
		gotoxy(80,11);
		cout<<"  \\:##########/";
		gotoxy(80,12);
		cout<<"   ':_####-_.'";
		gotoxy(80,13);
		cout<<"     `````  ";
		textcolor(WHITE);
	}
}

void endGameCondition()
{
	if(player.gold>350)
	{
		isExit = true;
	}
	if(player.deathcount>=3)
	{
		isExit = true;
	}
	if(player.step <= 0)
	{
		isExit = true;
	}
}

void endScreen()
{
	if(player.deathcount>=3)
	{
		cout<<"_________________________________________________________________"<<endl;
		cout<<"| .----.  .--.  .-..-. .-.  .-.   .-. .-..----..-. . .-. .----. |"<<endl;
		cout<<"| | {}  \\/ {} \\ | || |  \\ \\/ /    |  `| || {_  | |/ \\| |{ {__   |"<<endl;
		cout<<"| |     /  /\\  \\| || `--.}  {     | |\\  || {__ |  .'.  |.-._} } |"<<endl;
		cout<<"| `----'`-'  `-'`-'`----'`--'     `-' `-'`----'`-'   `-'`----'  |"<<endl;
		cout<<"|---------------------------------------------------------------|"<<endl;
		cout<<"|    BREAKING NEWS!!!!                              25/12/2017  |"<<endl;
		cout<<"|      SANTA CLAUS?                ###########################  |"<<endl;
		cout<<"|     BEEN CAUGHT!!!               ###########################  |"<<endl;
		cout<<"|                                  ###########################  |"<<endl;
		cout<<"| #########################        ###########################  |"<<endl;
		cout<<"| #########################        ###########################  |"<<endl;
		cout<<"|  CARRYING "<<player.gold<<" IN         ###########################  |"<<endl;
		cout<<"|       CHRISTMAS EVE              ###########################  |"<<endl;
		cout<<"| #########################        ###########################  |"<<endl;
		cout<<"| #########################        ###########################  |"<<endl;
		cout<<"| #########################        ###########################  |"<<endl;
		cout<<"|_______________________________________________________________|"<<endl;
	}
	if(player.karma<0)
	{
		cout<<"_________________________________________________________________"<<endl;
		cout<<"| .----.  .--.  .-..-. .-.  .-.   .-. .-..----..-. . .-. .----. |"<<endl;
		cout<<"| | {}  \\/ {} \\ | || |  \\ \\/ /    |  `| || {_  | |/ \\| |{ {__   |"<<endl;
		cout<<"| |     /  /\\  \\| || `--.}  {     | |\\  || {__ |  .'.  |.-._} } |"<<endl;
		cout<<"| `----'`-'  `-'`-'`----'`--'     `-' `-'`----'`-'   `-'`----'  |"<<endl;
		cout<<"|---------------------------------------------------------------|"<<endl;
		cout<<"|    BREAKING NEWS!!!!                              25/12/2017  |"<<endl;
		cout<<"|  GLENMARIE GOT STOLEN!           ###########################  |"<<endl;
		cout<<"| Estimate "<<player.gold<<" thousands           ###########################  |"<<endl;
		cout<<"|        Loss!!!!!!!               ###########################  |"<<endl;
		cout<<"| #########################        ###########################  |"<<endl;
		cout<<"| #########################        ###########################  |"<<endl;
		cout<<"| The criminal have been           ###########################  |"<<endl;
		cout<<"| spotted "<<player.deathcount<<" time(s)                ###########################  |"<<endl;
		cout<<"| #########################        ###########################  |"<<endl;
		cout<<"| #########################        ###########################  |"<<endl;
		cout<<"| #########################        ###########################  |"<<endl;
		cout<<"|_______________________________________________________________|"<<endl;
	}
	if(player.karma>=0)
	{
		cout<<"_________________________________________________________________"<<endl;
		cout<<"| .----.  .--.  .-..-. .-.  .-.   .-. .-..----..-. . .-. .----. |"<<endl;
		cout<<"| | {}  \\/ {} \\ | || |  \\ \\/ /    |  `| || {_  | |/ \\| |{ {__   |"<<endl;
		cout<<"| |     /  /\\  \\| || `--.}  {     | |\\  || {__ |  .'.  |.-._} } |"<<endl;
		cout<<"| `----'`-'  `-'`-'`----'`--'     `-' `-'`----'`-'   `-'`----'  |"<<endl;
		cout<<"|---------------------------------------------------------------|"<<endl;
		cout<<"|     BREAKING NEWS!!!!                             25/12/2017  |"<<endl;
		cout<<"|       SANTA CLAUS                ###########################  |"<<endl;
		cout<<"|      REALLY EXIST?                  XXX donate "<<player.gold<<" thousands  |"<<endl;
		cout<<"| #########################                for charity.         |"<<endl;
		cout<<"| #########################        ###########################  |"<<endl;
		cout<<"|  RED SUIT MYSTERIOUS MAN         ###########################  |"<<endl;
		cout<<"|   FLYING REINDEER BEEN           ###########################  |"<<endl;
		cout<<"| SPOTTED "<<player.deathcount<<" time(s)                ###########################  |"<<endl;
		cout<<"| #########################        ###########################  |"<<endl;
		cout<<"| #########################        ###########################  |"<<endl;
		cout<<"| #########################        ###########################  |"<<endl;
		cout<<"|_______________________________________________________________|"<<endl;
	}
	
}	

int main(int argc, char** argv) {
	system("mode con: cols=110 lines=50");
	textcolor(WHITE);
	srand(time(NULL));
	StartMenu();
	InitializeMap();
	PlayerSelection();
	item.Initialize();
	do
	{
		system("CLS");
		UpdateInput();
		CollisionDetection();
		ShowMap();
		ShowPlayerInfo();
		ShowPlayerItem();
		ShowPlayerAvatar();
		bagStatus();
		gotoxy(mapOffsetX, mapOffsetY + mapRow + 13);
		endGameCondition();
		system("PAUSE");
	}while(!isExit);
	system("CLS");
	endScreen();
	system("PAUSE");
	return 0;
}
