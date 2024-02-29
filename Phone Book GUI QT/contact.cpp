#include "contact.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

/* constructor , deconstructor and methods for Contact class */
// Constructor for contact
Contact::Contact(string fname, string lname, string em) {
    firstName = fname;
    lastName = lname;
    email = em;
}

void Contact::displayContact() const{
    cout << "name:  " << firstName << " " << lastName << endl;
    cout << "email: " << email << endl;
    for(auto const& number : numbers)
    {
        switch (number.type)
        {
        case 0:
            cout << "FAX : ";
            break;
        case 1:
            cout << "OFFICE : ";
            break;
        case 2:
            cout << "WORK : ";
            break;
        case 3:
            cout << "HOME : ";
            break;
        case 4:
            cout << "MAIN : ";
            break;
        }

        cout << number.number << endl;
    }
}

void Contact::addPhoneNumber(phoneType type, const string &number)
{
    phoneNumber phone;
    phone.type = type;
    phone.number = number;
    numbers.push_back(phone);
}
/* Contact class ended here */

/* constructor , deconstructor and methods for PhoneBook class */
// Constructor to load files
PhoneBook::PhoneBook()
{
    ifstream inputFile("contacts.txt");
    if (inputFile.is_open()) {
        while (true) {
            string fname, lname, em;
            if (!(inputFile >> fname >> lname >> em)) {
                break;  // Exit the loop if there's an issue with reading data
            }

            Contact newContact(fname, lname, em);

            int type;
            string number;
            while (inputFile >> type >> number) {
                newContact.addPhoneNumber(static_cast<phoneType>(type), number);
            }

            contacts.push_back(newContact);

            inputFile.clear();
        }

        inputFile.close();
    } else {
        cerr << "Error opening file for reading." << endl;
    }
}

// Destructor to save files
PhoneBook::~PhoneBook()
{
    saveToFile();
}


void PhoneBook::saveToFile()
{
    ofstream outputFile("contacts.txt");
    if (outputFile.is_open()) {
        for (const auto& contact : contacts) {
            outputFile << contact.getFName() << " " << contact.getLName() << " " << contact.getEmail() << endl;

            for (const auto& number : contact.getNumbers()) {
                outputFile << static_cast<int>(number.type) << " " << number.number << endl;
            }
        }

        outputFile.close();
    }
    else {
        cerr << "Error opening file for writing." << endl;
    }
}

void PhoneBook::addContact(const Contact& newCont)
{
    contacts.push_back(newCont);
}

void PhoneBook::setAnotherNumber(phoneType type, const string &number, int indexToChange)
{
    contacts[indexToChange].addPhoneNumber(type, number);
}

void PhoneBook::clearTheContacts()
{
    contacts.clear();
}

void PhoneBook::SortByFirstName()
{
    sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b)
        {
            if (a.getFName() != b.getFName())
                return a.getFName() < b.getFName();
            return a.getLName() < b.getLName();
        });
}

void PhoneBook::SortByLastName()
{
    sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b)
         {
            if  (a.getLName() != b.getLName())
                 return a.getLName() < b.getLName();
            return a.getFName() < b.getFName();
         });
}

void PhoneBook::deleteContactByIndex(size_t index)
{
    if (index < contacts.size())
    {
        contacts.erase(contacts.begin() + index);
    }
}
/* PhoneBook class ended here */
