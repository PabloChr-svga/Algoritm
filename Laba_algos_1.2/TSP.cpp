#include "TSP.h"
#include <cstdlib>
#include <climits>
#include <ctime>

TspSolver::TspSolver()
    : cityCount_(0),
    startCity_(0),
    bestCost_(LLONG_MAX),
    worstCost_(LLONG_MIN),
    heuristicCost_(0),
    routesChecked_(0) {

    for (int i = 0; i < MAX_CITIES; i++) {
        visited_[i] = false;
        currentPath_[i] = -1;
        bestPath_[i] = -1;
        worstPath_[i] = -1;
        heuristicPath_[i] = -1;

        for (int j = 0; j < MAX_CITIES; j++) {
            costMatrix_[i][j] = 0;
        }
    }
}

bool TspSolver::generateRandomMatrix(int cityCount, int minCost, int maxCost) {
    if (cityCount < 2 || cityCount > MAX_CITIES || minCost < 1 || maxCost < minCost) {
        return false;
    }

    cityCount_ = cityCount;

    for (int i = 0; i < cityCount_; i++) {
        for (int j = 0; j < cityCount_; j++) {
            if (i == j) {
                costMatrix_[i][j] = 0;
            }
            else {
                costMatrix_[i][j] = minCost + rand() % (maxCost - minCost + 1);
            }
        }
    }
    return true;
}

bool TspSolver::solveExact(int startCity) {
    if (cityCount_ < 2 || startCity < 0 || startCity >= cityCount_) {
        return false;
    }

    startCity_ = startCity;
    bestCost_ = LLONG_MAX;
    worstCost_ = LLONG_MIN;
    routesChecked_ = 0;

    for (int i = 0; i < cityCount_; i++) {
        visited_[i] = false;
        currentPath_[i] = -1;
        bestPath_[i] = -1;
        worstPath_[i] = -1;
    }

    visited_[startCity_] = true;
    currentPath_[0] = startCity_;

    searchRoutes(startCity_, 1, 0);

    return routesChecked_ > 0;
}

void TspSolver::searchRoutes(int currentCity, int depth, long long currentCost) {
    if (depth == cityCount_) {
        long long totalCost = currentCost + costMatrix_[currentCity][startCity_];
        routesChecked_++;

        if (totalCost < bestCost_) {
            bestCost_ = totalCost;
            for (int i = 0; i < cityCount_; i++) {
                bestPath_[i] = currentPath_[i];
            }
        }

        if (totalCost > worstCost_) {
            worstCost_ = totalCost;
            for (int i = 0; i < cityCount_; i++) {
                worstPath_[i] = currentPath_[i];
            }
        }
        return;
    }

    for (int nextCity = 0; nextCity < cityCount_; nextCity++) {
        if (!visited_[nextCity]) {
            visited_[nextCity] = true;
            currentPath_[depth] = nextCity;

            searchRoutes(nextCity, depth + 1, currentCost + costMatrix_[currentCity][nextCity]);

            visited_[nextCity] = false;
        }
    }
}

bool TspSolver::solveNearestNeighbor(int startCity) {
    if (cityCount_ < 2 || startCity < 0 || startCity >= cityCount_) {
        return false;
    }

    startCity_ = startCity;

    for (int i = 0; i < cityCount_; i++) {
        visited_[i] = false;
        heuristicPath_[i] = -1;
    }

    int currentCity = startCity_;
    long long totalCost = 0;

    heuristicPath_[0] = startCity_;
    visited_[startCity_] = true;

    for (int step = 1; step < cityCount_; step++) {
        int nearestCity = -1;
        int nearestCost = INT_MAX;

        for (int city = 0; city < cityCount_; city++) {
            if (!visited_[city] && costMatrix_[currentCity][city] < nearestCost) {
                nearestCost = costMatrix_[currentCity][city];
                nearestCity = city;
            }
        }

        if (nearestCity == -1) {
            return false;
        }

        totalCost += nearestCost;
        currentCity = nearestCity; // Исправлена опечатка (был пробел в имени переменной)

        heuristicPath_[step] = currentCity;
        visited_[currentCity] = true;
    }

    totalCost += costMatrix_[currentCity][startCity_];
    heuristicCost_ = totalCost;

    return true;
}

int TspSolver::getCityCount() const { return cityCount_; }
long long TspSolver::getBestCost() const { return bestCost_; }
long long TspSolver::getWorstCost() const { return worstCost_; }
long long TspSolver::getHeuristicCost() const { return heuristicCost_; }
long long TspSolver::getRoutesChecked() const { return routesChecked_; }

int TspSolver::getBestPathCity(int index) const {
    if (index < 0 || index >= cityCount_) return -1;
    return bestPath_[index];
}

int TspSolver::getWorstPathCity(int index) const {
    if (index < 0 || index >= cityCount_) return -1;
    return worstPath_[index];
}

int TspSolver::getHeuristicPathCity(int index) const {
    if (index < 0 || index >= cityCount_) return -1;
    return heuristicPath_[index];
}
