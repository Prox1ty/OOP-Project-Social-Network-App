#pragma once
#include <iostream>
#include <cstdio>
#include "stringFunctions.h"
using namespace std;
class Date {
    int day;
    int month;
    int year;

    mutable char dateBuffer[20];
public:
    Date() {
        day = 1;
        month = 1;
        year = 2017;
        dateBuffer[0] = '\0'; // to get rid of stupid error
    }

    Date(int d, int m, int y) {
        if (m > 12) {
            month = (m % 12 == 0)? m: m % 12; // will reset to 1 if greater than 12
        }
        else if (m <= 0) {
            m = abs(m);
            month = (m % 12 == 0) ? m : m % 12;
        }
        else {
            month = m;
        }

        if (y < 2016) {
            year = 2016;
        }
        else if (y > 2026) {
            year = 2026;
        }
        else {
            year = y;
        }

        if (m == 2 && (y % 4 != 0) && d >= 28) {
            day = (d % 28 == 0 ? d : d % 28);
        }
        else {
            day = d;
        }

        dateBuffer[0] = '\0';
     }

    Date& operator=(const Date& other) {
        day = other.day;
        month = other.month;
        year = other.year;

        return *this;
    }

    Date(const Date& other) {
        day = other.day;
        month = other.month;
        year = other.year;

        dateBuffer[0] = '\0';
    }

    friend std::ostream& operator <<(std::ostream& out, const Date& obj) {
        out << obj.day << '/' << obj.month << '/' << obj.year << endl;
        return out;
    }
    // Imporatnt for the 24 hour requirement
    bool IsRecent(const Date& currDate) const {
        if (this->day == currDate.day || this->day == currDate.day - 1) return true;
        return false;
    }

    const char* getDateStr() const {
        // Format: (DD/MM/YYYY) with leading zeros
        sprintf_s(dateBuffer, sizeof(dateBuffer), "(%02d/%02d/%04d)", day, month, year);
        return dateBuffer;
    }

    int getYear() const {
        return year;
    }

    int getMonth() const {
        return month;
    }

    int getDay() const {
        return day;
    }

    ~Date() {}
    
};