//
// Created by Rohan Sacheti on 10/21/20.
//

#include "ImpliedVol.h"
#include "BlackScholes.h"
#include <cmath>


double ImpliedVol::implied_vol(double y_target, double m, double n,
                               double epsilon, double K, double T,
                               double s, double r) {
    double x = 0.5 * (m + n);

    BlackScholes bs(K, s, r, T, x);

    double y = bs.call_price();

    do {
        if (y < y_target) {
            m = x;
        }

        if (y > y_target) {
            n = x;
        }

        x = 0.5 * (m + n);

        BlackScholes bs(K, s, r, T, x);

        y = bs.call_price();

    } while (fabs(y-y_target) > epsilon);

    return x;
}