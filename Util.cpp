#include "Util.hpp"

// Calculate distance between two points
double calcDistance(const std::pair<double, double>& locA, const std::pair<double, double>& locB) {
	double lonDiff = locA.first - locB.first;
	double latDiff = locA.second - locB.second;
	return std::sqrt(lonDiff * lonDiff + latDiff * latDiff);
}

template <typename T>
int16_t calcDeviationScore(T value, T average, double sigma, uint16_t weight) {
	T deviation = std::abs(value - average);

	if (sigma == 0.0) return 0; // Prevent division by zero

	// If within standard deviation, return negative weight (healthy)
	if ((double)deviation <= sigma) {
		return static_cast<int16_t>(-weight);
	}

	return static_cast<int16_t>(deviation / sigma * weight);
}

// Random number generators

int randomNumber(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> randomNum(min, max);
	return randomNum(gen);
}

double randomNumber(double min, double max) {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<double> randomNum(min, max);
	return randomNum(gen);
}

template <typename T>
double deviationFromVector(const std::vector<T>& vec) {
	double avg = averageFromInputs(vec);

	double sum = 0.0;

	for (const T& val : vec) {
		sum += std::pow(val - avg, 2);
	}

	return std::sqrt(sum / static_cast<double>(vec.size() - 1));
}

template <typename T>
double deviationFromVector(const std::vector<T>& vec, const double& average) {
	double sum = 0.0;

	for (const T& val : vec) {
		sum += std::pow(val - average, 2);
	}

	return std::sqrt(sum / static_cast<double>(vec.size() - 1));
}

template <typename T>
double averageFromVector(const std::vector<T>& vec) {
	double sum = 0.0;

	for (const T& val : vec) {
		sum += val;
	}

	return sum / static_cast<double>(vec.size());
}