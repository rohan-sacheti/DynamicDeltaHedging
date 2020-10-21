//
// Created by Rohan Sacheti on 10/20/20.
//

#ifndef PROJECT1_BLACKSCHOLES_H
#define PROJECT1_BLACKSCHOLES_H

#include "StdNormalCDF.h"
#define _USE_MATH_DEFINES

class BlackScholes {

private:
    StdNormalCDF normCDF;
    double strike_price_K;
    double current_price_S;
    double risk_free_rate_r;
    double time_to_maturity_t;
    double volatility_sigma;
    double d_1();
    double d_2();
    double Black_Scholes_Option_Price(bool flag);

public:
    BlackScholes(double strike_price_K, double current_price_S,
                 double risk_free_rate_r, double time_to_maturity_t,
                 double volatility_sigma);

    double call_price();
    double put_price();
    double delta();
    double vega();
};


#endif //PROJECT1_BLACKSCHOLES_H
