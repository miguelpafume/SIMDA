#include <string>
#include <utility>
#include <random>

enum Risk {
	NORMAL,
	LOW,
	MEDIUM,
	HIGH
};

class Animal {
private:

public:
	Animal(Risk risk);
	Animal() : Animal(NORMAL) {};
	~Animal() = default;

	std::string m_name						= "";			// OPTIONAL | Name of the animal
	uint16_t m_id							= 1;			// Unique identifier (1 - 65535)
	uint16_t m_activity						= 0;			// Activity level (0% - 100%)
	uint16_t m_age							= 0;			// Age (months)
	double m_temperature					= 0;			// Body temperature (celsius)
	std::pair<double, double> m_location	= { 0.0, 0.0 };	// Mapping (latitude, longitude)
	double m_socialDistance					= 0;			// Average distance from other animals (meters)
	Risk m_risk								= NORMAL;		// Risk level

	void detectAnomaly();
};