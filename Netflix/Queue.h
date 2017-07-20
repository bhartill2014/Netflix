#include <iostream>
#include <vector>
#include <string>
using namespace std;

class NetflixNode 
{
public:

	NetflixNode(string, int, string, int, string);

	void setName(string);
	string getName();

	void setYear(int);
	int getYear();

	void setRating(string);
	string getRating();

	void setRank(int);
	int getRank();

	void setCategory(string);
	string getCategory();

	void setNextTitle(NetflixNode*);
	NetflixNode* getNextTitle();

	void setLastTitle(NetflixNode*);
	NetflixNode* getLastTitle();

private:
	string name;
	int year;
	string rating;
	int rank;
	string genre;
	NetflixNode* nextTitle;
	NetflixNode* lastTitle;
};

class NetflixQueue
{
public:
	NetflixQueue();
	void push_back(NetflixNode*);
	int getSize();
	void showQueue(int);
	void clearQueue();
	void sortQueue();
	void clearNode(string, int);
	NetflixNode* findNode(string, int);
	void changeNode(string, int);
	void showNode(NetflixNode*);
	void sort(vector<NetflixNode*>&);
	void mainMenu();

private:
	int size;
	NetflixNode* firstNode;
	NetflixNode* lastNode;
};

class ProfileNode
{
public:

	ProfileNode(string, string, string, int);

	void setProfileLabel(string);
	string getProfileLabel();

	void setFirstName(string);
	string getFirstName();

	void setLastName(string);
	string getLastName();

	void setAge(int);
	int getAge();

	void setNextProfile(ProfileNode*);
	ProfileNode* getNextProfile();

	void setLastProfile(ProfileNode*);
	ProfileNode* getLastProfile();

private:
	string profileLabel;
	string firstName;
	string lastName;
	int age;
	ProfileNode* nextProfile;
	ProfileNode* lastProfile;
};

class ProfileList
{
public:
	ProfileList();
	void push_back(ProfileNode*);
	int showList(int);
	void showProfile(ProfileNode*);
	int getListSize();
	void clearList();

private:
	int currentUser;
	int listSize;
	ProfileNode* fNode;
	ProfileNode* lNode;
};