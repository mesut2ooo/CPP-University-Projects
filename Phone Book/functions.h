#include <vector>
#include <string>
using namespace std;


enum PhoneType {MAIN = 1, HOME, FAX, WORK, OFFICE}; // we have 5 phone types

struct Phone // each phone number has a type and a number
{
	string number;
	PhoneType type;
};

struct PersonalInfo // personal info has a name and some phone numbers
{
	string firstName;
	string lastName;
	string email;

	vector<Phone> phoneNumbers;
};

// defining the functions
void Sleep(int);
void PrintTemplate();
void WelcomeScreen();
void PrintMenu();
PersonalInfo GetPersonInfo();
void ShowPersons(vector<PersonalInfo>);
void ShowPerson(PersonalInfo);
vector<PersonalInfo> SortPhones(vector<PersonalInfo>, char);
void Search(vector<PersonalInfo>, string, char);
void DeleteInstance(vector<PersonalInfo>&, size_t);
void SaveToFile(const vector<PersonalInfo>&);
void ReadFromFile(vector<PersonalInfo>&);
