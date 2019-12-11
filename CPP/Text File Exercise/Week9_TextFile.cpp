#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	//!output file stream -> write in to the text file
	ofstream myfile;
	//!open the text file,if the file is not exist,the requested text file will be create
	myfile.open("example.text");
	myfile<<"Writing this to a file.\n";
	//!requiered to close the raeget text file,after complete all the transaction
	myfile.close();
	system("PAUSE");
	return 0;
}
