#include <iostream>
#include "vector"
#include "StdNormalCDF.h"
#include "BlackScholes.h"
#include <random>
#include "SampleStock.h"

using namespace std;
#include <fstream>
#include <string>
#include <sstream>

double normalRandom() {
    // construct a trivial random generator engine from a time-based seed:
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();;
    default_random_engine generator(seed);
    normal_distribution<double> distribution(0,1);
    return distribution(generator);
}


void sample_path() {
    vector<double> stock_price_S;
    vector<double> option_price_V;
    vector<double> risk_free_rate_r;
    vector<double> delta;
    vector<double> B_i;

    double S0 = 100;
    double T = 0.4;
    double mean = 0.05;
    double sigma = 0.24;
    double r = 0.025;
    double N = 100;
    double K = 105;
    double delta_t = T/N;

    vector<vector<double>> all_stock_prices;
    vector<vector<double>> all_option_prices;

    for (int count = 0; count < 1000; count++) {
        stock_price_S.push_back(S0);
        BlackScholes bs(K, S0, r, T, sigma);
        option_price_V.push_back(bs.call_price());
        for (int i = 0; i < N - 1; i++) {
//            sim_stock_price << stock_price_S[i] << "," << option_price_V[i] << endl;
            stock_price_S.push_back(stock_price_S[i] +
                                    (mean * stock_price_S[i] * delta_t) +
                                    (sigma * stock_price_S[0] * sqrt(delta_t) * normalRandom()));

            BlackScholes sb(K, stock_price_S[i + 1], r, T - ((i + 1) * delta_t), sigma);
            option_price_V.push_back(sb.call_price());
        }
        all_option_prices.push_back(option_price_V);
        all_stock_prices.push_back(stock_price_S);
        option_price_V.clear();
        stock_price_S.clear();
    }
    ofstream sim_stock_price ("sim_stock_file.csv");
    ofstream sim_option_price ("sim_option_file.csv");

    sim_stock_price<<" Testing the delta hedging implementation"<<endl;

    for (int i = 0; i < 1000; i++) {
        if (i == 1000-1) {
            sim_stock_price << "Stock_Price_" << i << endl;
            sim_option_price << "Stock_Price_" << i << endl;
        } else {
            sim_stock_price << "Stock_Price_" << i << ",";
            sim_option_price << "Option_Price_" << i << ",";
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 1000; j++ ){
            if (j == 999) {
                sim_stock_price << all_stock_prices[j][i] << endl;
                sim_option_price << all_option_prices[j][i] << endl;
            } else {
                sim_stock_price << all_stock_prices[j][i] << ",";
                sim_option_price << all_option_prices[j][i] << ",";
            }
        }
    }

    sim_stock_price.close();
    sim_option_price.close();

}

void delta_hedging() {
    vector<double> stock_price_S;
    vector<double> option_price_V;
    vector<double> risk_free_rate_r;
    vector<double> delta;
    vector<double> B_i;
    vector<double> hedging_error;

    double S0 = 100;
    double T = 0.4;
    double mean = 0.05;
    double sigma = 0.24;
    double r = 0.025;
    double N = 100;
    double K = 105;
    double delta_t = T/N;

//    stock_price_S.push_back(S0);
//    BlackScholes bs(K, S0, r, T, sigma);
//    option_price_V.push_back(bs.call_price());
//    delta.push_back(bs.delta());
//    B_i.push_back(option_price_V[0] - (delta[0] * stock_price_S[0]));


    vector<vector<double>> all_stock_prices;
    vector<vector<double>> all_option_prices;

    for (int count = 0; count < 1000; count++) {
        stock_price_S.push_back(S0);
        BlackScholes bs(K, S0, r, T, sigma);
        option_price_V.push_back(bs.call_price());
        delta.push_back(bs.delta());
        B_i.push_back(option_price_V[0] - (delta[0] * stock_price_S[0]));
        hedging_error.push_back(0);

        for (int i = 0; i < N - 1; i++) {
            stock_price_S.push_back(stock_price_S[i] +
                                    (mean * stock_price_S[i] * delta_t) +
                                    (sigma * stock_price_S[0] * sqrt(delta_t) * normalRandom()));

            BlackScholes bs(K, stock_price_S[i + 1], r, T - ((i + 1) * delta_t), sigma);
            option_price_V.push_back(bs.call_price());
            delta.push_back(bs.delta());
            hedging_error.push_back((delta[i] * stock_price_S[i + 1]) +
            (B_i[i] * exp(r * delta_t)) - option_price_V[i + 1]);
            B_i.push_back((delta[i] * stock_price_S[i + 1]) +
            (B_i[i] * exp(r * delta_t)) - (delta[i+1] * stock_price_S[i+1]));
        }
        all_option_prices.push_back(option_price_V);
        all_stock_prices.push_back(stock_price_S);
        option_price_V.clear();
        stock_price_S.clear();
    }
    ofstream sim_stock_price ("test_sim_stock_file.csv");
//    ofstream sim_option_price ("sim_option_file.csv");

    sim_stock_price<<" Testing the delta hedging implementation"<<endl;

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 2; j++) {
            if (i == 1000 - 1 && j == 1) {
                sim_stock_price << "Path_" << i << endl;
//            sim_option_price << "Stock_Price_" << i << endl;
            } else {
                sim_stock_price << "Path_" << i << ",";
//            sim_option_price << "Option_Price_" << i << ",";
            }
        }
    }

    for (int i = 0; i < 1000; i++) {
        if (i == 1000-1) {
            sim_stock_price << "Stock_Price_" << i << "," << "Option_Price_" << i << endl;
//            sim_option_price << "Stock_Price_" << i << endl;
        } else {
            sim_stock_price << "Stock_Price_" << i << "," << "Option_Price_" << i << ",";
//            sim_option_price << "Option_Price_" << i << ",";
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 1000; j++ ){
            if (j == 999) {
                sim_stock_price << all_stock_prices[j][i] << "," << all_option_prices[j][i] << endl;
//                sim_option_price << all_option_prices[j][i] << endl;
            } else {
                sim_stock_price << all_stock_prices[j][i] << "," << all_option_prices[j][i] << ",";
//                sim_option_price << all_option_prices[j][1] << ",";
            }
        }
    }

    sim_stock_price.close();
//    sim_option_price.close();

}



int main() {
    std::cout << "Hello, World!" << std::endl;

//    StdNormalCDF test;
//    cout << test.norm_distribution(0.296);
//
//    BlackScholes bs(102, 100, 0.03, 2, 0.15);
//
//    cout << "Call price: " << bs.call_price() << endl;
//    cout << "Put price: " << bs.put_price() << endl;
//    cout << "Delta price: " << bs.delta() << endl;
//    cout << "Vega price: " << bs.vega   () << endl;

//    sample_path();
//    delta_hedging();
    SampleStock test;
    test.saveSampleStock();
    return 0;
}
