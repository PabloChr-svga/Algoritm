#include "object.h"
#include <climits>
#include <random>
#include <ctime>

void initSolver(TspSolver& solver) {
    solver.cityCount = 0;
    solver.startCity = 0;
    solver.bestCost = LLONG_MAX;
    solver.worstCost = LLONG_MIN;
    solver.heuristicCost = 0;
    solver.routesChecked = 0;

    for (int i = 0; i < MAX_CITIES; i++) {
        solver.visited[i] = false;
        solver.currentPath[i] = -1;
        solver.bestPath[i] = -1;
        solver.worstPath[i] = -1;
        solver.heuristicPath[i] = -1;

        for (int j = 0; j < MAX_CITIES; j++) {
            solver.costMatrix[i][j] = 0;
        }
    }
}

// Заполнение матрицы случайными стоимостями путей по стандарту C++11
bool generateRandomMatrix(TspSolver& solver, int cityCount, int minCost, int maxCost) {
    if (cityCount < 2 || cityCount > MAX_CITIES || minCost < 1 || maxCost < minCost) {
        return false;
    }

    solver.cityCount = cityCount;

    // Использование современного генератора mt19937 и равномерного распределения
    static std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> distribution(minCost, maxCost);

    for (int i = 0; i < solver.cityCount; i++) {
        for (int j = 0; j < solver.cityCount; j++) {
            if (i == j) {
                solver.costMatrix[i][j] = 0; // Расстояние до самого себя всегда 0
            }
            else {
                solver.costMatrix[i][j] = distribution(generator);
            }
        }
    }
    return true;
}
