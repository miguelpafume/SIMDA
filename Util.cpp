#include "Util.hpp"

std::vector<char> readFile(const std::string& filename) {
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("FAILED TO OPEN FILE: " + filename);
	}

	size_t fileSize = static_cast<size_t>(file.tellg());
	std::vector<char> content(fileSize);

	file.seekg(0);
	file.read(content.data(), fileSize);

	file.close();

	return content;
}

// Calculate distance between two points
double calcDistance(const std::pair<double, double>& locA, const std::pair<double, double>& locB) {
	double lonDiff = locA.first - locB.first;
	double latDiff = locA.second - locB.second;
	return std::sqrt(lonDiff * lonDiff + latDiff * latDiff);
}

template <typename T>
int16_t calcDeviationScore(T value, double average, double sigma, uint16_t weight, bool includeLower) {

	if (!includeLower && value < average) {
		return static_cast<int16_t>(-weight);
	}

	if (sigma == 0.0) return 0; // Prevent division by zero
	
	double deviation = std::abs(value - average);

	// If within standard deviation, return negative weight (healthy)
	if (deviation <= sigma) {
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

int randomNumberInterval(int minA, int maxA, int minB, int maxB) {
	if (randomNumber(0, 1) == 0) {
		return randomNumber(minA, maxA);
	} else {
		return randomNumber(minB, maxB);
	}
}

double randomNumberInterval(double minA, double maxA, double minB, double maxB) {
	if (randomNumber(0, 1) == 0) {
		return randomNumber(minA, maxA);
	} else {
		return randomNumber(minB, maxB);
	}
}

// Calculate average
template <typename T>
double averageFromVector(const std::vector<T>& vec) {
	double sum = 0.0;

	for (const T& val : vec) {
		sum += val;
	}

	return sum / vec.size();
}

// Calculate standard deviation
template <typename T>
double deviationFromVector(const std::vector<T>& vec) {
	double avg = averageFromVector(vec);

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

template double averageFromVector(const std::vector<double>& vec);
template double deviationFromVector(const std::vector<double>& vec, const double& average);
template int16_t calcDeviationScore(double value, double average, double sigma, uint16_t weight, bool includeLower);

template double averageFromVector(const std::vector<uint16_t>& vec);
template double deviationFromVector(const std::vector<uint16_t>& vec, const double& average);
template int16_t calcDeviationScore(uint16_t value, double average, double sigma, uint16_t weight, bool includeLower);

template double averageFromVector(const std::vector<int>& vec);