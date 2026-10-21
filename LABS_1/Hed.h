#ifndef HED_H
#define HED_H

// Максимальное количество городов в эксперименте
const int MAX_CITIES = 10;


struct TspSolver {
    int costMatrix[MAX_CITIES][MAX_CITIES];
    int currentPath[MAX_CITIES];
    int bestPath[MAX_CITIES];
    int worstPath[MAX_CITIES];
    int heuristicPath[MAX_CITIES];
    bool visited[MAX_CITIES];
    int cityCount;
    int startCity;
    long long bestCost;
    long long worstCost;
    long long heuristicCost;
    long long routesChecked;
};

// Функция инициализации начальных параметров структуры
void initSolver(TspSolver& solver);


bool generateRandomMatrix(TspSolver& solver, int cityCount, int minCost, int maxCost);

