#include <iostream>
#include <string>
#include "functions.h"
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;

// sleep for a given seconds
void Sleep(int second)
{
	this_thread::sleep_for(chrono::seconds(second)); 
}

// printing a template for a better TUI exprience
void PrintTemplate()
{
	system("clear");
	cout << "*******************************\n";
	cout << "          **********           \n";
	cout << "         Phone Book App        \n";
	cout << endl;
}

// printing the welcome screen
void WelcomeScreen()
{
	PrintTemplate();
	cout <<"#####  Hello and Welcome  #####";
	cout << endl;
}

// printing the main menu
void PrintMenu()
{
	PrintTemplate();
	cout << "**  1. Add contact\n";
	cout << "**  2. Search\n";
	cout << "**  3. Remove contact\n";
	cout << "**  4. Delete the phonebook\n";
	cout << "**  5. List all contacts\n";
	cout << "**  6. Sort\n";
	cout << "**  7. Save\n";
	cout << "**  8. Quit\n\n";
	cout << "**  Enter the number of the opton :  ";
}

// a function to get personal info and return it as a structure
PersonalInfo GetPersonInfo()
{
	PersonalInfo person;

	// getting first name , last name , email
	cout << "Enter you're first name:  ";
	getline(cin, person.firstName);

	cout << "Enter you're last name:  ";
	getline(cin, person.lastName);

	cout << "Enter you're email(if none hit enter):  ";
	getline(cin, person.email);
	if (person.email == "")
		person.email = "none@none.none";

	
	// getting the phone numbers
	bool flag {true};
	while(flag)
	{

		Phone temp;

		// knowing the type of the number based on enum values
		bool thisflag = true;
		cout << "1.Main\n2.Home\n3.Fax\n4.Work\n5.Office\n";
		cout << "Which phone number do you:  ";
		while (thisflag)
		{
			char tempt; // temp for temp phone type
			cin >> tempt;

			switch (tempt)
			{
				case '1':
					temp.type = MAIN;
					thisflag = false;
					break;
				case '2':
					temp.type = HOME;
					thisflag = false;
					break;
				case '3':
					temp.type = FAX;
					thisflag = false;
					break;
				case '4':
					temp.type = WORK;
					thisflag = false;
					break;
				case '5':
					temp.type = OFFICE;
					thisflag = false;
					break;
				default:
					cout << "1/2/3/4/5:  ";
					continue;
			}
			cin.ignore();
		}
		
		// getting the number
		cout << "Enter the number:  ";
		getline(cin, temp.number);

		person.phoneNumbers.push_back(temp); // add the number to numbers

		// deciding to enter another number or not
		char tempChar;
		while (flag)
		{
			cout << "You want to enter another number('y' or 'n'):  ";
			cin >> tempChar;
			if (tempChar == 'y' || tempChar == 'Y')
			{
				flag = true;
				break;
			}
			else if (tempChar == 'n' || tempChar == 'N')
				flag = false;
			else 
				cout << "Y or N:  ";
		}
	}

	return person;

}

// showing all the iformation of the given contacts
void ShowPersons(vector<PersonalInfo> persons)
{
	int count = 1;
	
	// a loop for each person
	for (const auto& person : persons)
	{
		cout << "(" << count << ") :" << endl;
		cout << "First name: " << person.firstName << endl;
		cout << "Last name: " << person.lastName << endl;
		cout << "Email: " << person.email << endl;
		cout << "Phones :\n";
	
		// aloop for numbers
		for (const auto& phoneNumber : person.phoneNumbers)
		{
			switch (phoneNumber.type)
			{
				case 1:
					cout << "MAIN\t:\t";
					break;
				case 2:
					cout << "HOME\t:\t";
					break;
				case 3:
					cout << "FAX\t:\t";
					break;
				case 4:
					cout << "WORK\t:\t";
					break;
				case 5:
					cout << "OFFICE\t:\t";
					break;
				default:
					cout <<"UNKNOWN\t:\t";
					break;
			}

			cout << phoneNumber.number << endl;
		}
		cout << "\n---------------------------------\n";
		count++;
	}
}

// showing the info of just one person
void ShowPerson(PersonalInfo person)
{
	cout << "First name: " << person.firstName << endl;
	cout << "Last name: " << person.lastName << endl;
	cout << "Email: " << person.email << endl;
	cout << "Phones :\n";
	
	// aloop for numbers
	for (const auto& phoneNumber : person.phoneNumbers)
	{
		switch (phoneNumber.type)
		{
			case 1:
				cout << "MAIN\t:\t";
				break;
			case 2:
				cout << "HOME\t:\t";
				break;
			case 3:
				cout << "FAX\t:\t";
				break;
			case 4:
				cout << "WORK\t:\t";
				break;
			case 5:
				cout << "OFFICE\t:\t";
				break;
			default:
				cout <<"UNKNOWN\t:\t";
				break;
		}

		cout << phoneNumber.number << endl;
	}
		cout << "\n---------------------------------\n";
}

// sorting the phonebook and return the vector
vector<PersonalInfo> SortPhones(vector<PersonalInfo> Persons, char lf)
{
	while (true)
	{
		// sort based on first name
		if (lf == 'f')
		{
			for (auto i = Persons.begin(); i != Persons.end(); i++)
			{
				for (auto j = i+1; j != Persons.end(); j++)
				{
					PersonalInfo temp;
					if (i->firstName > j->firstName)
					{
						temp = *j;
						*j = *i;
						*i = temp;
					}
				}
			}
			break;
		}

		// sort based on last name
		if (lf == 'l')
		{
			for (auto i = Persons.begin(); i != Persons.end(); i++)
			{
				for (auto j = i+1; j != Persons.end(); j++)
				{
					PersonalInfo temp;
					if (i->lastName > j->lastName)
					{
						temp = *j;
						*j = *i;
						*i = temp;
					}
				}
			}
			break;
		}
	
		else
		{
			cout << "WRONG chatacter !!!   l or f: ";
			cin >> lf;
		}
	}

	return Persons;
}

// for searching based on a string of name or number
void Search(vector<PersonalInfo> Persons, string searchstr, char lfn)
{
	int counter = 1;
	for (auto const& person : Persons)
	{
		switch (lfn)
		{
			case 'f':
				if (person.firstName.find(searchstr) != string::npos)
					{
						cout << "(" << counter << ") :" << endl;
						ShowPerson(person);
					}
				break;
			case 'l':
				if (person.lastName.find(searchstr) != string::npos)
					{
						cout << "(" << counter << ") :" << endl;
						ShowPerson(person);
					}
				break;
			case 'n':
				for (auto const& numbers : person.phoneNumbers)
				{
					if (numbers.number.find(searchstr) != string::npos)
					{
						cout << "(" << counter << ") :" << endl;
						ShowPerson(person);
						break;
					}
				}
				break;
			default:
				break;
		}
		counter++;
	}

}

// delete with the index number
void DeleteInstance(vector<PersonalInfo>& Persons, size_t index)
{
	if (index > Persons.size()) // if the index is out of range
		cout << "OUT OF INDEX" << endl;
	else
	{
		Persons.erase(Persons.begin() + index);
		cout << "Deleted" << endl;
	}
}

// saving to the file
void SaveToFile(const vector<PersonalInfo>& Persons) {
    ofstream outFile("phonebook.dat", ios::binary);

    if (outFile.is_open()) {
        for (const auto& person : Persons) {
            // Write personal info
            outFile.write(person.firstName.c_str(), person.firstName.size() + 1);
            outFile.write(person.lastName.c_str(), person.lastName.size() + 1);
            outFile.write(person.email.c_str(), person.email.size() + 1);

            // Write phone numbers
            size_t numPhones = person.phoneNumbers.size();
            outFile.write(reinterpret_cast<const char*>(&numPhones), sizeof(size_t));

            for (const auto& phone : person.phoneNumbers) {
                outFile.write(phone.number.c_str(), phone.number.size() + 1);
                outFile.write(reinterpret_cast<const char*>(&phone.type), sizeof(PhoneType));
            }
        }

        cout << "Saved to file" << endl;
        outFile.close();
    } else {
        cerr << "Unable to open the file for writing" <<  endl;
    }
}

// reading from the file
void ReadFromFile(vector<PersonalInfo>& Persons) {
    ifstream inFile("phonebook.dat", ios::binary);

    if (inFile.is_open()) {
        Persons.clear();  // Clear existing data in the vector

        while (!inFile.eof()) {
            PersonalInfo person;

            // Read personal info
            getline(inFile, person.firstName, '\0');
            getline(inFile, person.lastName, '\0');
            getline(inFile, person.email, '\0');

            // Read phone numbers
            size_t numPhones;
            inFile.read(reinterpret_cast<char*>(&numPhones), sizeof(size_t));

            for (size_t i = 0; i < numPhones; ++i) {
                Phone phone;
                getline(inFile, phone.number, '\0');
                inFile.read(reinterpret_cast<char*>(&phone.type), sizeof(PhoneType));
                person.phoneNumbers.push_back(phone);
            }

            Persons.push_back(person);
        }

        cout << "Read from file" << endl;
        inFile.close();
    } else {
        cerr << "Unable to open the file for reading" << endl;
    }
}
