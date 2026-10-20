#ifndef PROJECT_H
#define PROJECT_H

// Максимальное количество городов для перебора
const int MAX_CITIES = 12;

struct TspData {
    int matrix[MAX_CITIES][MAX_CITIES]; // Матрица стоимостей (расстояний)
    int cityCount;                      // Текущее количество городов в эксперименте
};