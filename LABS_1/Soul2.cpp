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
