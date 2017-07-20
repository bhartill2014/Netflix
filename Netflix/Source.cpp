#include<iostream>
#include<string>
#include"Queue.h"

using namespace std;

void createProfile()
{

	ProfileList user;
	int choice = 0;
	
	cout << "Welcome to the Netflix Movie Menu! Please select (or create) a profile: " << endl;

	user.showList(choice);
}

void main()
{
	createProfile();
}