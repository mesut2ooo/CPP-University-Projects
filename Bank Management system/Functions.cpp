#include <iostream>
#include <chrono>
#include <thread>
#include "Classes.h"

using namespace std;

void printMenu()
{
    system("clear");
    cout << "1.Clerk\n";
    cout << "2.Manager\n";
    cout << "3.Customer\n";
    cout << "4.Exit\n";
    cout << "Enter :  ";
}

void printClerkMenu()
{
    system("clear");
    cout << "1.Show personal info\n";
    cout << "2.Show Customer info\n";
    cout << "3.Create an account\n";
    cout << "4.Delete a Customer\n";
    cout << "5.Exit\n";
    cout << "Enter :  ";
}

void printManagerMenu()
{
    system("clear");
    cout << "1.Show personal info\n";
    cout << "2.Show Customer info\n";
    cout << "3.Create an account\n";
    cout << "4.Delete a Customer\n";
    cout << "5.Show personnel info\n";
    cout << "6.Hire a clerk\n";
    cout << "7.Fire a clerk\n";
    cout << "8.Saving clerk worked hours\n";
    cout << "9.Eit\n";
    cout << "Enter :  ";
}

void printCustomerMenu()
{
    system("clear");
    cout << "1.Put money\n";
    cout << "2.Take money\n";
    cout << "3.Show personal and account info\n";
    cout << "4.Exit\n";
    cout << "Enter :  ";
}

// vector<Customer> customers;
// vector<Clerk> clerks;

Clerk getClerk()
{
    while (true)
    {
        cout << "Enter the personnel number :  ";
        long int pn;
        cin >> pn;

        int index = 0;
        bool flag {false};
        for (auto clerk : clerks)
        {
            if (clerk.getPersonnelID() == pn)
            {
                flag = true;
                break;
            }
            index++;
        }

        if (flag)
            return clerks[index];
        else    
        {
            cout << "cant find the personnel try again\nthe first person is 11111\n\n";
        }
    }
}

void stopTime(int seconds) 
{
    this_thread::sleep_for(chrono::seconds(seconds));
}

Customer getCustomer()
{
    while (true)
    {
        cout << "Enter the Customer national ID :  ";
        long int pn;
        cin >> pn;

        int index = 0;
        bool flag {false};
        for (auto customer : customers)
        {
            if (customer.getNationalID() == pn)
            {
                flag = true;
                break;
            }
            index++;
        }

        if (flag)
            return customers[index];
        else    
        {
            cout << "cant find the personnel try again\n\n";
        }
    }
}
