#include <iostream>
#include "functions.h"

using namespace std;

int main()
{
	bool flag {true}; // a flag to resume or end the program
	WelcomeScreen(); 
	Sleep(3);

	vector<PersonalInfo> Persons; // a vector of a structure of personal info a.k.a contacts
	ReadFromFile(Persons);
	Persons.pop_back(); // the last element is empty

	while(flag)
	{

		PersonalInfo temp;
		char option;
		char tempchar;
		string searchstr;
		char searchchar;

		PrintMenu();

		// getting the right option from the user
		while (true)
		{
			cin >> option;
			if (option > '0' && option < '9')
				break;
			else
			{
				cout << "** 1, 2, 3, 4, 5, 6, 7, 8:  ";
				continue;
			}
		}

		cin.ignore(); // clearing the buffer

		switch (option)
		{
			// adding a contact
			case '1':
				PrintTemplate();
				temp = GetPersonInfo();
				Persons.push_back(temp);
				break;

			// searching for a contact
			case '2':
				PrintTemplate();
				cout << "there is three options to search\nf, l, n:  ";
			
				// options to search are f , l , n
				while (true)
				{
					cin >> searchchar;
					if (searchchar == 'l' || searchchar == 'f' || searchchar == 'n')
						break;
					else
						cout << "WRONG INPUT!!!!  l, f, n:  ";
				}

				cin.ignore();

				// getting the search string to search
				cout << "Enter the string you want to search:  ";
				getline(cin, searchstr);

				Search(Persons, searchstr, searchchar);

				// ending the search by getting a character
				cout << "Enter anything to exit";
				cin >> searchchar;
				break;

			// deleting a contact
			case '3':

				// this part is like searching
				PrintTemplate();
				cout << "there is three options to search\nf, l, n:  ";
				while (true)
				{
					cin >> searchchar;
					if (searchchar == 'l' || searchchar == 'f' || searchchar == 'n')
						break;
					else
						cout << "WRONG INPUT!!!!  l, f, n:  ";
				}
				cin.ignore();
				cout << "Enter the string you want to search:  ";
				getline(cin, searchstr);

				Search(Persons, searchstr, searchchar);
				//end of search

				// deleting by entering the index number
				int numberToDelete;
				cout << "Enter the line number you want to delete:  ";
				cin >> numberToDelete;
				DeleteInstance(Persons, numberToDelete-1);
				Sleep(2);
				break;
			
			// clearing the whole phonebook
			case '4':
				Persons.clear();
				Sleep(2);
				break;

			// showing the whole phonebook
			case '5':
				PrintTemplate();
				ShowPersons(Persons);
				cout << "Enter anything to exit:  ";
				cin >> searchchar;
				break;

			// sorting 
			case '6':
				cout << "Sort by first / last name (l, f): ";
				cin >> tempchar;
				Persons = SortPhones(Persons, tempchar);
				Sleep(2);
				break;

			// saving
			case '7':
				SaveToFile(Persons);
				Sleep(2);
				break;

			// exit
			case '8':
				Sleep(2);
				flag = false;
				break;

			default: 
				break;

		}
	}
}
