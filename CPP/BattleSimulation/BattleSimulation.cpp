#include <iostream>
#include "windows.h"

using namespace std;
//! struct	-user define structure
//!			-what attribute or data required
//!			-what method or functions required
int round=1;

struct Hero
{
	char type;
	int hp, mhp;
	int level;
	double attackPower;
	
	void Initialize(char t,int h, int le, double att)
	{
		type = t;
		hp =h;
		mhp = hp;
		level = le;
		attackPower = att;
	}
	
	void DisplayStat()
	{
		cout<<"Hero Stat:"<<endl;
		cout<<"==========="<<endl;
		if(type == 'W')
		{
			cout<<"Type = Warrior"<<endl;
		}
		else if(type == 'A')
		{
			cout<<"Type = Archer"<<endl;
		}
		cout<<"HP ="<<hp<<endl;
		cout<<"Level = "<<level<<endl;
		cout<<"Attack Power ="<<attackPower<<endl;
	
	}
	
	void BattleSimulation(Hero tempHero)
	{
		hp = hp-(mhp * (tempHero.attackPower/100));
		if(hp<=0)
		{
			hp=0;
			cout<<type<<" hitted by "<<tempHero.type<<" ,"<<type<<" left "<<hp<<" HP"<<endl;
			cout<<tempHero.type<<" win!!!"<<endl;
		}
		else
		{
		cout<<type<<" hitted by "<<tempHero.type<<" ,"<<type<<" left "<<hp<<" HP"<<endl;
		}
	}
};



int main()
{
	Hero hero1;
	hero1.Initialize('W',150,1,5.5);
	
	Hero hero2;
	hero2.Initialize('A',100,1,8.5);
	
	hero1.DisplayStat();
	cout<<endl<<endl;
	hero2.DisplayStat();
	
	//! battle simulation
	do
	{
		cout<<endl;
		cout<<"Battle Simulation Round "<<round<<endl;
		cout<<"==========================="<<endl;
		round++;
		if(hero2.hp>0)
		{
			hero1.BattleSimulation(hero2);
		}
		if(hero1.hp>0)
		{
			hero2.BattleSimulation(hero1);
		}
	}while(hero1.hp>0 && hero2.hp>0);
	
	system("PAUSE");
	return 0;
}
