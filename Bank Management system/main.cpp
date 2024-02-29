#include <iostream>
#include <limits>
#include "Classes.h"
using namespace std;

string bankName = "sample";
string branchName = "sub_sample";
long int brancCode = 123452;
Manager manager("boss", "bossy");

int main()
{
    while (true)
    {
        printMenu();
        char temp;
        char option;
        cin >> option;
        
        // clerk
        if (option == '1')
        {
            system("clear");
            Clerk nclerk = getClerk();

            while (true)
            {
                printClerkMenu();
                
                char option1;
                cin >> option1;
                
                // show the personnel info
                if (option1 == '1')
                {
                    nclerk.showPersonnelInfo();
                    cout << "\nEnter a char to exit :  ";
                    cin >> temp;
                }

                // show the customer info
                else if(option1 == '2')
                {
                    nclerk.showAccounteeInfo();
                    cout << "\nEnter a char to exit :  ";
                    cin >> temp;
                }

                // create account
                else if (option1 == '3')
                {
                    nclerk.createAccount();
                    stopTime(2);
                }
                
                //delet customer
                else if (option1 == '4')
                {
                    nclerk.removeCustomer();
                    stopTime(2);
                }
                //break
                else if(option1 == '5')
                {
                    system("clear");
                    break;
                }

                else
                {
                    continue;
                }
            }
        }

        // Manager
        else if (option == '2')
        {
            system("clear");

            while (true)
            {
                printManagerMenu();

                char option2;
                cin >> option2;
                
                // show the personnel info
                if (option2 == '1')
                {
                    manager.showPersonnelInfo();
                    cout << "\nEnter a char to exit :  ";
                    cin >> temp;
                }

                // show the customer info
                else if(option2 == '2')
                {
                    manager.showAccounteeInfo();
                    cout << "\nEnter a char to exit :  ";
                    cin >> temp;
                }

                // create account
                else if (option2 == '3')
                {
                    manager.createAccount();
                    stopTime(2);
                }
                
                //delet customer
                else if (option2 == '4')
                {
                    manager.removeCustomer();
                    stopTime(2);
                }

                // Show personnel info
                else if (option2 == '5')
                {
                    manager.showPersonnelsInfo();
                    cout << "Enter a character to exit  :  ";
                    cin >> temp;
                }

                // add clerk
                else if (option2 == '6')
                {
                    manager.addClerk();
                    stopTime(2);
                }

                // remove clerk
                else if (option2 == '7')
                {
                    manager.removeClerk();
                    stopTime(2);
                }

                // save working hours
                else if (option == '8')
                {
                    manager.setWorkingHours();
                    stopTime(2);
                }

                //break
                else if(option2 == '9')
                {
                    system("clear");
                    break;
                }

                else
                {
                    continue;
                }
            }
        }

        // Customer
        else if (option == '3')
        {
            Customer nCustomer = getCustomer();
            while (true)
            {
                printCustomerMenu();
                char option3;
                cin >> option3;

                // put money
                if (option3 == '1')
                {
                    long int money;
                    cout << "Enter how much money you want to put  :  ";
                    cin >> money;
                    nCustomer.putMoney(money);
                    cout << "Money saved in the account\n";
                    stopTime(2);
                }

                // take money
                else if (option3 == '2')
                {
                    long int money;
                    cout << "Enter how much money you want to take  :  ";
                    cin >> money;
                    nCustomer.takemoney(money);
                    cout << "Money taked out from the account\n";
                    stopTime(2);
                }

                // show customer info
                else if (option3 == '3')
                {
                    nCustomer.showAllInformation();
                    cout << "\n\nEnter a char to exit :  ";
                    cin >> temp;
                }

                // exit 
                else if (option3 == '4')
                {
                    system("clear");
                    break;
                }

                else
                {
                    continue;
                }
            }
        }

        // Exit
        else if (option == '4')
        {
            cout << "\nBye Bye :)\n";
            stopTime(2);
            break;
        }

        else
        {
            continue;
        }
    }
}
