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

    void setMonth(int m) {
        if (m <= 0) m = abs(m);
        if (m > 12) month = (m % 12 == 0) ? 12 : m % 12;
        else if (m == 0) month = 1;
        else month = m;
    }

    void setYear(int y) {
        if (y < 2016) year = 2016;
        else if (y > 2026) year = 2026;
        else year = y;
    }

    void setDay(int d) {
        int maxDay = 31;
        if (month == 2) {
            maxDay = (year % 4 == 0) ? 29 : 28;
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11) {
            maxDay = 30;
        }

        if (d <= 0) {
            day = 1;
        }
        else if (d > maxDay) {
            day = d % maxDay;
            if (day == 0) day = 1;
            setMonth(month + 1);
        }
        else {
            day = d;
        }
    }


public:
    Date() {
        day = 1;
        month = 1;
        year = 2017;
        dateBuffer[0] = '\0'; // to get rid of stupid error
    }

    Date(int d, int m, int y) {
        dateBuffer[0] = '\0';
        setMonth(m);
        setYear(y);
        setDay(d);
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