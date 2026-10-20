#ifndef PROJECT_H
#define PROJECT_H

const int MAX_CITIES = 12;

struct TspData {
    int matrix[MAX_CITIES][MAX_CITIES];
    int cityCount;
};

#endif // PROJECT_H
