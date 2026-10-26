#include "Date.h"

// Внутренняя проверка валидности даты
bool Date::isValidDate(int d, int m, int y) const {
    if (y < 1 || m < 1 || m > 12 || d < 1) return false;
    return d <= daysInMonth(m, y);
}

// Внутренний подсчет дней в конкретном месяце
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

// 4) Аксессор-сеттер (тоже проверяет корректность перед изменением)
void Date::setDate(int d, int m, int y) {
    if (isValidDate(d, m, y)) {
        day = d; month = m; year = y;
    }
    else {
        std::cout << "Ошибка: Попытка записать некорректную дату. Поля не изменены!\n";
    }
}

// 2) Вывод даты на экран
void Date::print() const {
    if (day < 10) std::cout << "0";
    std::cout << day << ".";
    if (month < 10) std::cout << "0";
    std::cout << month << "." << year << "\n";
}

// 2) Ввод даты с проверкой
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
