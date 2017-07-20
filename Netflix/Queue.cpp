#include "Queue.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

NetflixNode::NetflixNode(string title, int date, string rate, int ranking, string genre)
{
	setName(title);
	setYear(date);
	setRating(rate);
	setRank(ranking);
	setCategory(genre);
	setNextTitle(nullptr);
	setLastTitle(nullptr);
}

void NetflixNode::setName(string title)
{
	name = title;
}

string NetflixNode::getName()
{
	return name;
}

void NetflixNode::setYear(int date)
{
	year = date;
}

int NetflixNode::getYear()
{
	return year;
}

void NetflixNode::setRating(string rate)
{
	rating = rate;
}

string NetflixNode::getRating()
{
	return rating;
}

void NetflixNode::setRank(int ranking)
{
	rank = ranking;
}

int NetflixNode::getRank()
{
	return rank;
}

void NetflixNode::setCategory(string category)
{
	genre = category;
}

string NetflixNode::getCategory()
{
	return genre;
}

void NetflixNode::setNextTitle(NetflixNode* nxt)
{
	nextTitle = nxt;
}

NetflixNode* NetflixNode::getNextTitle()
{
	return nextTitle;
}

void NetflixNode::setLastTitle(NetflixNode* lst)
{
	lastTitle = lst;
}

NetflixNode* NetflixNode::getLastTitle()
{
	return lastTitle;
}

NetflixQueue::NetflixQueue() :firstNode(nullptr), lastNode(nullptr)
{
	size = 0;
	firstNode = nullptr;
	lastNode = nullptr;
}

int NetflixQueue::getSize()
{
	return size;
}

void NetflixQueue::push_back(NetflixNode* newNode)
{
	if (firstNode == nullptr) //if there is nothing in the array
	{
		firstNode = newNode; //a new node is added to the array
	}
	else
	{
		NetflixNode* temp = firstNode;
		
		while (temp->getNextTitle() != nullptr)
		{
			temp = temp->getNextTitle();
		} 

		temp->setNextTitle(newNode);
		newNode->setLastTitle(temp);
		lastNode = newNode;
	}
	size++;
}

void NetflixQueue::showQueue(int option)
{
	if (size != 0)
	{
		NetflixNode* temp = firstNode;
		string genre;
		string rating;
		vector<NetflixNode*>rank;

		if (option == 1) //high rank to low rank
		{
			for (int i = 0; i < size; i++)
			{
				rank.push_back(temp);
				temp = temp->getNextTitle();
			}

			sort(rank);

			cout << "The movies in your Netflix queue are:" << endl;
			cout << "-----------------------------------" << endl;

			for (int k = 0; k < size; k++)
			{
				showNode(rank[k]);
			}
		}
		else if (option == 2) // low rank to high rank
		{
			for (int i = 0; i < size; i++)
			{
				rank.push_back(temp);
				temp = temp->getNextTitle();
			}

			sort(rank);

			cout << "\nThe movies in your Netflix queue are:" << endl;
			cout << "----------------------------------- " << endl;

			for (int k = size - 1; k >= 0; k--)
			{
				showNode(rank[k]);
			}
		}
		else if (option == 3) //by rating
		{
			cout << "Enter a Rating: ";
			cin >> rating;
			cout << endl;
			cout << "The movies in your Netflix Queue with a Rating of " << rating << " are:" << endl;
			cout << "----------------------------------- " << endl;

			while (temp != nullptr)
			{
				if (temp->getRating() == rating)
				{
					showNode(temp);
				}
				temp = temp->getNextTitle();
			} 

		}
		else if (option == 4) //by genre
		{
			cout << "Enter a Category: ";
			cin.ignore();
			getline(cin, genre);
			cout << endl;
			cout << "The movies in your Netflix Queue with a Category of " << genre << " are:" << endl;
			cout << "----------------------------------- " << endl;

			while (temp != nullptr)
			{
				if (temp->getCategory() == genre)
				{
					showNode(temp);
				}
				temp = temp->getNextTitle();
			}

		}
		else if (option == 5)
		{
			cout << "Exiting display menu." << endl;
			cout << endl;
		}
		else
			cout << "Invalid option, please try again!" << endl;
	}
	else
		cout << "The movie queue is empty! Please add movies to the queue." << endl;
}

void NetflixQueue::clearQueue()
{
	NetflixNode* temp = firstNode;
	NetflixNode* toClear = nullptr;

	while (temp != nullptr)
	{
		toClear = temp;
		temp = temp->getNextTitle();
		delete toClear;
		--size;
	} 

	cout << "The list has been destroyed." << endl;
}

void NetflixQueue::clearNode(string name, int year)
{
	NetflixNode* temp = findNode(name, year);

	if (temp == nullptr)
	{
		cout << "ERROR 404: MOVIE NOT FOUND" << endl;
		cout << endl;
	}
	else //first node needs to be deleted
	{
		if (temp == firstNode)
		{
			firstNode = temp->getNextTitle();
			delete temp;
			if (firstNode != nullptr)
				firstNode->setLastTitle(nullptr);
		}
		else if (temp == lastNode)
		{
			lastNode = temp->getLastTitle();
			delete temp;
			lastNode->setNextTitle(nullptr);
		}
		else
		{
			NetflixNode* lastTitle = temp->getLastTitle();
			NetflixNode* nextTitle = temp->getNextTitle();
			delete temp;
			lastTitle->setNextTitle(nextTitle);
			nextTitle->setLastTitle(lastTitle);
		}
		size--;
		cout << "Movie deleted!" << endl;
		cout << endl;
	}
}

NetflixNode* NetflixQueue::findNode(string name, int year)
{
	NetflixNode* temp = firstNode;

	do
	{
		if (temp->getName() == name)
		{
			if (temp->getYear() == year)
			{
				break;
			}
		}
		temp = temp->getNextTitle();
	} while (temp != nullptr);

	return temp;
}

void NetflixQueue::changeNode(string name, int year)
{
	NetflixNode* temp = findNode(name, year);

	if (temp == nullptr)
	{
		cout << "ERROR 404: MOVIE NOT FOUND" << endl;
		cout << endl;
	}
	else
	{
		string genre;
		int ranking;
		string rating;
		cin.ignore();
		
		cout << "Enter New Movie Name : ";
		getline(cin, name);

		cout << "Enter Year: ";
		cin >> year;
		cout << "Enter Category: ";
		cin.ignore();
		getline(cin, genre);
		cout << "Rating: ";
		cin >> rating;
		cout << "Ranking (1-5): ";
		cin >> ranking;
		
		temp->setName(name);
		temp->setYear(year);
		temp->setCategory(genre);
		temp->setRating(rating);
		temp->setRank(ranking);
		cout << "Movie Edited!"<<endl;
	}
}

void NetflixQueue::showNode(NetflixNode* node)
{
	if (node == nullptr)
	{
		cout << "ERROR 404: MOVIE NOT FOUND" << endl;
		cout << endl;
	}

	else
	{
		cout << node->getName() << endl;
		cout << "Year: " << node->getYear() << endl;
		cout << "Category: " << node->getCategory() << endl;
		cout << "Rated: " << node->getRating() << endl;
		cout << "Ranked: ";

		for (int i = 0; i < node->getRank(); i++)
		{
			cout << "*"; //displays the number of stars specified by rank
		}
		cout << endl;
		cout << "-------------------------" << endl;
	}
}

void NetflixQueue::sort(vector<NetflixNode*>&rank)
{
	for (int i = 1; i < size; i++)
	{
		if ((rank[i])->getRank() <= (rank[i - 1])->getRank())
		{
			continue;
		}
		else
		{
			for (int j = i; j > 0; j--)	 
			{
				if ((rank[j])->getRank() > (rank[j - 1])->getRank()) 
				{
					swap(rank[j], rank[j - 1]);
				}
				else   
				{
					break;
				}

			}
		}
	}
}

void NetflixQueue::mainMenu()
{
	int option = 0;
	string name;
	int year = 0;
	string rating;
	int rank = 0;
	string genre;
	NetflixQueue list;
	int displayOption = 0;

	cout << "Welcome to the Netflix Movie Queue!" << endl;

	while (option != 6)
	{
		cout << "1. Display Movie Queue" << endl;
		cout << "2. Add Movie to Queue" << endl;
		cout << "3. Edit Movie in Queue" << endl;
		cout << "4. Remove Movie from Queue" << endl;
		cout << "5. Search for Movie in Queue" << endl;
		cout << "6. Exit Program" << endl;
		cout << endl;
		cout << "Enter option: ";
		cin >> option;

		if (option == 1)
		{
			if (list.getSize() == 0)
			{
				cout << endl;
				cout << "The movie queue is empty! Please add movies to the queue." << endl;
				cout << endl;
			}
			else
			{
				while (displayOption != 5)	// 5 is exit menu
				{
					cout << endl;
					cout << "Display options:" << endl;
					cout << "1. Highest to Lowest Ranking" << endl;
					cout << "2. Lowest to Highest Ranking" << endl;
					cout << "3. Filter by Rating" << endl;
					cout << "4. Filter by Category" << endl;
					cout << "5. Exit Display Menu" << endl;
					cout << endl;
					cout << "Enter option: ";
					cin >> displayOption;
					list.showQueue(displayOption);
				}
			}

		}
		else if (option == 2)
		{
			cout << endl;
			cout << "Enter Movie Name: ";
			cin.ignore();
			getline(cin, name);
			cout << "Enter Year: ";
			cin >> year;
			cout << "Enter Category: ";
			cin.ignore();
			getline(cin, genre);
			cout << "Rating: ";
			cin >> rating;
			cout << "Ranking (1-5): ";
			cin >> rank;

			list.push_back(new NetflixNode(name, year, rating, rank, genre)); //added to the list
			cout << endl;
			cout << "Movie added to the queue!" << endl;
			cout << endl;
		}
		else if (option == 3)
		{
			if (list.getSize() == 0)
			{
				cout << endl;
				cout << "The movie queue is empty! Please add movies to the queue." << endl;
				cout << endl;
			}
			else
			{
				cout << "Enter Movie Name: ";
				cin.ignore();
				getline(cin, name);
				cout << "Enter Movie Year: ";
				cin >> year;
				list.changeNode(name, year);
			}
		}
		else if (option == 4)
		{
			if (list.getSize() == 0)
			{
				cout << endl;
				cout << "The movie queue is empty! Please add movies to the queue." << endl;
				cout << endl;
			}
			else
			{
				cout << "Enter Movie Name: ";
				cin.ignore();
				getline(cin, name);
				cout << "Enter Movie Year: ";
				cin >> year;
				list.clearNode(name, year);
			}
		}
		else if (option == 5)
		{
			if (list.getSize() == 0)
			{
				cout << endl;
				cout << "The movie queue is empty! Please add movies to the queue." << endl;
				cout << endl;
			}
			else
			{
				cout << "Enter Movie Name: ";
				cin.ignore();
				getline(cin, name);
				cout << "Enter Movie Year: ";
				cin >> year;
				cout << endl;
				list.showNode(list.findNode(name, year));
			}

		}
		else if (option > 6)
		{
			cout << "Invalid entry, please try again!" << endl;
			cout << endl;
		}
	}

	cout << endl;
	list.clearQueue();
	cout << "Good bye!" << endl;
	system("pause");
}

ProfileNode::ProfileNode(string label, string fName, string lName, int num)
{
	setProfileLabel(label);
	setFirstName(fName);
	setLastName(lName);
	setAge(num);
	setNextProfile(nullptr);
	setLastProfile(nullptr);
}

void ProfileNode::setProfileLabel(string label)
{
	profileLabel = label;
}

string ProfileNode::getProfileLabel()
{
	return profileLabel;
}

void ProfileNode::setFirstName(string fName)
{
	firstName = fName;
}

string ProfileNode::getFirstName()
{
	return firstName;
}

void ProfileNode::setLastName(string lName)
{
	lastName = lName;
}

string ProfileNode::getLastName()
{
	return lastName;
}

void ProfileNode::setAge(int num)
{
	age = num;
}

int ProfileNode::getAge()
{
	return age;
}

void ProfileNode::setNextProfile(ProfileNode* next)
{
	nextProfile = next;
}

ProfileNode* ProfileNode::getNextProfile()
{
	return nextProfile;
}

void ProfileNode::setLastProfile(ProfileNode* last)
{
	lastProfile = last;
}

ProfileNode* ProfileNode::getLastProfile()
{
	return lastProfile;
}

ProfileList::ProfileList() :fNode(nullptr), lNode(nullptr)
{
	listSize = 0;
	fNode = nullptr;
	lNode = nullptr;
}

int ProfileList::getListSize()
{
	return listSize;
}

void ProfileList::push_back(ProfileNode* newProfile)
{
	if (fNode == nullptr) //if there is nothing in the array
	{
		fNode = newProfile; //a new node is added to the array
	}
	else
	{
		ProfileNode* Temp = fNode;

		while (Temp->getNextProfile() != nullptr)
		{
			Temp = Temp->getNextProfile();
		}

		Temp->setNextProfile(newProfile);
		newProfile->setLastProfile(Temp);
		lNode = newProfile;
	}
	listSize++;
}
void ProfileList::showProfile(ProfileNode* node)
{
		cout << node->getProfileLabel() << endl;
}

void ProfileList::clearList()
{
	ProfileNode* temp = fNode;
	ProfileNode* toClear = nullptr;

	while (temp != nullptr)
	{
		toClear = temp;
		temp = temp->getNextProfile();
		delete toClear;
		--listSize;
	}

	cout << "The profiles have been destroyed." << endl;
}

int ProfileList::showList(int option)
{
	int age = 0;
	string profileLabel;
	string firstName;
	string lastName;
	int choice = 0;
	ProfileNode* temp = fNode;
	vector<ProfileNode*>users;

	cout << "1. Add New Profile" << endl;
	cout << "2. Exit Program" << endl;
	cout << "Enter option: ";
	cin >> choice;

	if (choice == 2)
	{
		clearList();
		cout << "Good bye!" << endl;
		return 0;
		system("pause");
	}
	else
	{
		cout << "Enter Profile Label: ";
		cin.ignore();
		getline(cin, profileLabel);
		cout << "Enter First Name: ";
		cin >> firstName;
		cout << "Enter Last Name: ";
		cin >> lastName;
		cout << "Enter Age: ";
		cin >> age;

		push_back(new ProfileNode(profileLabel, firstName, lastName, age));

		cout << "Profile Created!" << endl;
	}

	while (listSize != 0)
	{
		for (int i = 0; i < listSize; i++)
		{
			push_back(temp);
			temp = temp->getNextProfile();
			cout << i << ". ";
			showProfile(users[i]);
		}

		cout << listSize + 2 << ". Add New Profile" << endl;
		cout << listSize + 3 << ". Exit Program" << endl;
		cout << "Enter option: " << endl;
		cin >> choice;

		if (choice <= listSize)
		{
			NetflixQueue mainMenu();
		}
		else if (choice == listSize + 2)
		{
			cout << "Enter Profile Label: ";
			cin.ignore();
			getline(cin, profileLabel);
			cout << "Enter First Name: ";
			cin >> firstName;
			cout << "Enter Last Name: ";
			cin >> lastName;
			cout << "Enter Age: ";
			cin >> age;

			push_back(new ProfileNode(profileLabel, firstName, lastName, age));

			cout << "Profile Created!" << endl;
		}
		else if (choice == listSize + 2)
		{
			clearList();
			cout << "Good Bye!" << endl;
			return 0;
			system("pause");
		}
	}	
}
