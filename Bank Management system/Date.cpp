#include "Classes.h"
#include <iostream>

using namespace std;

// constructor to get the right date
Date::Date(): day(1), month(1), year(1) {}

// show the date method
void Date::showDate()
{
    // outputing in the right format
    // cout year first
    if (year/10 == 0)
        cout << "000" << year;
    else if (year/100 == 0)
        cout << "00"  << year;
    else if (year/100 == 0)
        cout << "0"   << year;
    else
        cout << year;

    // right input for month
    if (month/10 == 0)
        cout << " / 0" << month;
    else
        cout << " / "  << month;

    // right input for day
    if (day/10 == 0)
        cout << " / 0" << day;
    else
        cout << " / "  << day;
}

void Date::setDate(int _day, int _month, int _year)
{
    bool isValidDate {true};

    // deciding if it is a leap year
    bool isLeapYear = (_year % 4 == 0 && (_year % 100 != 0 || _year % 400 == 0));

    // wrong dates
    if (_day > 31 || _day <= 0 || _month > 12 || _month <= 0)
        isValidDate = false;
    else if (isLeapYear && _month == 12 && _day > 30)
        isValidDate = false;
    else if (_month >= 7 && _month <= 12 && _day > 30)
        isValidDate = false;

    if (isValidDate)
    {
        day = _day;
        month = _month;
        year = _year;
    }

    // setting default values for wrong input date
    else
    {
        day = 1;
        month = 1;
        year = 1;
    }

}





