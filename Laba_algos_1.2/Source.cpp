#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <clocale>

#include "TSP.h"

using namespace std;

// Печать пути через геттеры класса
void printRoute(const TspSolver& solver, int routeType) {
    int cityCount = solver.getCityCount();
    for (int i = 0; i < cityCount; i++) {
        if (routeType == 1) cout << solver.getBestPathCity(i) << " ";
        else cout << solver.getHeuristicPathCity(i) << " ";
    }
    if (routeType == 1) cout << solver.getBestPathCity(0);
    else cout << solver.getHeuristicPathCity(0);
}

void runExperiment(int cityCount, int experimentNumber) {
    TspSolver solver; // Создаем объект класса

    if (!solver.generateRandomMatrix(cityCount, 1, 50)) {
        cout << "Ошибка создания матрицы.\n";
        return;
    }

    // Точный метод + замер времени
    clock_t start = clock();
    bool exactResult = solver.solveExact(0);
    clock_t end = clock();
    double exactTime = static_cast<double>(end - start) * 1000.0 / CLOCKS_PER_SEC;

    // Эвристика + замер времени
    start = clock();
    bool heuristicResult = solver.solveNearestNeighbor(0);
    end = clock();
    double heuristicTime = static_cast<double>(end - start) * 1000.0 / CLOCKS_PER_SEC;

    if (!exactResult || !heuristicResult) {
        cout << "Ошибка выполнения алгоритмов.\n";
        return;
    }

    long long best = solver.getBestCost();
    long long worst = solver.getWorstCost();
    long long heur = solver.getHeuristicCost();

    // Расчет точности по формуле из лекции
    double quality = (worst == best) ? 100.0 : 100.0 * (worst - heur) / (worst - best);

    // Студенческий компактный вывод через printf
    printf("\n--- Тест N%d (Городов: %d) ---\n", experimentNumber, cityCount);

    printf("Точный метод: Cost = %lld | %.2f ms | Путь: ", best, exactTime);
    printRoute(solver, 1);
    cout << "\n";

    printf("Эвристика:    Cost = %lld | %.2f ms | Путь: ", heur, heuristicTime);
    printRoute(solver, 3);

    printf("\nТочность эвристики: %.2f%%\n", quality);
}

int main() {
    setlocale(LC_ALL, ".UTF-8");
    srand(static_cast<unsigned int>(time(nullptr)));

    const int cityCounts[] = { 4, 6, 8, 10 }; // MAX_CITIES в классе равен 10, поэтому максимум 10
    const int numberOfSizes = 4;
    const int experimentsPerSize = 3;

    cout << "=== СРАВНЕНИЕ АЛГОРИТМОВ ТСП ===\n";

    for (int i = 0; i < numberOfSizes; i++) {
        for (int exp = 1; exp <= experimentsPerSize; exp++) {
            runExperiment(cityCounts[i], exp);
        }
    }

    cout << "\nВсе эксперименты успешно завершены.\n";
    return 0;
}
