//
// Created by Rohan Sacheti on 10/20/20.
//

#ifndef PROJECT1_STDNORMAL_H
#define PROJECT1_STDNORMAL_H
#include "math.h"

class StdNormalCDF {
private:
    double const a1 = 0.31938153;
    double const a2 = -0.356563782;
    double const a3 = 1.781477937;
    double const a4 = -1.821255978;
    double const a5 = 1.330274429;

public :
    StdNormalCDF(){}
    ~StdNormalCDF(){}
    double norm_distribution(double x);
};



#endif //PROJECT1_STDNORMAL_H
