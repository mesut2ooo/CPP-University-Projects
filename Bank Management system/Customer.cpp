#include <iostream>
#include "Classes.h"

using namespace std;

void Customer::setCustomer(string _firstName, string _lastName, long int _nationalID, Date _birthDate, Account _account)
{
    firstName = _firstName;
    lastName = _lastName;
    nationalID = _nationalID;
    birthDate = _birthDate;
    account = _account;
}

void Customer::putMoney(long int money)
{
    account.increaseCredit(money);
}

void Customer::takemoney(long int money)
{
    account.decreaseCredit(money);
}

void Customer::showAllInformation()
{
    cout << "First Name   :  " << firstName;
    cout << "\nLast Name    :  " << lastName;
    cout << "\nNational ID  :  " << nationalID;
    cout << "\nBirth date   :  "; birthDate.showDate();
    cout << "\n\nAccount Info :"; account.showAccountInformation();
    cout << "\n";
}

long int Customer::getNationalID()
{
    return nationalID;
}

void Customer::toggleActivation()
{
    account.toggleActivation();
}
