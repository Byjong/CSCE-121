/*
 * TemperatureData.h
 *
 *  Created on: Jul 16, 2018
 *      Author: student
 */

#ifndef TEMPERATUREDATA
#define TEMPERATUREDATA

#include <string>

using std::string;

struct TemperatureData {
	string id;
	int year;
	int month;
	double temperature;
	TemperatureData();
	TemperatureData(string id, int year, int month, double temperature);
	virtual ~TemperatureData();
	bool operator<(const TemperatureData& b);
};

#endif /* TEMPERATUREDATA */
