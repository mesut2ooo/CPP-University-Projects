#ifndef CLASSES_H
#define CLASSES_H

#include <string>
#include <vector>
using namespace std;


class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date();
    void showDate();
    void setDate(int _day, int _month, int _year);

};


class Account
{
private:
    static long long int firstID;
    long long int accountID;
    long long int credit;
    Date creationDate;
    bool activeOrNot;

public:
    Account();
    void setAccount(Date creationDate, long long int credit, bool activeOrNot);
    void increaseCredit(long int newCredit);
    void decreaseCredit(long int newCredit);
    void showAccountInformation();
    void toggleActivation();
};

class Customer
{
private:
    string firstName;
    string lastName;
    long int nationalID;
    Date birthDate;
    Account account;

public:
    void setCustomer(string _firstName, string _lastName, long int _nationalID, Date _birthDate, Account _account);
    void putMoney(long int money);
    void takemoney(long int money);
    void showAllInformation();
    long int getNationalID();
    void toggleActivation();
};

extern vector<Customer> customers;


class Clerk
{
private:
    static long int firstPersonnelNumber;
    string firstName;
    string lastName;
    long int personnelNumber;
    Date birthDate;
    long int leastSalary = 10000000;
    static const int mustWorkHours = 250;
    int workedHours = 0;

public:
    Clerk(string _fname, string _lname);
    void setWorkHours(int hours);
    long int paycheck();
    bool createAccount();
    void toggleActive();
    void showAccounteeInfo();
    long int getPersonnelID();
    void showPersonnelInfo();
    void removeCustomer();
    string getFirstName();
};


extern vector<Clerk> clerks;


class Manager : public Clerk
{
public:
    Manager(string _fname, string _lname);
    void setNames(string _fname, string _lname);
    void showPersonnelsInfo();
    void addClerk();
    void removeClerk();
    void setWorkingHours();
};

struct Bank
{
    public:
        string bankName = "Sample";
        string branchName = "SubSample";
        long int branchCode = 1111111;
        Manager manager;
        vector<Customer> bankCustomers;
        vector<Clerk> bankClerks;
};





void printMenu();
void printCustomerMenu();
void printManagerMenu();
void printClerkMenu();
Clerk getClerk();
void stopTime(int seconds);
Customer getCustomer();



#endif // CLASSES_H
