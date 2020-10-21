//
// Created by Rohan Sacheti on 10/20/20.
//

#include "StdNormalCDF.h"

double StdNormalCDF::norm_distribution(double x) {
//   function for approximate normal distribution
    if (x < 0) {
        return 1 - norm_distribution(-x);
    }

    double z = 1 / (1 + 0.2316419*x);
    double R = a1*z + a2*pow(z,2)+
               a3*pow(z,3) + a4*pow(z,4)
               + a5*pow(z,5);

    return 1 - ((1/sqrt(2*M_PI)) * exp(-pow(x,2) * 0.5) * R);
}

