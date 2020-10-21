//
// Created by Rohan Sacheti on 10/21/20.
//

#include "SampleStock.h"

void SampleStock::saveSampleStock() {
//    create all the vectors for the appropriate values
    vector<double> stock_price_S;
    vector<double> option_price_V;
    vector<double> risk_free_rate_r;
    vector<double> delta;
    vector<double> B_i;
    vector<double> hedging_error;
    vector<double> cum_hedging_error;
    vector<double> money_invested;
    vector<double> portfolio_val;

    vector<vector<double>> all_stock_prices;
    vector<vector<double>> all_option_prices;
    vector<vector<double>> all_hedging_error;
    vector<vector<double>> all_cum_hedging_error;
    vector<vector<double>> all_delta_p;


//    Double for loop, outer one to simulate 1000 paths

    for (int count = 0; count < 1000; count++) {
        stock_price_S.push_back(S0);
        BlackScholes bs(K, S0, r, T, sigma);
        option_price_V.push_back(bs.call_price());
        delta.push_back(bs.delta());
        B_i.push_back(option_price_V[0] - (delta[0] * stock_price_S[0]));
        hedging_error.push_back(0);
        cum_hedging_error.push_back(0);
        money_invested.push_back(delta[0] * stock_price_S[0]);
        portfolio_val.push_back(option_price_V[0] - money_invested[0]);

//      Inner for loop to create the individual paths
        for (int i = 0; i < N - 1; i++) {
            stock_price_S.push_back(stock_price_S[i] +
                                    (mean * stock_price_S[i] * delta_t) +
                                    (sigma * stock_price_S[0] * sqrt(delta_t) * normalRandom()));
//            BS option pricing (call)
            BlackScholes bs(K, stock_price_S[i + 1], r, T - ((i + 1) * delta_t), sigma);
            option_price_V.push_back(bs.call_price());
            delta.push_back(bs.delta());
//            Cumulative hedging error
            cum_hedging_error.push_back((delta[i] * stock_price_S[i + 1]) +
                                    (B_i[i] * exp(r * delta_t)) - option_price_V[i + 1]);
            hedging_error.push_back(cum_hedging_error[i+1] - cum_hedging_error[i]);
            money_invested.push_back(delta[i + 1] * stock_price_S[i +1]);
            portfolio_val.push_back(option_price_V[i + 1] - money_invested[i + 1]);
            B_i.push_back((delta[i] * stock_price_S[i + 1]) +
                          (B_i[i] * exp(r * delta_t)) - (delta[i+1] * stock_price_S[i+1]));
        }
        all_option_prices.push_back(option_price_V);
        all_stock_prices.push_back(stock_price_S);
        all_delta_p.push_back(delta);
//        all_delta_portfolio.push_back(portfolio_val);
        all_cum_hedging_error.push_back(cum_hedging_error);
        all_hedging_error.push_back(hedging_error);
        option_price_V.clear();
        cum_hedging_error.clear();
        stock_price_S.clear();
        delta.clear();
        portfolio_val.clear();
        hedging_error.clear();
        B_i.clear();
        money_invested.clear();
    }
    ofstream sim_stock_price ("results_part_I.csv");

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 1000 - 1 && j == 4) {
                sim_stock_price << "Path_" << i << endl;
            } else {
                sim_stock_price << "Path_" << i << ",";
            }
        }
    }

    for (int i = 0; i < 1000; i++) {
        if (i == 1000-1) {
            sim_stock_price << "Stock_Price_" << i << "," << "Option_Price_" << i << ","
            << "Delta_" << i << "," << "Portfolio_value_" << i << "," << "Hedging_error_" << i << endl;
//            sim_option_price << "Stock_Price_" << i << endl;
        } else {
            sim_stock_price << "Stock_Price_" << i << "," << "Option_Price_" << i << ","
                            << "Delta_" << i << "," << "Cumulative_hedging_error_" << i << "," << "Hedging_error_" << i << ",";
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 1000; j++ ){
            if (j == 999) {
                sim_stock_price << all_stock_prices[j][i] << "," << all_option_prices[j][i] << "," << all_delta_p[j][i] << "," << all_cum_hedging_error[j][i] << "," << all_hedging_error[j][i] << endl;
            } else {
                sim_stock_price << all_stock_prices[j][i] << "," << all_option_prices[j][i] << "," << all_delta_p[j][i] << "," << all_cum_hedging_error[j][i] << "," << all_hedging_error[j][i] << ",";
            }
        }
    }

    sim_stock_price.close();

}

double SampleStock::normalRandom() {

    // construct a trivial random generator engine from a time-based seed:
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();;
    default_random_engine generator(seed);
    normal_distribution<double> distribution(0,1);
    return distribution(generator);
}