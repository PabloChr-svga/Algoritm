#include "Date.h"


bool Date::isValidDate(int d, int m, int y) const {
    if (y < 1 || m < 1 || m > 12 || d < 1) return false;
    return d <= daysInMonth(m, y);
}


int Date::daysInMonth(int m, int y) const {
    if (m == 2) {
        // Год високосный, если делится на 4 и не на 100, либо делится на 400
        return ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) ? 29 : 28;
    }
    if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
    return 31;
}

// 1) Конструктор. Предусматривает корректность ввода
Date::Date(int d, int m, int y) {
    if (isValidDate(d, m, y)) {
        day = d; month = m; year = y;
    }
    else {
        std::cout << "Предупреждение: Некорректная дата! Выставлено значение по умолчанию: 01.01.2000\n";
        day = 1; month = 1; year = 2000;
    }
}

void Date::setDate(int d, int m, int y) {
    if (isValidDate(d, m, y)) {
        day = d; month = m; year = y;
    }
    else {
        std::cout << "Ошибка: Попытка записать некорректную дату. Поля не изменены!\n";
    }
}


void Date::print() const {
    if (day < 10) std::cout << "0";
    std::cout << day << ".";
    if (month < 10) std::cout << "0";
    std::cout << month << "." << year << "\n";
}


void Date::read() {
    int d, m, y;
    do {
        std::cout << "Введите день, месяц и год через пробел: ";
        std::cin >> d >> m >> y;
        if (!isValidDate(d, m, y)) {
            std::cout << "Ошибка: Такой даты не существует в календаре. Повторите ввод.\n";
        }
    } while (!isValidDate(d, m, y));
    day = d; month = m; year = y;
}

// 3) Определение времени года
std::string Date::getSeason() const {
    if (month == 12 || month == 1 || month == 2) return "Зима";
    if (month >= 3 && month <= 5) return "Весна";
    if (month >= 6 && month <= 8) return "Лето";
    return "Осень";
}

bool Date::isLeapYear() const {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

// 6) Сколько дней прошло от начала года
int Date::daysFromStartOfYear() const {
    int sum = 0;
    for (int m = 1; m < month; ++m) {
        sum += daysInMonth(m, year);
    }
    sum += day;
    return sum;
}

bool Date::isHoliday() const {
    if (month == 1 && (day >= 1 && day <= 8)) return true; 
    if (month == 2 && day == 23) return true;             
    if (month == 3 && day == 8) return true;              
    if (month == 5 && (day == 1 || day == 9)) return true; 
    if (month == 6 && day == 12) return true;             
    if (month == 11 && day == 4) return true;             
    return false;
}
