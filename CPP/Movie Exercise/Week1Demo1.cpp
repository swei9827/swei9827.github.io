#include <iostream>
#include <sstream>
#include <ctime>
#include "windows.h"

using namespace std;

struct MovieTicket
{
    string title;
    string seat;

    void RandomizeTicket()
    {
        stringstream ss;
        ss<<(rand()%10+1);
        title ="Movie: " + ss.str();
        ss.str("");
        ss.clear();
        ss<<(rand()%10+1);
        seat = "Seat : " + ss.str();
    }
    void ShowDetails()
    {
        cout<<"Title : "<<title<<endl;
        cout<<"Seat : "<<seat<<endl;
    }
};

struct MyADT
{
    string text01;
    string text01Title;
    string text02;
    string text02Title;

    void RandomizeData()
    {
        stringstream ss;
        ss<<(rand()%10+1);
        text01=text01Title + " " +ss.str();
        ss.str("");
        ss.clear();
        ss<<(rand()%10+1);
        text02=text02Title + " " +ss.str();
    }
    void ShowDetails()
    {
        cout<<text01<<endl;
        cout<<text02<<endl;
    }
};

int main(int argc, _TCHAR* argv[])
{

    srand(time(NULL));
    const int TOTAL_MOVIE_TICKET = 10;
    MovieTicket movieTicket [TOTAL_MOVIE_TICKET];

    for(int i=0; i<TOTAL_MOVIE_TICKET; i++)
    {
        movieTicket[i].RandomizeTicket();
        movieTicket[i].ShowDetails();
    }

    MyADT myADT [TOTAL_MOVIE_TICKET];
    string movieTitle;
    string movieSeat;
    for(int i=0; i<TOTAL_MOVIE_TICKET; i++)
    {
        cout<<i+1<<endl;
        cin>>movieTitle;
        cin>>movieSeat;
        myADT[i].text01Title = movieTitle;
        myADT[i].text02Title = movieSeat;
        myADT[i].RandomizeData();
        myADT[i].ShowDetails();

    }
    system("PAUSE");
    return 0;
}
