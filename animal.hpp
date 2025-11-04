#pragma once

#include <string>
#include <random>
#include <utility>

enum Risk {
	NORMAL,
	LOW,
	MEDIUM,
	HIGH,
	RANDOM
};

class Animal {
private:
	static uint16_t s_nextId;
	uint16_t m_id							= 0;			// Unique identifier (1 - 65535)

public:
	Animal(Risk risk);
	Animal() : Animal(RANDOM) {};
	~Animal() = default;

	uint16_t getId() const { return m_id; };

	std::string m_name						= "";			// OPTIONAL | Name of the animal
	uint16_t m_activity						= 0;			// Activity level (0% - 100%)
	uint16_t m_age							= 0;			// Age (days)
	double m_temperature					= 0;			// Body temperature (celsius)
	std::pair<double, double> m_location	= { 0.0, 0.0 };	// Mapping (latitude, longitude)
	double m_socialDistance					= 0;			// Average distance from other animals (meters)
	Risk m_risk								= NORMAL;		// Risk level

	int16_t m_score							= 0;			// Anomaly score

	void detectAnomaly();
};