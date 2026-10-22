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