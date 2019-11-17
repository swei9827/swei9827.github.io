// Iterator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "windows.h"
#include <vector>
#include <map>
#include <list>
#include <unordered_map>

using namespace std;

class Com
{
public:
	int num;
	Com()
	{
		cout << "Com1" << endl;
	}
	Com(int value)
	{
		num = value;
		cout << "Com2" << endl;
	}
	~Com()
	{
		cout << "~Com" << endl;
	}
};
int main()
{
	vector<Com*> listContainer;
	Com *com1 = new Com(1);
	Com *com2 = new Com(2);
	Com *com3 = new Com(3);
	listContainer.push_back(com1);
	listContainer.push_back(com2);
	listContainer.push_back(com3);


	//list<int>::iterator iter = listContainer.begin();
	////list<int>::iterator iter3;
	//while (iter != listContainer.end())
	//{
	//	if (*iter == 300)
	//	{
	//		listContainer.erase(iter);
	//	}
	//	else
	//	{	
	//		int theNumber = *iter;
	//	}		
	//}

	//list<int>::reverse_iterator riter = listContainer.rbegin();
	//while (riter != listContainer.rend())
	//{
	//	cout << *riter << endl;
	//	riter++;
	//}

	//vector<int> vectorContainer;
	//vectorContainer.push_back(100);
	//vectorContainer.push_back(200);
	//vectorContainer.push_back(300);
	//vectorContainer.push_back(400);


	//vector<int>::iterator iter2 = vectorContainer.begin();

	//while (iter2 != vectorContainer.end())
	//{
	//	int theNumber = *iter2;
	//	cout << theNumber << endl;
	//	iter2++;
	//}

	vector<Com*>::iterator iter = listContainer.begin();
	while (iter != listContainer.end())
	{
		Com& theCom = **iter;
		cout << theCom.num << endl;
		iter++;
	}

	iter = listContainer.begin();
	while (iter != listContainer.end())
	{
		delete *iter; // delete the object
		iter = listContainer.erase(iter);
	}


	system("PAUSE");
	return 0;
}


