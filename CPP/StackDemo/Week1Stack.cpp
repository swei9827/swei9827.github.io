#include <iostream>
#include "windows.h"
#include <stack>
#include <queue>
using namespace std;

stack<int> myStack;

void DisplayStack(stack<int> tempStack)
{
    cout<<"==========================="<<endl;
    if(tempStack.empty())
    {
        cout<<"Stack is Empty!"<<endl;
    }
    else
    {
        while(tempStack.size()>0)
        {
            cout<<tempStack.top()<<endl;
            tempStack.pop();
        }
    }
    cout<<"=========================="<<endl;
}
void ClearStack(stack<int>& realStack)
{
    while(!realStack.empty())
    {
        realStack.pop();
    }
}
void ReverseStack(stack<int>& realStack, stack<int> tempStack)
{
    ClearStack(realStack);
    while(!tempStack.empty())
    {
        realStack.push(tempStack.top());
        tempStack.pop();
    }
}
int main()
{
    bool isExit = false;

    do
    {
        int choice =- 1;
        int value = 0;
        cout<<"The stack program"<<endl;
        DisplayStack(myStack);
        cout<<"1. Add to the stack"<<endl;
        cout<<"2. Remove from the stack"<<endl;
        cout<<"3. Reverse the stack"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Your Choice: ";
        cin>>choice;
        cout<<"============================"<<endl;
        if(choice == 1)
        {
            cout<<"Value to be added : ";
            cin>>value;
            myStack.push(value);
        }
        else if(choice == 2)
        {
            if(myStack.empty())
            {
                cout<<"There is nothing to be pop anymore"<<endl;
            }
            else
            {
                myStack.pop();
            }
        }
        else if(choice == 3)
        {
            ReverseStack(myStack,myStack);
        }
        else if(choice == 4)
        {
            isExit = true;
        }
        system("PAUSE");
        system("CLS");
    }while(!isExit);
}
