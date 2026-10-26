#pragma once
#include <iostream>
#include <string>

class Date {
private:
    int day;
    int month;
    int year;

    
    bool isValidDate(int d, int m, int y) const;
    int daysInMonth(int m, int y) const;

public:
    // 1) Конструкторы: по умолчанию и с аргументами (совмещены через значения по умолчанию)
    Date(int d = 1, int m = 1, int y = 2000);

    // 4) Аксессоры (геттеры и сеттеры) для всех полей класса
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    void setDate(int d, int m, int y);

    
    void print() const;
    void read();
};

std::string getSeason() const;

bool isLeapYear() const;

int daysFromStartOfYear() const;

bool isHoliday() const;

bool operator==(const Date& other) const;

int daysUntilNewYear() const;

int operator-(const Date& other) const;

std::string compareWithCurrent(int curD, int curM, int curY) const;

bool isWithinRange(const Date& start, const Date& end) const;
};

