//
// Created by Rohan Sacheti on 10/21/20.
//

#ifndef PROJECT1_IMPLIEDVOL_H
#define PROJECT1_IMPLIEDVOL_H

#include <string>
using namespace std;


class ImpliedVol {
private:

public:
    double implied_vol(double y_target,  // Target y value
                       double m,         // Left interval value
                       double n,         // Right interval value
                       double epsilon,   // Tolerance
                       double K, //strike price
                       double T, //expiration time
                       double s, //stock price
                       double r);
};


#endif //PROJECT1_IMPLIEDVOL_H
