#pragma once
#include <iostream>
#include <string>

class Date {
private:
    int day;
    int month;
    int year;

    // Вспомогательные приватные методы для внутренней логики
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

    // 2) Ввод/вывод даты
    void print() const;
    void read();
};
