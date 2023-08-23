#ifndef RENTAL_COMPANY_H
#define RENTAL_COMPANY_H

#include <string>
#include <vector>
using std::string, std::vector;

class RentalCompany{
    string name;
    vector<Car> fleet;
    
public:
    RentalCompany(string name);
    string getName();
    void addCar(Car newCar);
};

#endif