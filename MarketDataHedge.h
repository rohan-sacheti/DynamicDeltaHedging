//
// Created by Rohan Sacheti on 10/21/20.
//

#ifndef PROJECT1_MARKETDATAHEDGE_H
#define PROJECT1_MARKETDATAHEDGE_H

#include <string>
using namespace std;
#include <iostream>
#include "vector"
#include <random>

#include <fstream>
#include <string>
#include <sstream>

class MarketDataHedge {
private:
    string t0;
    string tn;
    string T;
    double K;

public:
    MarketDataHedge(string t0, string tn, string T, double K);
    void getResults();
    double getOptionData();
    int dateDiff(string date1, string date2);
};


#endif //PROJECT1_MARKETDATAHEDGE_H
