#include "TemperatureDatabase.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

// Default constructor/destructor. Modify them if you need to.
TemperatureDatabase::TemperatureDatabase() : records(LinkedList()) {}
TemperatureDatabase::~TemperatureDatabase() {}

void TemperatureDatabase::loadData(const string& filename) {

	ifstream fin(filename);
	istringstream sin;

	if (!fin.is_open()) {
		cout << "Error: Unable to open " << filename << "\n";
	}


	string id = string();
	string line = string();
	int year = 0;
	int month = 0;
	double temperature = 0.0;


	while (!fin.eof()) {
		line = string();
		getline(fin, line);
		sin.clear();
		sin.str(line);

		if(fin.eof() && line.empty()){
			break;
		}

		sin >> id;
		if (sin.fail()) {
			cout << "Error: Other invalid input" << endl;
			continue;
		}

		sin >> year;
		if (sin.fail()) {
			cout << "Error: Other invalid input" << endl;
			continue;
		}

		if (year < 1800 || year > 2022) {
			cout << "Error: Invalid year " << year << endl;
			continue;
		}

		sin >> month;
		if (sin.fail()) {
			cout << "Error: Other invalid input" << endl;
			continue;
		}

		if (month < 1 || month > 12) {
			cout << "Error: Invalid month " << month << endl;
		}

		sin >> temperature;
		if (sin.fail()) {
			cout << "Error: Other invalid input" << endl;
			continue;
		}
		if ((temperature < -50.0 && temperature != -99.99) || temperature > 50.0) {
			cout << "Error: Invalid temperature " << temperature << endl;
		}

		this->records.insert(id, year, month, temperature);
	}
}

// Do not modify
void TemperatureDatabase::outputData(const string& filename) {
	ofstream dataout("sorted." + filename);

	if (!dataout.is_open()) {
		cout << "Error: Unable to open " << filename << endl;
		exit(1);
	}
	dataout << records.print();
}

void TemperatureDatabase::performQuery(const string& filename) {
	// Implement this function for part 2
	//  Leave it blank for part 1
	cout << filename << "\n";
}
