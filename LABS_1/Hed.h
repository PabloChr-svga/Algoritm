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

// Функция генерации случайных стоимостей дорог
bool generateRandomMatrix(TspSolver& solver, int cityCount, int minCost, int maxCost);

// Функции точного решения (Полный перебор)
bool solveExact(TspSolver& solver, int startCity);
void searchRoutes(TspSolver& solver, int currentCity, int depth, long long currentCost);

// Функция приближенного жадного решения
bool solveNearestNeighbor(TspSolver& solver, int startCity);

// Прототипы функций безопасного чтения элементов пути
int getBestPathCity(const TspSolver& solver, int index);
int getWorstPathCity(const TspSolver& solver, int index);
int getHeuristicPathCity(const TspSolver& solver, int index);

#endif // HED_H
