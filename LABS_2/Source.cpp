#include <iostream>
#include <iomanip>
#include <chrono>
#include <clocale>
#include "object.h"

using namespace std;
using namespace std::chrono;

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
    const int maxCost = 50; // Диапазон стоимостей из задания

    cout << "\n----------------------------------------\n";
    cout << "Размер матрицы: " << cityCount << " x " << cityCount << "\n";
    cout << "Эксперимент №: " << experimentNumber << "\n";
    cout << "Диапазон стоимостей: " << minCost << "-" << maxCost << "\n";

    if (!generateRandomMatrix(solver, cityCount, minCost, maxCost)) {
        cout << "Ошибка создания матрицы.\n";
        return;
    }
