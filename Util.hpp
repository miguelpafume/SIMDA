#pragma once

#include <cmath>
#include <vector>
#include <utility>
#include <iostream>
#include <random>
#include <fstream>

std::vector<char> readFile(const std::string& filename);

// Calculate distance between two points
double calcDistance(const std::pair<double, double>& locA, const std::pair<double, double>& locB);

template <typename T>
int16_t calcDeviationScore(T value, double average, double sigma, uint16_t weight, bool includeLower = true);

// Random number generators
int randomNumber(int min, int max);
double randomNumber(double min, double max);
int randomNumberInterval(int minA, int maxA, int minB, int maxB);
double randomNumberInterval(double minA, double maxA, double minB, double maxB);

template <typename T>
double averageFromVector(const std::vector<T>& vec);

template <typename T>
double deviationFromVector(const std::vector<T>& vec);
template <typename T>
double deviationFromVector(const std::vector<T>& vec, const double& average);