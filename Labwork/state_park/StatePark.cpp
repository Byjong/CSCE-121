// Class file for StatePark class

#include "Passport.h"

using std::string, std::vector;

// Mandatory
// Constructor for StatePark class
StatePark::StatePark(string parkName, double entranceFee, double trailMiles)
	:parkName(parkName)
	,entranceFee(entranceFee)
	,trailMiles(trailMiles)
	,camperLog(vector<Passport*>())
{
}

// Mandatory
// Getter for data member parkName
string StatePark::getParkName() {
	return parkName;
}

// Mandatory
// Getter for data member entranceFee
double StatePark::getEntranceFee() {
	return entranceFee;
}

// Mandatory
// Getter for data member trailMiles
double StatePark::getTrailMiles() {
	return trailMiles;
}

// Mandatory
// Adds a camper (represented by Passport object) to data member camperLog
void StatePark::addCamper(Passport* camper) {
	INFO(camper)
	camperLog.push_back(camper);
}

// Option A
// Calculates the park revenue based on the campers in camperLog
double StatePark::getRevenue() {
	// TODO(student): implement function
	return 0.0;
}