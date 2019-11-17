#include "windows.h"
#include <iostream>
#include "CircularBuffer.h"

using namespace std;

int main()
{
	CircularBuffer cBuffer;

	cout << "\n === CPP Circular buffer check ===\n";
	cout << "Size:" << cBuffer.getSize()<<endl;

	MyType x = 3;
	cout << "Push 1 , value : " << x << endl;
	cBuffer.pushBack(x);

	x = cBuffer.getAt(1);
	cout << "Get : " << x << endl;
	cout << cBuffer.getSize() << endl;
	cBuffer.clear();
	cout << cBuffer.getSize() << endl;
	for (int i = 0; i < 9; i++)
	{
		x = i;
		cBuffer.pushBack(x);
	}

	x = cBuffer.getAt(1);
	cout << "Get 1: " << x << endl;
	x = cBuffer.getAt(2);
	cout << "Get 2: " << x << endl;
	x = cBuffer.getAt(3);
	cout << "Get 3: " << x << endl;
	x = cBuffer.getAt(4);
	cout << "Get 4: " << x << endl;

	cout << cBuffer.getSize()<<endl;






	system("PAUSE");
	return 0;
}