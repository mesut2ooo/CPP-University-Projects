#include <iostream>
#include "Classes.h"

using namespace std;

long long int Account::firstID = 123456789101;

Account::Account():accountID(firstID++), creationDate(), credit(0), activeOrNot(true) {}

void Account::setAccount(Date _creationDate, long long int _credit, bool _activeOrNot)
{
    creationDate = _creationDate;
    credit = _credit;
    activeOrNot = _activeOrNot;
}

void Account::increaseCredit(long int newCredit)
{
    credit += newCredit;
}

void Account::decreaseCredit(long int newCredit)
{
    if (activeOrNot)
        credit -= newCredit;
    else
        cout << " We can't take money from that account because it is not active\n";
}

void Account::showAccountInformation()
{
    cout << "\nAccount ID   :  " << accountID;
    cout << "\nCredit       :  " << credit;
    cout << "\nCreated      :  " ;creationDate.showDate();
    if (activeOrNot)
        cout << "\nActivation   :  Active";
    else
        cout << "\nActivation   :  Not Active";

}

void Account::toggleActivation()
{
    activeOrNot = !activeOrNot;
}
