//
// Created by Rohan Sacheti on 10/20/20.
//

#include "BlackScholes.h"

BlackScholes::BlackScholes(double strike_price_K, double current_price_S,
                           double risk_free_rate_r, double time_to_maturity_t,
                           double volatility_sigma) {

    this->strike_price_K = strike_price_K;
    this->current_price_S = current_price_S;
    this->risk_free_rate_r = risk_free_rate_r;
    this->time_to_maturity_t = time_to_maturity_t;
    this->volatility_sigma = volatility_sigma;
}

double BlackScholes::Black_Scholes_Option_Price(bool flag) {
    if (flag) {
//        call option
        return (current_price_S * normCDF.norm_distribution(d_1())) -
               (strike_price_K * exp(-risk_free_rate_r * time_to_maturity_t) * normCDF.norm_distribution(d_2()));
    }
//    put option
    return (-current_price_S * normCDF.norm_distribution(-d_1())) +
           (strike_price_K * exp(-risk_free_rate_r*time_to_maturity_t) * normCDF.norm_distribution(-d_2()));
}

double BlackScholes::call_price() {
    return Black_Scholes_Option_Price(true);
}
double BlackScholes::put_price() {
    return Black_Scholes_Option_Price(false);
}

double BlackScholes::d_1() {
//    calculates d_1
    return (log(current_price_S / strike_price_K) +
            ((risk_free_rate_r + (0.5 * pow(volatility_sigma, 2)))* time_to_maturity_t)) /
           (volatility_sigma * sqrt(time_to_maturity_t));
}

double BlackScholes::d_2() {
    //    calculates d_2
    return d_1() - (volatility_sigma * sqrt(time_to_maturity_t));
}

double BlackScholes::delta() {
    return normCDF.norm_distribution(d_1());
}

double BlackScholes::vega() {
    double pdf_norm = exp(-(pow(d_1(), 2))*0.5) / sqrt(2 * M_PI);
    return  current_price_S * sqrt(time_to_maturity_t) * pdf_norm;
}

int bs_main() {
//    unnittests
    BlackScholes bs(102, 100, 0.03, 2, 0.15);

    cout << "Call price: " << bs.call_price() << endl;
    cout << "Put price: " << bs.put_price() << endl;
    cout << "Delta price: " << bs.delta() << endl;
    cout << "Vega price: " << bs.vega   () << endl;

//    Call price: 10.3982
//    Put price: 6.45822
//    Delta price: 0.616216
//    Vega price: 54.0078
}