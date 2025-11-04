#pragma once

#include "animal.hpp"

#include <cmath>
#include <vector>
#include <utility>
#include <iostream>

// Point distance math
double calcDistance(const std::pair<double, double>& locA, const std::pair<double, double>& locB);

void calcSocialDistance(std::vector<Animal>& animals);