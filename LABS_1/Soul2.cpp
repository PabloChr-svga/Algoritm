#include <iostream>
#include <clocale>
#include <ctime>
#include "Hed.h"

using namespace std;

// Вывод маршрута на экран с замыканием в стартовом городе
void printRoute(const TspSolver& solver, int routeType) {
    int cityCount = solver.cityCount;
    for (int i = 0; i < cityCount; i++) {
        int city = -1;
        if (routeType == 1) city = getBestPathCity(solver, i);
        else if (routeType == 2) city = getWorstPathCity(solver, i);
        else city = getHeuristicPathCity(solver, i);
        cout << city << " ";
    }
    int startCity = 0;
    if (routeType == 1) startCity = getBestPathCity(solver, 0);
    else if (routeType == 2) startCity = getWorstPathCity(solver, 0);
    else startCity = getHeuristicPathCity(solver, 0);
    cout << startCity;
}

void runExperiment(int cityCount, int experimentNumber) {
    TspSolver solver;
    initSolver(solver);

    const int startCity = 0;
    const int minCost = 1;
    const int maxCost = 50;

    cout << "\n----------------------------------------\n";
    cout << "Размер матрицы: " << cityCount << " x " << cityCount << "\n";
    cout << "Эксперимент №: " << experimentNumber << "\n";
    cout << "Диапазон стоимостей: " << minCost << "-" << maxCost << "\n";

    if (!generateRandomMatrix(solver, cityCount, minCost, maxCost)) {
        cout << "Ошибка создания матрицы.\n";
        return;
    }

    // Измерение процессорного времени для точного решения
    std::clock_t exactStart = std::clock();
    bool exactResult = solveExact(solver, startCity);
    std::clock_t exactEnd = std::clock();

    if (!exactResult) {
        cout << "Ошибка точного решения.\n";
        return;
    }
    double exactTime = 1000.0 * (exactEnd - exactStart) / CLOCKS_PER_SEC;

    // Измерение процессорного времени для эвристики
    std::clock_t heuristicStart = std::clock();
    bool heuristicResult = solveNearestNeighbor(solver, startCity);
    std::clock_t heuristicEnd = std::clock();

    if (!heuristicResult) {
        cout << "Ошибка эвристического решения.\n";
        return;
    }
    double heuristicTime = 1000.0 * (heuristicEnd - heuristicStart) / CLOCKS_PER_SEC;

    // Вычисление относительного качества решения
    double quality = (solver.worstCost == solver.bestCost) ? 100.0 :
        100.0 * (solver.worstCost - solver.heuristicCost) / (solver.worstCost - solver.bestCost);

    // Установка фиксированного формата без iomanip
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(3);

    cout << "\nТочное решение:\nЛучший маршрут: ";
    printRoute(solver, 1);
    cout << "\nСтоимость: " << solver.bestCost << "\nХудший маршрут: ";
    printRoute(solver, 2);
    cout << "\nСтоимость: " << solver.worstCost << "\nПроверено маршрутов: " << solver.routesChecked;
    cout << "\nВремя точного алгоритма: " << exactTime << " мс\n";

    cout << "\nЭвристическое решение:\nМаршрут: ";
    printRoute(solver, 3);
    cout << "\nСтоимость: " << solver.heuristicCost << "\nВремя эвристики: " << heuristicTime << " мс\n";
    cout << "Качество решения: " << quality << "%\n";
}

int main() {
    setlocale(LC_ALL, ".UTF-8");

    const int cityCounts[] = { 4, 6, 8, 10 }; // Четыре размерности матриц
    const int numberOfSizes = 4;
    const int experimentsPerSize = 4;        // Количество запусков на размерность

    cout << "==================================================\n";
    cout << " СРАВНЕНИЕ ТОЧНОГО И ЭВРИСТИЧЕСКОГО МЕТОДОВ\n";
    cout << "==================================================\n";

    for (int i = 0; i < numberOfSizes; i++) {
        for (int experiment = 1; experiment <= experimentsPerSize; experiment++) {
            runExperiment(cityCounts[i], experiment);
        }
    }

    return 0;
}
