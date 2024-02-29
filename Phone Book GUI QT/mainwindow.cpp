#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
#include "contact.h"
#include <string>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

PhoneBook myContacts; // initializing the object

// Showing all contacts
void MainWindow::on_showAllContactsButton_clicked()
{
    ui -> mainTextBrowser -> clear();
    int count {0};
    ui -> mainTextBrowser -> clear();
    Contacts showingContacts = myContacts.getContacts();
    for (auto const& person : showingContacts)
    {
        ui -> mainTextBrowser -> append(QString::number(count));
        ui -> mainTextBrowser -> append(QString::fromStdString(person.getFName()) + "  ");
        ui -> mainTextBrowser -> insertPlainText(QString::fromStdString(person.getLName()) + "          ");
        ui -> mainTextBrowser -> insertPlainText(QString::fromStdString(person.getEmail()));
        natV numbers = person.getNumbers();
        for(auto const& number : numbers)
        {
            switch (number.type)
            {
            case FAX:
                ui -> mainTextBrowser -> append("FAX  :  ");
                break;
            case OFFICE:
                ui -> mainTextBrowser -> append("OFFICE  :  ");
                break;
            case WORK:
                ui -> mainTextBrowser -> append("WORK  :  ");
                break;
            case HOME:
                ui -> mainTextBrowser -> append("HOME  :  ");
                break;
            case MAIN:
                ui -> mainTextBrowser -> append("MAIN  :  ");
                break;
            default:
                ui -> mainTextBrowser -> append("UNKNOWN  :  ");
                break;
            }

            ui -> mainTextBrowser -> insertPlainText(QString::fromStdString(number.number));
        }
        count++;
        ui -> mainTextBrowser -> append("-----------------------------------");
    }
}

// Add contact
void MainWindow::on_addContactButton_clicked()
{
    ui->mainTextBrowser->clear();

    string firstName{};
    string lastName{};
    string email{};

    // Getting the first name and last name
    QString fName = ui->firstNameLineEdit->text();
    firstName = fName.toStdString();
    QString lName = ui->lastNameLineEdit->text();
    lastName = lName.toStdString();
    // Getting the email
    QString emailq = ui->EmailLineEdit->text();
    email = emailq.isEmpty() ? "none@none.none" : emailq.toStdString(); // setting an email if nothing entered

    // if the first name or last name is empty
    if (fName.isEmpty() || lName.isEmpty())
    {
        ui->mainTextBrowser->append("!!!! Enter first name or last name or both !!!!");
        return;
    }

    // Initialize a new contact object
    Contact newCont(firstName, lastName, email);


    QString newNumQ = ui->phoneNumberLineEdit->text();

    if (newNumQ.isEmpty())
    {
        ui->mainTextBrowser->append("!!!! Enter a number !!!!");
        return;
    }


    // Getting the number and its type
    string newNum = newNumQ.toStdString();
    int temp = ui->phoneTypeCombo->currentIndex();
    phoneType type = static_cast<phoneType>(temp);
    newCont.addPhoneNumber(type, newNum);

    // contact added and we need to clear the line edits
    myContacts.addContact(newCont);
    ui -> mainTextBrowser -> append("New contact added successfully :)");
    ui -> firstNameLineEdit -> clear();
    ui -> lastNameLineEdit -> clear();
    ui -> EmailLineEdit ->clear();
    ui -> phoneNumberLineEdit -> clear();

}

// add another number
void MainWindow::on_addNumberPushButton_clicked()
{
    ui -> mainTextBrowser -> clear();
    // getting the number and type
    QString newNumQ = ui->phoneNumberLineEdit->text();
    string newNum = newNumQ.toStdString();
    int temp = ui->phoneTypeCombo->currentIndex();
    phoneType type = static_cast<phoneType>(temp);

    // Getting the index of the contact that you want to add another number
    QString contactIndexQ = ui -> contactIndexLineEdit -> text();
    bool isNumber;
    int contactIndex = contactIndexQ.toInt(&isNumber);

    // The number field is empty
    if (newNumQ.isEmpty())
    {
        ui->mainTextBrowser->append("!!!! Enter a number !!!!");
        return;
    }


    if (isNumber)
    {
        // out of range index
        if (contactIndex >= static_cast<int>(myContacts.getContacts().size()))
        {
            ui -> mainTextBrowser -> append("!!! INDEX OUT OF RANGE !!!");
            return;
        }
        // adding the new number
        else
            myContacts.setAnotherNumber(type, newNum, contactIndex);
    }
    else
    {
        ui -> mainTextBrowser -> append("!!! Enter a number for the index !!!");
        return;
    }


    ui -> mainTextBrowser -> append("New Number added successfully :)");
    ui -> phoneNumberLineEdit -> clear();

}

// Save all contacts
void MainWindow::on_saveContactsButton_clicked()
{
    // Making a message box
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Saving", "SAVE ?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        myContacts.saveToFile();
    }

}

// Deleting all contacts
void MainWindow::on_deleteAllContactsButton_clicked()
{
    // yes or no message box
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "DELETE EVERYTHING??", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        myContacts.clearTheContacts();
        ui -> mainTextBrowser -> clear();
        ui -> mainTextBrowser -> append("All contacts cleared!!!!");
    }
}


void MainWindow::on_sortButton_clicked()
{
    ui -> mainTextBrowser -> clear();
    int choosedOption = ui -> SortingOrSerachComboBox -> currentIndex();
    switch (choosedOption)
    {
    case 0:
        ui -> mainTextBrowser ->append("** Enter an option to sort **");
        break;
    case 1:
        myContacts.SortByFirstName();
        ui -> mainTextBrowser -> append("Sorted based on first name");
        break;
    case 2:
        myContacts.SortByLastName();
        ui -> mainTextBrowser -> append("Sorted based on last name");
        break;
    default: // if the number in combo box entered
        ui -> mainTextBrowser -> append("INVALID OPTION for this operation\nChoose another option");
        break;
    }
}

// Searching
void MainWindow::on_searchContactButton_clicked()
{
    ui -> mainTextBrowser -> clear();
    int choosedOption = ui -> SortingOrSerachComboBox -> currentIndex();

    if (choosedOption == 0)
        ui -> mainTextBrowser ->append("** Please enter an option **");

    // search and print by the first name
    else if (choosedOption == 1)
    {
        ui -> mainTextBrowser -> clear();
        QString searchPhraseQ = ui -> firstNameLineEdit -> text();
        string searchPhrase = searchPhraseQ.toStdString();
        int count {0};
        for (auto const& person : myContacts.getContacts())
        {
            string name = person.getFName();
            if (name.find(searchPhrase) != string::npos) // if there is what we want
            {
                ui -> mainTextBrowser -> append(QString::number(count));
                ui -> mainTextBrowser -> append(QString::fromStdString(person.getFName()) + "  ");
                ui -> mainTextBrowser -> insertPlainText(QString::fromStdString(person.getLName()) + "          ");
                ui -> mainTextBrowser -> insertPlainText(QString::fromStdString(person.getEmail()));
                natV numbers = person.getNumbers();
                for(auto const& number : numbers)
                {
                    switch (number.type)
                    {
                    case FAX:
                        ui -> mainTextBrowser -> append("FAX  :  ");
                        break;
                    case OFFICE:
                        ui -> mainTextBrowser -> append("OFFICE  :  ");
                        break;
                    case WORK:
                        ui -> mainTextBrowser -> append("WORK  :  ");
                        break;
                    case HOME:
                        ui -> mainTextBrowser -> append("HOME  :  ");
                        break;
                    case MAIN:
                        ui -> mainTextBrowser -> append("MAIN  :  ");
                        break;
                    default:
                        ui -> mainTextBrowser -> append("UNKNOWN  :  ");
                        break;
                    }

                    ui -> mainTextBrowser -> insertPlainText(QString::fromStdString(number.number));
                }
            }
            count++;
            ui -> mainTextBrowser -> append("");
        }
        ui -> firstNameLineEdit -> clear();
    }

    // search and print by the last name
    else if (choosedOption == 2)
    {
        ui -> mainTextBrowser -> clear();
        QString searchPhraseQ = ui -> lastNameLineEdit -> text();
        string searchPhrase = searchPhraseQ.toStdString();
        int count {0};
        for (auto const& person : myContacts.getContacts())
        {
            string name = person.getFName();
            if (name.find(searchPhrase) != string::npos)
            {
                ui -> mainTextBrowser -> append(QString::number(count));
                ui -> mainTextBrowser -> append(QString::fromStdString(person.getFName()) + "  ");
                ui -> mainTextBrowser -> insertPlainText(QString::fromStdString(person.getLName()) + "          ");
                ui -> mainTextBrowser -> insertPlainText(QString::fromStdString(person.getEmail()));
                natV numbers = person.getNumbers();
                for(auto const& number : numbers)
                {
                    switch (number.type)
                    {
                    case FAX:
                        ui -> mainTextBrowser -> append("FAX  :  ");
                        break;
                    case OFFICE:
                        ui -> mainTextBrowser -> append("OFFICE  :  ");
                        break;
                    case WORK:
                        ui -> mainTextBrowser -> append("WORK  :  ");
                        break;
                    case HOME:
                        ui -> mainTextBrowser -> append("HOME  :  ");
                        break;
                    case MAIN:
                        ui -> mainTextBrowser -> append("MAIN  :  ");
                        break;
                    default:
                        ui -> mainTextBrowser -> append("UNKNOWN  :  ");
                        break;
                    }

                    ui -> mainTextBrowser -> insertPlainText(QString::fromStdString(number.number));
                }
            }
            count++;
            ui -> mainTextBrowser -> append("");
        }
        ui -> lastNameLineEdit -> clear();
    }

    // search and print by any number
    else
    {
        ui -> mainTextBrowser -> clear();
        QString searchPhraseQ = ui -> phoneNumberLineEdit -> text();
        string searchPhrase = searchPhraseQ.toStdString();
        int count {0};
        for (auto const& person : myContacts.getContacts())
        {
            for (auto const& numberAndType : person.getNumbers())
            {
                string number = numberAndType.number;
                if (number.find(searchPhrase) != string::npos)
                {
                    ui -> mainTextBrowser -> append(QString::number(count));
                    ui -> mainTextBrowser -> append(QString::fromStdString(person.getFName()) + "  ");
                    ui -> mainTextBrowser -> insertPlainText(QString::fromStdString(person.getLName()) + "          ");
                    ui -> mainTextBrowser -> insertPlainText(QString::fromStdString(person.getEmail()));
                    natV numbers = person.getNumbers();
                    for(auto const& number : numbers)
                    {
                        switch (number.type)
                        {
                        case FAX:
                            ui -> mainTextBrowser -> append("FAX  :  ");
                            break;
                        case OFFICE:
                            ui -> mainTextBrowser -> append("OFFICE  :  ");
                            break;
                        case WORK:
                            ui -> mainTextBrowser -> append("WORK  :  ");
                            break;
                        case HOME:
                            ui -> mainTextBrowser -> append("HOME  :  ");
                            break;
                        case MAIN:
                            ui -> mainTextBrowser -> append("MAIN  :  ");
                            break;
                        default:
                            ui -> mainTextBrowser -> append("UNKNOWN  :  ");
                            break;
                        }

                        ui -> mainTextBrowser -> insertPlainText(QString::fromStdString(number.number));
                    }
                    break;
                }

            }
            count++;
            ui -> mainTextBrowser -> append("");
        }
        ui -> phoneNumberLineEdit -> clear();
    }
}

// Delete a contact
void MainWindow::on_deleteContactButton_clicked()
{
    // Getting the right index and delete the contact
    QString contactIndexQ = ui -> contactIndexLineEdit -> text();
    bool isNumber;
    int contactIndex = contactIndexQ.toInt(&isNumber);
    if (isNumber)
    {
        size_t indexToDelete = static_cast<size_t>(contactIndex);
        if (indexToDelete >= myContacts.getContacts().size())
        {
            ui -> mainTextBrowser -> append("OUT OF RANGE NUMBER");
            return;
        }
        else
        {
            myContacts.deleteContactByIndex(indexToDelete);
            ui -> mainTextBrowser -> append("contact deleted successfuly :)");
            ui -> contactIndexLineEdit -> clear();
            return;
        }
    }
    else
    {
        ui -> mainTextBrowser -> append("!!! Enter a number for the index !!!");
        ui -> contactIndexLineEdit -> clear();
    }
}

