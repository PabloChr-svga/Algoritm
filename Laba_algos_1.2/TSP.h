#ifndef TSP_H
#define TSP_H

class TspSolver {
public:
    static const int MAX_CITIES = 10;

    TspSolver();

    bool generateRandomMatrix(int cityCount, int minCost, int maxCost);

    bool solveExact(int startCity);
    bool solveNearestNeighbor(int startCity);

    int getCityCount() const;

    long long getBestCost() const;
    long long getWorstCost() const;
    long long getHeuristicCost() const;
    long long getRoutesChecked() const;

    int getBestPathCity(int index) const;
    int getWorstPathCity(int index) const;
    int getHeuristicPathCity(int index) const;

private:
    int costMatrix_[MAX_CITIES][MAX_CITIES];

    int currentPath_[MAX_CITIES];
    int bestPath_[MAX_CITIES];
    int worstPath_[MAX_CITIES];
    int heuristicPath_[MAX_CITIES];

    bool visited_[MAX_CITIES];

    int cityCount_;
    int startCity_;

    long long bestCost_;
    long long worstCost_;
    long long heuristicCost_;
    long long routesChecked_;

    void searchRoutes(int currentCity, int depth, long long currentCost);
};

#endif

