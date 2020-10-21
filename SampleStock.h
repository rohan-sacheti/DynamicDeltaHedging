//
// Created by Rohan Sacheti on 10/21/20.
//

#ifndef PROJECT1_SAMPLESTOCK_H
#define PROJECT1_SAMPLESTOCK_H

#include <iostream>
#include "vector"
#include "StdNormalCDF.h"
#include "BlackScholes.h"
#include <random>

using namespace std;
#include <fstream>
#include <string>

class SampleStock {
private:
    double S0 = 100;
    double T = 0.4;
    double mean = 0.05;
    double sigma = 0.24;
    double r = 0.025;
    double N = 100;
    double K = 105;
    double delta_t = T/N;
    double normalRandom();

public:
    void saveSampleStock();
};


#endif //PROJECT1_SAMPLESTOCK_H
