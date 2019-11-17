#include <iostream>
#include <ctime>
#include <string>
#include "conio_yp.h"
#include "windows.h"
#include <vector>

using namespace std;

#define tree 5
#define wall 219
#define traps 21
#define undead 85
#define monster 77
#define grave 241
#define treasure 36
#define portal 63
const int mapRow = 27;
const int mapCol = 36;
char map[mapRow][mapCol];
int startPosX = 2;
int startPosY = 2;
int mapOffsetX = 4;
int mapOffsetY = 4;
bool isVictory = false;

enum GameState
{
    MAIN_MENU = 0,
    CHARACTER_SELECTION,
    MAP,
    BATTLE,
    RESULT
};
//! global variable
GameState gameState = MAIN_MENU;
int choice = -1;

enum PlayerType
{
    TREASURE_HUNTER= 0,
	TOMB_RAIDER,
	MONKEY,
    TOTAL_PLAYER_TYPE
};

enum CharAction
{
    ATTACK = 0,
    ITEM,
    DODGE,
    STUN,
    HEAL,
    TOTAL_CHAR_ACTION
};

enum EnemyType
{
    WILDLIFE = 0,
    UNDEAD,
    MONSTER,
    TOTAL_ENEMY_TYPE
};

//! SUPER CLASS / PARENT CLASS
class Character
{
public:
    string name;
    int health;
    int offense;
    int defense;
    bool isStunned;
    bool isDodged;
    int row;
    int column;
    int rowOld;
    int columnOld;
    char avatar;
    int step;
    vector <CharAction> actionList;
    virtual void InitializeStats() = 0;

    string GetCharActionName(CharAction charAction)
    {
        if(charAction == ATTACK)
        {
            return "Attack";
        }
        else if(charAction == DODGE)
        {
            return "Dodge";
        }
        else if(charAction == STUN)
        {
            return "Stun";
        }
        else if(charAction == HEAL)
        {
            return "Heal";
        }
        else if(charAction == ITEM)
        {
            return "Item";
        }
    }
};

class Player : public Character //! Hero class --> virtual class
{
public:
    PlayerType type;

    Player(string name)
    {
        this->name = name;
    }

    virtual void InitializeStats()= 0;

    string GetPlayerTypeName()
    {
        if(type == TREASURE_HUNTER)
        {
            return "Treasure Hunter";
        }
        else if(type == TOMB_RAIDER)
        {
            return "Tomb Raider";
        }
        else if(type == MONKEY)
        {
            return "Monkey";
        }
    }
    void DisplayStats(int x, int y)
    {
        gotoxy(x,y);
        cout<<"Name : "<<name;
        gotoxy(x,y+1);
        cout<<"Class : "<<GetPlayerTypeName();
        gotoxy(x,y+2);
        cout<<"Health : "<<health;
        gotoxy(x,y+3);
        cout<<"Offense : "<<offense;
        gotoxy(x,y+4);
        cout<<"Defense : "<<defense;
    }
};

class tHunter : public Player
{
public:
    tHunter(string name) : Player (name)
    {
        type = TREASURE_HUNTER;
        InitializeStats();
    }
    void InitializeStats()
    {
        health = rand()%20 + 80;
        offense = rand()%20 + 30;
        defense = rand()%20 + 50;
        row = 2;
        column = 2;
        avatar = 'H';
        isStunned = false;
        isDodged = false;
        step = 500;

        actionList.push_back(ATTACK);
        actionList.push_back(STUN);
        actionList.push_back(HEAL);
        actionList.push_back(ITEM);
    }
};

class tRaider : public Player
{
public:
    tRaider(string name) : Player (name)
    {
        type = TOMB_RAIDER;
        InitializeStats();
    }
    void InitializeStats()
    {
        health = rand()%20 + 30;
        offense = rand()%20 + 50;
        defense = rand()%20 + 80;
        row = 2;
        column = 2;
        avatar = 'R';
        isStunned = false;
        isDodged = false;

        actionList.push_back(ATTACK);
        actionList.push_back(HEAL);
        actionList.push_back(DODGE);
        actionList.push_back(ITEM);
    }
};

class Monkey : public Player
{
public:
    Monkey(string name) : Player (name)
    {
        type = MONKEY;
        InitializeStats();
    }
    void InitializeStats()
    {
        health = rand()%20 + 50;
        offense = rand()%20 + 80;
        defense = rand()%20 + 30;
        row = 2;
        column = 2;
        avatar = 'M';
        isStunned = false;
        isDodged = false;

        actionList.push_back(ATTACK);
        actionList.push_back(STUN);
        actionList.push_back(DODGE);
        actionList.push_back(HEAL);
    }
};

class Enemy : public Character
{
public:
    EnemyType type;

    Enemy(string name)
    {
        this->name = name;
    }

    virtual void InitializeStats()= 0;

    string GetEnemyTypeName()
    {
        if(type == WILDLIFE)
        {
            return "Wildlife";
        }
        else if(type == UNDEAD)
        {
            return "Undead";
        }
        else if(type == MONSTER)
        {
            return "Monster";
        }
    }
    void DisplayStats(int x, int y)
    {
        gotoxy(x,y);
        cout<<"Name : "<<name;
        gotoxy(x,y+1);
        cout<<"Class : "<<GetEnemyTypeName();
        gotoxy(x,y+2);
        cout<<"Health : "<<health;
        gotoxy(x,y+3);
        cout<<"Offense : "<<offense;
        gotoxy(x,y+4);
        cout<<"Defense : "<<defense;
    }
};

class Wildlife: public Enemy
{
public:
    Wildlife(string name) : Enemy (name)
    {
        type = WILDLIFE;
        InitializeStats();
    }
    void InitializeStats()
    {
        health = rand()%10 + 15;
        offense = rand()%20 + 10;
        defense = rand()%20 + 20;

        actionList.push_back(ATTACK);
    }
};

class Undead : public Enemy
{
public:
    Undead(string name) : Enemy (name)
    {
        type = UNDEAD;
        InitializeStats();
    }
    void InitializeStats()
    {
        health = rand()%20 + 40;
        offense = rand()%30 + 30;
        defense = rand()%20 + 10;

        actionList.push_back(ATTACK);
        actionList.push_back(DODGE);
        actionList.push_back(STUN);
    }
};

class Monster : public Enemy
{
public:
    Monster(string name) : Enemy (name)
    {
        type = MONSTER;
        InitializeStats();
    }
    void InitializeStats()
    {
        health = rand()%20 + 120;
        offense = rand()%10 + 40;
        defense = rand()%20 + 50;

        actionList.push_back(ATTACK);
        actionList.push_back(HEAL);
        actionList.push_back(DODGE);
        actionList.push_back(STUN);
    }
};

class Item
{
public:
    int axeDurability;
	bool trapDetection ;
	bool treasureHunter ;
	vector<string> inventory;

	Item()
	{
	    axeDurability = 2;
	    trapDetection = false;
	    treasureHunter = false;
	}
};
Player* player;
Enemy* enemy;
Item* item;

void DisplayMainMenu()
{
    textcolor(LIGHTRED);
    gotoxy(15,15);
    cout<<"   ___  _____   __   ____  ____   ___ ";
    gotoxy(15,16);
    cout<<"  /  _]/ ___/  /  ] /    ||    \\ /  _]";
    gotoxy(15,17);;
    cout<<" /  [_(   \\_  /  / |  o  ||  o  )  [_ ";
    gotoxy(15,18);
    cout<<"|    _]\\__  |/  /  |     ||   _/    _]";
    gotoxy(15,19);
    cout<<"|   [_ /  \\ /   \\_ |  _  ||  | |   [_ ";
    gotoxy(15,20);
    cout<<"|     |\\    \\     ||  |  ||  | |     |";
    gotoxy(15,21);
    cout<<"|_____| \\___|\\____||__|__||__| |_____|";
    textcolor(WHITE);

    gotoxy(17,30);
    system("PAUSE");
    gameState = CHARACTER_SELECTION;
    choice = 0;
}

void DisplayCharacterSelection()
{
    string name;
    gotoxy(15,17);
    textcolor(YELLOW);
    cout<<"Enter your character name : ";
    getline(cin,name);
    gotoxy(15,22);
    textcolor(GREEN);
    cout<<"Please select your character class";
    gotoxy(15,24);
    textcolor(LIGHTBLUE);
    cout<<"1.Treasure Hunter";
    gotoxy(15,25);
    textcolor(LIGHTRED);
    cout<<"2.Tomb Raider";
    gotoxy(15,26);
    textcolor(LIGHTCYAN);
    cout<<"3.Monkey";
    gotoxy(15,28);
    textcolor(YELLOW);
    cout<<"Your Input : ";
    cin>>choice;

    if(cin.good())
    {
        item = new Item();
        if(choice == 1)
        {
            player = new tHunter(name);
            item->treasureHunter = true;
            item->inventory.push_back("health potion");
        }
        else if(choice == 2)
        {
            player = new tRaider(name);
            item->trapDetection = true;
            item->inventory.push_back("health potion");
        }
        else if(choice == 3)
        {
            player = new Monkey(name);
            item->inventory.push_back("health potion");
            item->inventory.push_back("health potion");
            item->inventory.push_back("health potion");
        }
        gameState = MAP;
    }
    else
    {
        cout<<"Wrong Input!!!"<<endl;
        system("PAUSE");
    }
    cin.clear();
    cin.ignore(1000,'\n');
}
void InitializeMap()
{
	char tempMap[mapRow][mapCol] = {
	{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
	{'#','.','.','.',tree,'.',tree,'.','.',tree,tree,tree,treasure,monster,'.',tree,treasure,tree,tree,tree,tree,'.','.','.','.','.',tree,tree,tree,tree,tree,tree,tree,tree,treasure,'#'},
	{'#','.','.','.','.','.','.','.',tree,tree,tree,tree,tree,tree,'.','.','.',tree,tree,treasure,'.',tree,tree,traps,tree,'.',tree,tree,tree,tree,tree,tree,traps,'.','.','#'},
	{'#','.','.','.','.','.','.','.',tree,tree,tree,tree,tree,'.','.',tree,tree,tree,tree,tree,tree,tree,tree,'.','.','.',tree,tree,treasure,'.',tree,tree,'.',tree,tree,'#'},
	{'#','.','.','.',tree,tree,'.',tree,tree,'.','.',tree,'.','.','.',tree,tree,tree,tree,tree,'.',tree,tree,undead,traps,tree,tree,tree,'.',tree,tree,tree,'.',tree,tree,'#'},
	{'#','.','.','.',tree,'.','.','.',tree,tree,'.','.',traps,'.','.','.',tree,tree,tree,'.',tree,tree,tree,'.',undead,tree,tree,'.',portal,tree,tree,tree,'.',tree,tree,'#'},
	{'#','.','.',tree,tree,'.','.','.','.',tree,'.','.','.','.','.','.','.',tree,tree,tree,tree,tree,'.','.',tree,tree,tree,'.','.','.',tree,tree,'.','.',tree,'#'},
	{'#','.','.',tree,'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.',tree,tree,'.','.',tree,tree,tree,'.','.',tree,'.',tree,tree,tree,'.',tree,'#'},
	{'#','.','.','.','.','.','.','.','.','.',wall,wall,wall,tree,'.','.','.','.','.','.','.','.','.',tree,tree,tree,'.','.',tree,'.','.','.',tree,'.',tree,'#'},
	{'#',tree,'.',tree,tree,traps,tree,'.','.','.',wall,wall,wall,tree,'.','.','.','.','.','.','.','.','.',tree,tree,'.',treasure,tree,tree,tree,tree,'.',tree,'.',tree,'#'},
	{'#',tree,'.','.',tree,treasure,tree,tree,'.','.','.','.','.','.','.',wall,wall,wall,tree,'.','.','.','.','.',tree,tree,tree,tree,tree,'.','.','.','.','.',tree,'#'},
	{'#','.','.','.',tree,tree,tree,tree,'.','.','.','.',tree,'.','.',wall,wall,wall,tree,'.','.','.','.','.',tree,tree,tree,'.','.',traps,tree,tree,'.',tree,tree,'#'},
	{'#','.',tree,tree,tree,tree,tree,tree,tree,tree,'.',tree,tree,'.','.','.','.','.','.','.',tree,tree,'.','.',tree,tree,tree,tree,tree,tree,tree,tree,'.',tree,tree,'#'},
	{'#','.',tree,tree,tree,tree,tree,tree,'.','.',tree,'.','.',tree,'.',traps,'.','.','.','.',traps,tree,'.','.','.','.',tree,tree,tree,tree,tree,tree,'.',tree,tree,'#'},
	{'#','.','.',undead,treasure,tree,tree,'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.',tree,tree,tree,tree,tree,tree,tree,tree,'.','.',tree,'#'},
	{'#',traps,'.','.','.','.','.',traps,'.','.',wall,wall,wall,tree,'.','.',wall,wall,wall,tree,'.','.','.','.',tree,tree,tree,tree,tree,tree,tree,tree,tree,undead,tree,'#'},
	{'#','.',traps,'.','.','.','.','.','.','.',wall,wall,wall,tree,'.','.',wall,wall,wall,tree,'.',traps,'.',tree,'.','.','.',tree,tree,tree,tree,tree,tree,'.',tree,'#'},
	{'#','.','.',traps,'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.',tree,'.','.','.',tree,tree,tree,'.','.','#'},
	{'#','.','.',tree,tree,tree,'.','.','.','.','.',tree,'.','.','.','.','.','.','.','.','.','.',tree,tree,'.','.','.','.','.','.','.','.',tree,tree,'.','#'},
	{'#','.',tree,tree,tree,tree,tree,monster,tree,tree,tree,tree,'.',traps,'.','.',tree,wall,wall,wall,'.','.',tree,'.','.',traps,'.','.','.','.','.','.',tree,tree,'.','#'},
	{'#',tree,tree,tree,'.','.',tree,tree,'.','.',tree,'.','.','.','.','.',tree,wall,wall,wall,'.','.','.','.','.','.',tree,tree,tree,undead,undead,tree,tree,'.','.','#'},
	{'#',tree,'.','.','.','.',grave,grave,grave,'.',tree,'.','.','.','.','.','.','.','.','.','.','.','.',tree,tree,tree,tree,'.','.','.','.','.',tree,'.',tree,'#'},
	{'#',tree,'.',grave,'.','.','.','.',grave,'.',tree,tree,'.',tree,tree,tree,'.','.',tree,'.','.','.','.',tree,'.','.','.','.','.','.','.','.','.','.',tree,'#'},
	{'#',tree,tree,'.','.',grave,'.',grave,'.','.',tree,tree,'.',tree,tree,'.','.',tree,'.','.',tree,'.',tree,tree,'.',grave,'.',grave,'.',grave,'.',grave,'.',grave,'.','#'},
	{'#',tree,tree,tree,treasure,'.',traps,grave,'.','.',tree,tree,treasure,'.',tree,tree,tree,'.',tree,'.','.',tree,tree,tree,'.','.','.','.','.','.','.','.','.','.',tree,'#'},
	{'#',tree,tree,tree,tree,tree,tree,tree,tree,tree,tree,tree,tree,tree,tree,tree,tree,'.',tree,tree,'.','.',tree,tree,treasure,grave,'.',grave,'.',grave,'.',grave,'.',grave,tree,'#'},
	{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
	};

	for(int i=0; i<mapRow; i++)
	{
		for(int j=0; j<mapCol; j++)
		{
			map[i][j] = tempMap[i][j];
		}
	}
}
int invenAsk()
{
	for(int i=0; i<item->inventory.size(); i++)
	{
		cout<<"Item "<<i+1<<" : "<<item->inventory[i]<<endl;
	}

	int invenOption =0;
	cout<<"Please Select item: ";
	cin>>invenOption;

	return invenOption;
}
string wildlifeName()
{
    int random =rand()%3;
    if(random == 0)
    {
        return "Black Panther";
    }
    else if(random == 1)
    {
        return "Tiger";
    }
    else if(random == 2)
    {
        return "Giant Python";
    }
}
void UpdateInput()
{
    int random  = rand()%20;
	//store the old position before input
	player->rowOld = player->row;
	player->columnOld = player->column;

	if(GetAsyncKeyState(VK_LEFT))
	{
		if(player->column>1)
		{
			player->column--;
			player->step--;
			if(random == 0)
            {
                enemy = new Wildlife(wildlifeName());
                gameState = BATTLE;
            }
		}
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		if(player->column<mapCol-2)
		{
			player->column++;
			player->step--;
			if(random == 0)
            {
                enemy = new Wildlife(wildlifeName());
                gameState = BATTLE;
            }
		}
	}
	if(GetAsyncKeyState(VK_UP))
	{
		if(player->row>1)
		{
			player->row--;
			player->step--;
			if(random == 0)
            {
                enemy = new Wildlife(wildlifeName());
                gameState = BATTLE;
            }
		}
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		if(player->row<mapRow-2)
		{
			player->row++;
			player->step--;
			if(random == 0)
            {
                enemy = new Wildlife(wildlifeName());
                gameState = BATTLE;
            }
		}
	}
	if(GetAsyncKeyState(VK_ESCAPE))
	{
		if(!item->inventory.empty())
		{
			int selectedItem=0;
			gotoxy(mapOffsetX, mapOffsetY+mapRow +2);
			selectedItem = invenAsk();
			if(item->inventory[selectedItem-1] == "health potion")
			{
				player->health += 80;
				item->inventory.erase(item->inventory.begin()+selectedItem);
				cout<<"You used the health potion, you regen 80 health point!"<<endl;
			}
			else if(item->inventory[selectedItem-1] == "teleport potion")
			{
				for(int i=0; i<mapRow; i++)
				{
					for(int j=0; j<mapCol; j++)
					{
						if(map[i][j] == char(portal))
						{
							player->column = j;
							player->row = i;
						}
					}
				}
				item->inventory.erase(item->inventory.begin()+selectedItem);
				cout<<"You used teleport potion, you have been teleport another portal"<<endl;
				system("PAUSE");
				system("CLS");
			}
			else if(item->inventory[selectedItem-1] == "crystal skull")
			{
				cout<<"You cannot use this item right now"<<endl;
			}
		}
		else
		{
			gotoxy(mapOffsetX, mapOffsetY+mapRow +2);
			cout<<"Your inventory is empty";
		}
	}
}

void DisplayPlayerItem()
{
	textcolor(BLUE);
	gotoxy(42,12);
	cout<<"Player Item";
	gotoxy(42,13);
	cout<<"===========";
	textcolor(WHITE);
	gotoxy(42,14);
	if(item->axeDurability > 0)
	{
		cout<<"Axe Durability: "<<item->axeDurability;
	}
	else
	{
		textcolor(DARKGRAY);
		cout<<"Axe Durability:"<<item->axeDurability;
		textcolor(WHITE);
	}
	gotoxy(42,15);
	if(item->trapDetection == false)
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
	if(item->treasureHunter == false)
	{
		textcolor(DARKGRAY);
		cout<<"Treasure Map";
		textcolor(WHITE);
	}
	else
	{
		cout<<"Treasure Map";
	}
	for(int i=0; i<item->inventory.size();i++)
    {
        gotoxy(42,17+i);
        cout<<item->inventory[i];
    }
}

void ShowMap()
{
	for(int i=0; i<mapRow; i++)
	{
		for(int j=0; j<mapCol; j++)
		{
			gotoxy(mapOffsetX+j,mapOffsetY+i);

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
				if(item->trapDetection == false)
				{
					cout<<'.';
				}
				else if(item->trapDetection == true)
				{
					if(i<player->row - 1 || i>player->row + 1 || j<player->column - 1 || j>player->column + 1)
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
				if(item->treasureHunter == false)
				{
					if(i<player->row - 1 || i>player->row + 1 || j<player->column - 1 || j>player->column + 1)
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
				else if(item->treasureHunter == true)
				{
					if(i<player->row - 3 || i>player->row + 3 || j<player->column - 3 || j>player->column + 3)
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
			else if(map[i][j] == grave)
			{
				textcolor(LIGHTGRAY);
				cout<<map[i][j];
				textcolor(WHITE);
			}
			else if((map[i][j] == (char)undead) || (map[i][j] == (char)monster))
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
	gotoxy(mapOffsetX+player->column, mapOffsetY+player->row);
	textcolor(LIGHTGREEN);
	cout<<player->avatar;
	textcolor(WHITE);
}
void trap()
{
	gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
	int rd = rand()%3;
	if(rd == 0)
	{
		cout<<"You step on a trap, received 20 damaage";
		player->health -= 15;
	}
	else if(rd == 1)
	{
		enemy = new Undead("ZOMBIE");
		cout<<"A zombie jumping out from underground"<<endl;
		gameState = BATTLE;
	}
	else if(rd == 2)
	{
		cout<<"You dodged a trap";
	}
	map[player->row][player->column] = '*';
	system("PAUSE");
	if(player->health <= 0)
	{
		gameState = RESULT;
	}
}
void treasureCollide()
{
	int random;
    random = rand()%5+1;
    if(random == 1)
    {
        gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
        cout<<"You found some foods and drinks!";
        gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
        cout<<"(After having those food, you gain some health and now you have travel longer)";
        gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
        cout<<"( health + 20    steps + 20 )";
        player->health += 20;
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
                item->axeDurability += random;
            }
            case 2:
            {
                gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
                cout<<"There is an iron axe down here, the blade is still new but the handle seem will break after few use";
                item->axeDurability += random;
				}
            case 3:
            {
                gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
                cout<<"You found an axe, and it still in great condition";
                item->axeDurability += random;
            }
        }
    }
    else if(random == 4)
    {
        gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
        cout<<"You found a teleport potion!";
        gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
        cout<<"( after used, you will be teleport to the portal )";
        item->inventory.push_back("teleport potion");
    }
    else if(random == 5)
    {
        gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
        cout<<"You found a health potion!";
        gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
        cout<<"( health potion can regan character health)";
        item->inventory.push_back("health potion");
    }
	map[player->row][player->column] = '.';
}
void graveCollide()
{
    gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
    int random = rand()%5;
    if(random == 0)
    {
        cout<<"An undead climbing out from underground and attack you!";
        enemy = new Undead("Zombie");
        gameState = BATTLE;
    }
    else if(random == 1)
    {
        cout<<"You found a treasure map";
        item->treasureHunter = true;
    }
    else if(random == 2)
    {
        cout<<"You found a trap detector";
        item->trapDetection = true;
    }
    else if(random == 3)
    {
        cout<<"You found a bottle of potion";
        item->inventory.push_back("health potion");
    }
    else if(random == 4)
    {
        cout<<"You found a mystery crystal skull";
        item->inventory.push_back("crystal skull");
    }
    map[player->row][player->column] = '.';
}
void CollisionDetection()
{
	if(map[player->row][player->column] == (char)tree)
	{
		if(item->axeDurability > 0)
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
                map[player->row][player->column] = '.';
                item->axeDurability -= 1;
            }
            else if(choice == 2)
            {
                player->row = player->rowOld;
                player->column = player->columnOld;
            }
        }
		else
		{
			player->row = player->rowOld;
			player->column = player->columnOld;
		}
	}
	if(map[player->row][player->column] == (char)monster)
	{
		enemy = new Monster("Vampire");
		map[player->row][player->column] = '.';
		player->row = player->rowOld;
		player->column = player->columnOld;
		gameState = BATTLE;
	}
	else if(map[player->row][player->column] == (char)undead)
	{
		enemy = new Undead("Zombie");
		map[player->row][player->column] = '.';
		player->row = player->rowOld;
		player->column = player->columnOld;
		gameState = BATTLE;
	}
	if(map[player->row][player->column] == (char)wall)
	{
		player->row = player->rowOld;
		player->column = player->columnOld;
	}
	else if(map[player->row][player->column] == (char)grave)
	{
		graveCollide();
	}
	else if(map[player->row][player->column] == (char)treasure)
	{
		treasureCollide();
	}
	else if(map[player->row][player->column] == traps)
	{
		trap();
	}
}
void DisplayPlayerAvatar()
{
	if(player->type == TREASURE_HUNTER)
	{
		gotoxy(62,3);
		cout<<"     ,...,";
		gotoxy(62,4);
		cout<<"     |. .|";
		gotoxy(62,5);
		cout<<"     q - p";
		gotoxy(62,6);
		cout<<"     |\\'/|";
		gotoxy(62,7);
		cout<<"  .-''---''-.";
		gotoxy(62,8);
		cout<<" / ,       , \\";
		gotoxy(62,9);
		cout<<"/\\/\\   Y   /\\/\\";
		gotoxy(62,10);
		cout<<"\\ \\ | ~ ~ | / /";
	}
	else if(player->type == TOMB_RAIDER)
	{
		gotoxy(62,3);
		cout<<"     ,.,";
		gotoxy(62,4);
		cout<<"   ,((()),";
		gotoxy(62,5);
		cout<<"  ,((/\"\\))";
		gotoxy(62,6);
		cout<<"  ,)\\'-'/(";
		gotoxy(62,7);
		cout<<"  ((()'()))";
		gotoxy(62,8);
		cout<<"  /')\\_/('\\";
		gotoxy(62,9);
		cout<<" / (_   _)|";
		gotoxy(62,10);
		cout<<" \\ \\)   ( |";
		gotoxy(62,11);
		cout<<"  \\ \\   / |";
	}
	else if(player->type == MONKEY)
	{
		gotoxy(62,3);
		cout<<"         .-\"\"\"-.";
		gotoxy(62,4);
		cout<<"       _/-=-.   \\";
		gotoxy(62,5);
		cout<<"      (_|a a/   |_";
		gotoxy(62,6);
		cout<<"       / \"  \\   ,_)";
		gotoxy(62,7);
		cout<<"  _    \\`=' /__/";
		gotoxy(62,8);
		cout<<" / \\_  .;--'  `-.";
		gotoxy(62,9);
		cout<<" \\___)//      ,  \\";
		gotoxy(62,10);
		cout<<"  \\ \\/;        \\  \\";
		gotoxy(62,11);
		cout<<"   \\_.|         | |";
	}
}
void BattleSimulation(Character *actor, Character *target)
{
    if(actor->actionList[choice-1] == ATTACK )
    {
        int tempDamage = actor->offense*(1.0f-target->defense/100.00f);
        target->health -= tempDamage;
        cout<<actor->name<<" ATTACKED "<<target->name<<" with "<<tempDamage<<" damage!"<<endl;
    }
    else if(actor->actionList[choice-1] == STUN )
    {
        int random = rand()%3;
        if(random == 0)
        {
            int tempDamage = actor->offense*(1.0f-target->defense/130.00f);
            target->health -= tempDamage;
            cout<<"Fail to stun"<<endl;
            cout<<actor->name<<" ATTACKED "<<target->name<<" with "<<tempDamage<<" damage!"<<endl;
        }
        else if(random == 1 || random == 2 )
        {
            target->isStunned = true;
            int tempDamage = actor->offense*(1.0f-target->defense/130.00f);
            target->health -= tempDamage;
            cout<<"Enemy Stunned !!"<<endl;
            cout<<actor->name<<" ATTACKED "<<target->name<<" with "<<tempDamage<<" damage!"<<endl;
        }
    }
    else if(actor->actionList[choice-1] == DODGE )
    {
        int random = rand()%3;
        if(random == 0)
        {
            int tempDamage = actor->offense*(1.0f-target->defense/130.00f);
            target->health -= tempDamage;
            cout<<"Fail to dodge"<<endl;
            cout<<actor->name<<" ATTACKED "<<target->name<<" with "<<tempDamage<<" damage!"<<endl;
        }
        else if(random == 1)
        {
            actor->isDodged = true;
            int tempDamage = actor->offense*(1.0f-target->defense/130.00f);
            target->health -= tempDamage;
            cout<<"You dodge enemy attack !!"<<endl;
            cout<<actor->name<<" ATTACKED "<<target->name<<" with "<<tempDamage<<" damage!"<<endl;
        }
    }
    else if(actor->actionList[choice-1] == HEAL)
    {
        int healAmount = actor->defense*(2.0f-actor->offense/100.00f);
        actor->health += healAmount;
        cout<<"You healed yourself "<<healAmount<<" Health"<<endl;
    }
    else if(actor->actionList[choice-1]== ITEM)
    {
        if(!item->inventory.empty())
		{
			int selectedItem=0;
			gotoxy(mapOffsetX, mapOffsetY+mapRow +2);
			selectedItem = invenAsk();
			if(item->inventory[selectedItem-1] == "health potion")
			{
				player->health += 80;
				item->inventory.erase(item->inventory.begin()+selectedItem);
				gotoxy(mapOffsetX, mapOffsetY+mapRow +4);
				cout<<"You used the health potion, you regen 80 health point!"<<endl;
			}
			else if(item->inventory[selectedItem-1] == "teleport potion")
			{
				for(int i=0; i<mapRow; i++)
				{
					for(int j=0; j<mapCol; j++)
					{
						if(map[i][j] == char(portal))
						{
							player->column = j;
							player->row = i;
						}
					}
				}
				gameState = MAP;
				item->inventory.erase(item->inventory.begin()+selectedItem);
				gotoxy(mapOffsetX, mapOffsetY+mapRow +4);
				cout<<"You successful escape from the fight by using teleport potion"<<endl;
				system("PAUSE");
				system("CLS");
			}
			else if(item->inventory[selectedItem-1] == "crystal skull")
            {
                target->health = 0;
                gameState = MAP;
				item->inventory.erase(item->inventory.begin()+selectedItem);
				gotoxy(mapOffsetX, mapOffsetY+mapRow +4);
				cout<<"The enemy and crystal skull disappear after a flash of light"<<endl;
            }
		}
		else
		{
			gotoxy(mapOffsetX, mapOffsetY+mapRow +2);
			cout<<"Your inventory is empty";
		}
    }
}

void ShowBattleResult()
{
    gotoxy(mapOffsetX, mapOffsetY + mapRow + 13);
    string resultText = "";
    if(player->health <=0 && enemy->health <=0)
    {
        resultText = "Both are dead. It is a draw";
    }
    else if(player->health <= 0)
    {
        resultText = "You are dead. Your lost";
    }
    else if(enemy->health<=0)
    {
        resultText = "Enemy is dead. Your Win !";
    }
    gameState = MAP;
    cout<<endl;
    system("PAUSE");
}

void DisplayBattleScreen()
{
    player->DisplayStats(1,10);
    enemy->DisplayStats(30,10);

    cout<<endl<<endl;
    cout<<"======================="<<endl;
    cout<<"Please select an ACTION"<<endl;
    cout<<"======================="<<endl;
    for(int i=0; i<player->actionList.size();i++)
    {
        cout<<(i+1)<<player->GetCharActionName(player->actionList[i])<<endl;
    }
    cout<<"======================="<<endl;
    cout<<"Your input : ";
    cin>>choice;
    BattleSimulation(player,enemy);

    //! enemy
    if(enemy->isStunned == false && player->isDodged == false && enemy->health >= 0)
    {
        choice = rand()%enemy->actionList.size()+1;
        BattleSimulation(enemy,player);
    }
    cout<<endl;
    system("PAUSE");
    if(enemy->health<= 0)
    {
        ShowBattleResult();
    }
    if(player->health<=0)
    {
        isVictory = false;
        gameState = RESULT;
    }

    cout<<endl;
    system("PAUSE");
}
void CheckWinGameCondition()
{
    int crystalSkull = 0;
    for(int i=0;i<item->inventory.size();i++)
    {
        if(item->inventory[i] == "crystal skull")
        {
            crystalSkull++;
        }
    }
    if(crystalSkull >= 3)
    {
        gotoxy(mapOffsetX, mapOffsetY + mapRow + 11);
        cout<<"You found 3 crystal skulls, you escaped from the illusion of this jungle and finally found the way out";
        isVictory = true;
        gameState = RESULT;
    }

    int monsterLeft = 0;
    for(int i=0; i<mapRow; i++)
    {
        for(int j=0; j<mapCol; j++)
        {
            if(map[i][j] == char(undead))
            {
                monsterLeft++;
            }
            else if(map[i][j] == char(monster))
            {
                monsterLeft++;
            }
        }
    }
    if(monsterLeft == 0)
    {
        gotoxy(mapOffsetX, mapOffsetY + mapRow + 11);
        cout<<"All threat in this jungle have been slain, now you can wait for the rescue peacefully";
        isVictory = true;
        gameState = RESULT;
    }
}
int main()
{
    system("mode con: cols=80 lines=50");
    srand(time(NULL));
    InitializeMap();

    textcolor(WHITE);
    do
    {
        if(gameState == MAIN_MENU)
        {
            DisplayMainMenu();
        }
        else if(gameState == CHARACTER_SELECTION)
        {
            DisplayCharacterSelection();
        }
        else if(gameState == MAP)
        {
            do
            {
                system("CLS");
                UpdateInput();
                CollisionDetection();
                ShowMap();
                DisplayPlayerAvatar();
                DisplayPlayerItem();
                CheckWinGameCondition();
                gotoxy(mapOffsetX, mapOffsetY + mapRow + 13);
                system("PAUSE");
            }while(gameState == MAP);
        }
        else if(gameState == BATTLE)
        {
            DisplayBattleScreen();
        }
        else if(gameState == RESULT)
        {
            if(isVictory)
            {
                cout<<"You Won!"<<endl;
            }
            else
            {
                system("CLS");
                gotoxy(15,25);
                textcolor(RED);
                cout<<"XXX   You Die In The Search!   XXX"<<endl;
                textcolor(WHITE);
                gotoxy(mapOffsetX, mapOffsetY + mapRow + 13);
                system("PAUSE");
            }
            choice = -1;
        }
        system("CLS");
    }while(choice != -1);
    system("PAUSE");
    return 0;
}
