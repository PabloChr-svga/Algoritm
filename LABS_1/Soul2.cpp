#include <iostream>
#include <clocale>
#include <ctime>
#include "Hed.h"

using namespace std;

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
    cout << "Эксперимент: " << experimentNumber << "\n";
    cout << "Диапазон стоимостей: " << minCost << "-" << maxCost << "\n";

    if (!generateRandomMatrix(solver, cityCount, minCost, maxCost)) {
        cout << "Ошибка создания матрицы.\n";
        return;
    }

    std::clock_t exactStart = std::clock();
    bool exactResult = solveExact(solver, startCity);
    std::clock_t exactEnd = std::clock();

    if (!exactResult) {
        cout << "Ошибка точного решения.\n";
        return;
    }
    double exactTime = 1000.0 * (exactEnd - exactStart) / CLOCKS_PER_SEC;

    std::clock_t heuristicStart = std::clock();
    bool heuristicResult = solveNearestNeighbor(solver, startCity);
    std::clock_t heuristicEnd = std::clock();

    if (!heuristicResult) {
        cout << "Ошибка эвристического решения.\n";
        return;
    }
    double heuristicTime = 1000.0 * (heuristicEnd - heuristicStart) / CLOCKS_PER_SEC;

    double quality = (solver.worstCost == solver.bestCost) ? 100.0 :
        100.0 * (solver.worstCost - solver.heuristicCost) / (solver.worstCost - solver.bestCost);

    // Установка точности вывода без использования iomanip
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(3);

    cout << "\nТочное решение:\nЛучший маршрут: ";
    printRoute(solver, 1);
    cout << "\nСтоимость: " << solver.bestCost << "\nHудший маршрут: ";
    printRoute(solver, 2);
    cout << "\nСтоимость: " << solver.worstCost << "\nПроверено маршрутов: " << solver.routesChecked;
    cout << "\nВремя точного алгоритма: " << exactTime << " мс\n";

    cout << "\nЭвристическое решение:\nМаршрут: ";
    printRoute(solver, 3);
    cout << "\nСтоимость: " << solver.heuristicCost << "\nВремя эвристики: " << heuristicTime << " мс\n";

    cout.precision(2);
    cout << "Качество решения: " << quality << "%\n";
}
