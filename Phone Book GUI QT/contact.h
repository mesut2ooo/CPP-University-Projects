#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include <vector>
using namespace std;
enum phoneType  {FAX , OFFICE, WORK, HOME, MAIN}; // an enum for the type of the number

// a structure for the number and its type
struct phoneNumber{
    phoneType type;
    string number;
};

typedef vector<phoneNumber> natV; // number and type vector


class Contact
{
private:
    string firstName;
    string lastName;
    string email;
    natV numbers; // a vector of numbers (structures)

public:
    Contact(string fname, string lname, string em); // constructor
    string getFName()const {return firstName;};
    string getLName()const {return lastName;};
    string getEmail()const {return email;};
    natV getNumbers()const {return numbers;};

    void displayContact() const;
    void addPhoneNumber(phoneType type, const string& number);

};

typedef vector<Contact> Contacts; // a vector of objects

class PhoneBook
{
private:
    Contacts contacts;
public:
    PhoneBook();
    ~PhoneBook();

    Contacts getContacts()const {return contacts;};

    void addContact(const Contact& newCont);
    void saveToFile();
    void setAnotherNumber(phoneType type, const string& number, int indexToChange);
    void clearTheContacts();
    void SortByFirstName();
    void SortByLastName();
    void deleteContactByIndex(size_t index);
};

#endif // CONTACT_H
