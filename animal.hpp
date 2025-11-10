#pragma once

#include "Util.hpp"

#include <string>
#include <random>
#include <utility>
#include <iostream>

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
	uint16_t m_heartRate					= 0;			// BPM (beats per minute)
	double m_size							= 0;			// Length (meters)

	int16_t m_score							= 0;			// Anomaly score
	Risk m_risk								= NORMAL;		// Risk level

	uint16_t m_lastIteration				= 0; 			// Number of iterations the animal has skipped

	void resetIdCounter() { s_nextId = 1; };

	void generatePosition(double minX, double maxX, double minY, double maxY); // Generates a random position without collision
	void generateUniquePosition(double minX, double maxX, double minY, double maxY, const std::vector<Animal>& animals);

	void update();
};