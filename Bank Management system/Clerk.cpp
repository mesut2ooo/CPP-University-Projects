#include <iostream>
#include "Classes.h"
#include <ctime>
#include <vector>

using namespace std;

long int Clerk::firstPersonnelNumber = 11111;
vector<Customer> customers;

// Function to get the current day
int getCurrentDay() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return ltm->tm_mday;
}

// Function to get the current month
int getCurrentMonth() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return 1 + ltm->tm_mon;
}

// Function to get the current year
int getCurrentYear() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return 1900 + ltm->tm_year;
}


Clerk::Clerk(string _fname, string _lname)
{
    firstName = _fname;
    lastName = _lname;
    personnelNumber = firstPersonnelNumber++;

}

void Clerk::setWorkHours(int hours)
{
    workedHours = hours;
}

long int Clerk::paycheck()
{
    int offWork = mustWorkHours - workedHours;
    if (offWork < 15 && offWork >= 0)
        return leastSalary;
    else if (offWork >= 15)
        return leastSalary - offWork*100000;
    else
        return leastSalary - offWork*120000;
}

bool Clerk::createAccount()
{
    long int firstMoney;
    cout << "Enter how much money you want to start with :  "; cin >> firstMoney;

    if (firstMoney < 50000)
    {
        cout << "Sorry we cant create account , the credit is low\n";
        return false;
    }

    string fName, lName;
    long int natID;

    cin.ignore();

    cout << "Enter the first name :  ";
    getline(cin, fName);

    cout << "Enter the last name  :  ";
    getline(cin, lName);

    cout << "Enter the national ID :  ";
    cin >> natID;

    cin.ignore();

    Date bDate;
    int bDay, bMonth, bYear;
    cout << "Enter the birth date || year  month  day\n";
    cin >> bYear >> bMonth >> bDay;
    bDate.setDate(bDay, bMonth, bYear);

    Date crDate;
    int crDay = getCurrentDay();
    int crMonth = getCurrentMonth();
    int crYear = getCurrentYear();
    crDate.setDate(crDay,crMonth,crYear);

    bool acOrNo;
    cout << "Active / Not Active (A/N)  :  ";
    while (true)
    {
        char temp;
        cin >> temp;

        if (temp == 'A' || temp == 'a')
        {
            acOrNo = true;
            break;
        }
        else if (temp == 'N' || temp == 'n')
        {
            acOrNo = false;
            break;
        }
        else
            cout << "Ente N or A  :  ";
    }

    Account nAccount;
    nAccount.setAccount(crDate,firstMoney, acOrNo);

    Customer newCustomer;
    newCustomer.setCustomer(fName, lName, natID, bDate, nAccount);

    customers.push_back(newCustomer);
    return true;

}

void Clerk::toggleActive()
{
    long int natIDToToggle;
    cout << "Enter the national ID of the customer you want to toggle  :  ";
    cin >> natIDToToggle;

    bool flag {true};
    for (auto& customer : customers)
    {
        if (customer.getNationalID() == natIDToToggle)
        {
            customer.toggleActivation();
            cout << "Toggled\n";
            flag = false;
            break;
        }
    }

    if (flag)
        cout << "Customer not found\n";
}

void Clerk::showAccounteeInfo()
{
    long int natID;
    cout << "Enter the national ID :  ";
    cin >> natID;

    bool flag {true};
    for (auto& customer : customers)
    {
        if (customer.getNationalID() == natID)
        {
            customer.showAllInformation();
            flag = false;
            break;
        }
    }

    if (flag)
        cout << "Customer not found\n";
}

long int Clerk::getPersonnelID()
{
    return personnelNumber;
}

void Clerk::showPersonnelInfo()
{
    cout << "First Name   :  " << firstName;
    cout << "\nLast Name    :  " << lastName;
    cout << "\nPersonnel Number  :  " << personnelNumber;
    cout << "\nBirth date   :  "; birthDate.showDate();
    cout << "\nWorked Hours:" << workedHours << endl;
}

string Clerk::getFirstName()
{
    return firstName;
}

void Clerk::removeCustomer()
{
    cout << "Enter the Customer national ID that you want to delete :  ";
    long long int toDeleteCustomer;
    cin >> toDeleteCustomer;

    size_t index = 0;
    bool flag {false};
    for (auto& customer : customers)
    {
        if (customer.getNationalID() == toDeleteCustomer)
        {
            flag = true;
            break;
        }
        index++;
    }

    if (flag)
    {
        auto it = customers.begin() + index;
        customers.erase(it);
        cout << "The customer deleted\n";
    }

    else    
        cout <<"The customer not found\n";
}

