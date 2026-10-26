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


bool Date::operator==(const Date& other) const {
    return (day == other.day && month == other.month && year == other.year);
}

// 9) Сколько дней осталось до нового года
int Date::daysUntilNewYear() const {
    int totalInYear = isLeapYear() ? 366 : 365;
    return totalInYear - daysFromStartOfYear();
}


int calculateAbsoluteDays(const Date& d) {
    int absDays = d.getDay();
    for (int y = 1; y < d.getYear(); ++y) {
        absDays += ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) ? 366 : 365;
    }
    for (int m = 1; m < d.getMonth(); ++m) {
        if (m == 2) absDays += ((d.getYear() % 4 == 0 && d.getYear() % 100 != 0) || (d.getYear() % 400 == 0)) ? 29 : 28;
        else if (m == 4 || m == 6 || m == 9 || m == 11) absDays += 30;
        else absDays += 31;
    }
    return absDays;
}

// 10) Количество дней между двумя датами (перегрузка оператора -)
int Date::operator-(const Date& other) const {
    return calculateAbsoluteDays(*this) - calculateAbsoluteDays(other);
}

// 11) Сравнение с текущей датой (её параметры передаются в метод)
std::string Date::compareWithCurrent(int curD, int curM, int curY) const {
    Date current(curD, curM, curY);
    int diff = calculateAbsoluteDays(*this) - calculateAbsoluteDays(current);
    if (diff < 0) return "Прошлое";
    if (diff > 0) return "Будущее";
    return "Текущий день";
}


bool Date::isWithinRange(const Date& start, const Date& end) const {
    int currentAbs = calculateAbsoluteDays(*this);
    int startAbs = calculateAbsoluteDays(start);
    int endAbs = calculateAbsoluteDays(end);
    return (currentAbs >= startAbs && currentAbs <= endAbs);
}

