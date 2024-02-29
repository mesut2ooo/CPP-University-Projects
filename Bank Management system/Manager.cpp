#include "Classes.h"
#include <iostream>
#include <vector>

using namespace std;

Clerk firstClerk("Masoud","Gholypur");
Clerk secondClerk("James","Bond");
Clerk thirdClerk("Mammad","Golzar");
vector<Clerk> clerks = {firstClerk,secondClerk,thirdClerk};

Manager::Manager(string fname, string lname): Clerk(fname, lname) {}

void Manager::showPersonnelsInfo()
{
    long int pNum;
    cout << "Enter the personnel number :  ";
    cin >> pNum;

    bool flag {true};
    for (auto& clerk : clerks)
    {
        if (pNum == clerk.getPersonnelID())
        {
            clerk.showPersonnelInfo();
            flag = false;
            break;
        }
    }

    if (flag)
        cout << "The personnel with this ID does'nt found\n";
}

void Manager::addClerk()
{
    cin.ignore();
    string fname, lname;
    cout << "Enter the first name of the new clerk  :  ";
    getline(cin, fname);

    cout << "Enter the last name of the new clerk   :  ";
    getline(cin, lname);

    cin.ignore();

    Clerk newClerk(fname,lname);

    clerks.push_back(newClerk);
}

void Manager::removeClerk()
{
    long int removeID;
    cout << "Enter the ID of the clerk you want to delete  :  ";
    cin >> removeID;

    for (auto clerk = clerks.begin(); clerk != clerks.end();)
    {
        if (clerk -> getPersonnelID() == removeID)
        {
            clerk = clerks.erase(clerk);
            cout << "clerk removed successfully\n";
        }
        else
            clerk++;
    }
}

void Manager::setWorkingHours()
{
    cin.ignore();
    for (auto& clerk : clerks)
    {
        int workedHour;
        cout << "Enter the worked Hours for " << clerk.getFirstName() << " (" << clerk.getPersonnelID() << ")  :  ";
        cin >> workedHour;
        clerk.setWorkHours(workedHour);
    }
}

void Manager::setNames(string _fname, string _lname)
{
    Clerk(_fname,_lname);
}
