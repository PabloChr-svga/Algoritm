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

 
void runExperiment(int cityCount, int experimentNumber, int minCost, int maxCost) {
    TspSolver solver;
    initSolver(solver);

    const int startCity = 0;

    cout << "\n----------------------------------------\n";
    cout << "Размер матрицы: " << cityCount << " x " << cityCount << "\n";
    cout << "Эксперимент №: " << experimentNumber << "\n";
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

    
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int minCost = 1;
    int maxCost = 50;
    int userCityCount = 4;

    cout << "=== Настройка параметров эксперимента ===\n";

  
    while (true) {
        cout << "Введите минимальную стоимость (>= 1): ";
        cin >> minCost;
        cout << "Введите максимальную стоимость (до 80): ";
        cin >> maxCost;

        if (minCost >= 1 && maxCost <= 80 && maxCost >= minCost) {
            break;
        }
        cout << "Ошибка! Нарушены условия: 1 <= мин <= макс <= 80. Попробуйте снова.\n\n";
    }
 
    while (true) {
        cout << "Введите количество городов для исследования (от 2 до 12): ";
        cin >> userCityCount;

        if (userCityCount >= 2 && userCityCount <= 12) {
            break;
        }
        cout << "Ошибка! Количество городов должно быть строго в диапазоне от 2 до 12. Попробуйте снова.\n\n";
    }
 
    const int experimentsCount = 4;
    for (int experiment = 1; experiment <= experimentsCount; experiment++) {
        runExperiment(userCityCount, experiment, minCost, maxCost);
    }

    return 0;
}
