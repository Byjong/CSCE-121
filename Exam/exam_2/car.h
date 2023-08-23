#ifndef CAR_H
#define CAR_H

#include <string>
#include <vector>
using std::string, std::vector;

class Car{
    string model;
    double range;
    bool isElectric;

public:
    Car(string model, double range, bool isElectric);
    string getModel();
    double getRange();
    bool getIsElectric();
};

#endif