#include "Util.hpp"

double calcDistance(const std::pair<double, double>& locA, const std::pair<double, double>& locB) {
	double lonDiff = locA.first - locB.first;
	double latDiff = locA.second - locB.second;
	return std::sqrt(lonDiff * lonDiff + latDiff * latDiff);
}

void calcSocialDistance(std::vector<Animal>& animals) {
	double sumX = 0.0;
	double sumY = 0.0;

	for (uint16_t i = 0; i < animals.size(); i++) {
		double sum = 0.0;
			
		for (uint16_t j = 0; j < animals.size(); j++) {
			if (i != j) {
				sum += calcDistance(animals[i].m_location, animals[j].m_location);
			}
		}

		animals[i].m_socialDistance = sum / (animals.size() - 1);
	}
}