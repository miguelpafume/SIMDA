#pragma once

#include <cmath>
#include <vector>
#include <utility>
#include <iostream>
#include <random>

// Calculate distance between two points
double calcDistance(const std::pair<double, double>& locA, const std::pair<double, double>& locB);

template <typename T>
int16_t calcDeviationScore(T value, T average, double sigma, uint16_t weight);

// Random number generators
int randomNumber(int min, int max);
double randomNumber(double min, double max);

template <typename T>
double deviationFromVector(const std::vector<T>& vec);
template <typename T>
double deviationFromVector(const std::vector<T>& vec, const double& average);

template <typename T>
double averageFromVector(const std::vector<T>& vec);