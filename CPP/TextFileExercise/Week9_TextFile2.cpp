#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ofstream myfile("test.txt");

	if(myfile.is_open())
	{
		myfile<<"This is a line.\n";
		myfile<<"This is another line.\n";
		myfile.close();
	}
	else
	{
		cout<<"unable to open file"<<endl;
	}
	system("PAUSE");
	return 0;
}
