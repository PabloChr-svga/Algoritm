#include "Hed.h"
#include <cstdlib>
#include <climits>

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

bool generateRandomMatrix(TspSolver& solver, int cityCount, int minCost, int maxCost) {
    if (cityCount < 2 || cityCount > MAX_CITIES || minCost < 1 || maxCost < minCost) {
        return false;
    }
    solver.cityCount = cityCount;
    for (int i = 0; i < solver.cityCount; i++) {
        for (int j = 0; j < solver.cityCount; j++) {
            if (i == j) {
                solver.costMatrix[i][j] = 0;
            }
            else {
                solver.costMatrix[i][j] = minCost + std::rand() % (maxCost - minCost + 1);
            }
        }
    }
    return true;
}
