//
// Created by Rohan Sacheti on 10/21/20.
//

#include "MarketDataHedge.h"
#include "BlackScholes.h"
#include "ImpliedVol.h"
//#include <boost/date_time.hpp>

MarketDataHedge::MarketDataHedge(string t0, string tn, string T, double K) {
    this->t0 = t0;
    this->tn = tn;
    this->T = T;
    this->K = K;
}

double MarketDataHedge::getOptionData() {
    vector<string> date_op;
    vector<string> exdate_op;
    vector<string> type;
    vector<double> strike_price;
    vector<double> best_bid;
    vector<double> best_offer;
    vector<double> avg_option_price;
    ifstream infile("./data/op_GOOG.csv");

    string line, colname;

    bool header_reached = false;

    while (getline(infile, line) && infile.is_open()) {
        // getline(infile, line);
        string col1, col2, col3, col4, col5, col6;
        string delimiter = ",";
        int starting_position = 0;
        int delimit_position = line.find(delimiter);
//        date
        col1 = line.substr(starting_position, delimit_position);
        line = line.substr(delimit_position+1, line.length());
//        exdate
        delimit_position = line.find(delimiter);
        col2 = line.substr(starting_position, delimit_position);
        line = line.substr(delimit_position+1, line.length());
//        put/call
        delimit_position = line.find(delimiter);
        col3 = line.substr(starting_position, delimit_position);
        line = line.substr(delimit_position+1, line.length());
//        strike price
        delimit_position = line.find(delimiter);
        col4 = line.substr(starting_position, delimit_position);
        line = line.substr(delimit_position+1, line.length());
//      best_bid
        delimit_position = line.find(delimiter);
        col5 = line.substr(starting_position, delimit_position);
        line = line.substr(delimit_position+1, line.length());
//        best_offer
        col6 = line.substr(starting_position, line.length());
        bool withinBounds = false;
        if (header_reached) {
            if (col1 == t0) {
                withinBounds = true;
            }
            if (withinBounds && col2 == tn && col3 == "C" && stod(col4) == K) {
                date_op.push_back(col1);
                exdate_op.push_back(col2);
                type.push_back(col3);
                strike_price.push_back(stod(col4));
                best_bid.push_back(stod(col5));
                best_offer.push_back(stod(col6));
                avg_option_price.push_back((stod(col5) + stod(col6)) / 2);
            }
            if (col1 == tn){
                withinBounds = false;
            }


        } else {
            header_reached = "date" == col1;
        }
    }

    infile.close();

    return 2;
}
void MarketDataHedge::getResults() {
    vector<double> stock_price;
    vector<string> date_stock;
    ifstream infile("./data/sec_GOOG.csv");

    string line, colname;

    bool header_reached = false;
    bool withinBounds = false;

    while (getline(infile, line) && infile.is_open()) {
        // getline(infile, line);
        string col1, col2;
        string delimiter = ",";
        int delimit_position = line.find(delimiter);
        col1 = line.substr(0, delimit_position);
        col2 = line.substr(delimit_position + 1, line.length());

        if (header_reached) {
            if (t0 == col1) {
                withinBounds = true;
            }
            if (withinBounds)
            {
                date_stock.push_back(col1);
                stock_price.push_back(stod(col2));
            }
            if (tn == col1) {
                withinBounds = false;
            }

        } else {
            header_reached = "date" == col1;
        }
    }

    infile.close();

    vector<string> interest_date;
    vector<double> interest_rate;
    ifstream interest("./data/interest.csv");

//    string line, colname;

    header_reached = false;

    withinBounds = false;
    while (getline(interest, line) && interest.is_open()) {
        // getline(infile, line);
        string col1, col2;
        string delimiter = ",";
        int delimit_position = line.find(delimiter);
        col1 = line.substr(0, delimit_position);
        col2 = line.substr(delimit_position + 1, line.length());

        if (header_reached) {
            if (t0 == col1) {
                withinBounds = true;
            }
            if (withinBounds)
            {
                interest_date.push_back(col1);
                interest_rate.push_back(stod(col2) * 0.01);
            }
            if (tn == col1) {
                withinBounds = false;
            }

        } else {
            header_reached = "date" == col1;
        }
    }

    interest.close();

    cout << "done!";

    vector<string> date_op;
    vector<string> exdate_op;
    vector<string> type;
    vector<double> strike_price;
    vector<double> best_bid;
    vector<double> best_offer;
    vector<double> avg_option_price;
    ifstream option_data("./data/op_GOOG.csv");

//    string line, colname;

    header_reached = false;

    withinBounds = false;
    while (getline(option_data, line) && option_data.is_open()) {
        // getline(infile, line);
        string col1, col2, col3, col4, col5, col6;
        string delimiter = ",";
        int starting_position = 0;
        int delimit_position = line.find(delimiter);
//        date
        col1 = line.substr(starting_position, delimit_position);
        line = line.substr(delimit_position+1, line.length());
//        exdate
        delimit_position = line.find(delimiter);
        col2 = line.substr(starting_position, delimit_position);
        line = line.substr(delimit_position+1, line.length());
//        put/call
        delimit_position = line.find(delimiter);
        col3 = line.substr(starting_position, delimit_position);
        line = line.substr(delimit_position+1, line.length());
//        strike price
        delimit_position = line.find(delimiter);
        col4 = line.substr(starting_position, delimit_position);
        line = line.substr(delimit_position+1, line.length());
//      best_bid
        delimit_position = line.find(delimiter);
        col5 = line.substr(starting_position, delimit_position);
        line = line.substr(delimit_position+1, line.length());
//        best_offer
        col6 = line.substr(starting_position, line.length());

        if (header_reached) {
            if (col1 == t0 || col1 == tn) {
                withinBounds = true;
            }
            if (withinBounds && col2 == T && col3 == "C" && stod(col4) == K) {
                date_op.push_back(col1);
                exdate_op.push_back(col2);
                type.push_back(col3);
                strike_price.push_back(stod(col4));
                best_bid.push_back(stod(col5));
                best_offer.push_back(stod(col6));
                avg_option_price.push_back((stod(col5) + stod(col6)) / 2);
            }
            if (col1 == tn){
                withinBounds = false;
            }


        } else {
            header_reached = "date" == col1;
        }
    }

    double low_vol = 0.001;
    double high_vol = 0.99;
    double epsilon = 0.001;
    option_data.close();
    double delta_t = 1./252.;
//    vector<double> option_price_V;
    vector<double> delta;
    vector<double> B_i;
    vector<double> hedging_error;
    vector<double> cum_hedging_error;
    vector<double> money_invested;
    vector<double> portfolio_val;
    vector<double> implied_vol;

    hedging_error.push_back(0);
    cum_hedging_error.push_back(0);

    for (int i = 0; i < date_stock.size(); i++) {
        double date_diff = dateDiff(date_stock[i], T);
        double ttmat = date_diff * delta_t;

        ImpliedVol vol;
        double sigma = vol.implied_vol(avg_option_price[i], low_vol, high_vol, epsilon, K, ttmat, stock_price[i], interest_rate[i]);
        implied_vol.push_back(sigma);

        BlackScholes bs(K, stock_price[i], interest_rate[i],  ttmat, sigma);

        delta.push_back(bs.delta());
    }

    B_i.push_back(avg_option_price[0] - (delta[0] * stock_price[0]));
    portfolio_val.push_back(0);

    for (int i = 1; i < date_stock.size(); i++) {
        B_i.push_back((delta[i-1] * stock_price[i]) +
                                            (B_i[i-1] * exp(interest_rate[i-1] * delta_t)) - (delta[i] * stock_price[i]));
        cum_hedging_error.push_back((delta[i - 1] * stock_price[i]) +
                                (B_i[i - 1] * exp(interest_rate[i - 1] * delta_t)) - avg_option_price[i]);
        hedging_error.push_back(cum_hedging_error[i] - cum_hedging_error[i-1]);
        portfolio_val.push_back(avg_option_price[i]-avg_option_price[0]);
    }

    ofstream sim_stock_price ("results.csv");
    sim_stock_price << "date,Stock_Price,Option_Price,Implied_Volatility,delta,PNL,PNL(with_hedge),Daily_hedging_error" << endl;
    for (int i = 0; i < avg_option_price.size(); i++) {
        sim_stock_price << date_stock[i] << "," << stock_price[i] << "," << avg_option_price[i]
        << "," << implied_vol[i] << "," << delta[i] << "," << portfolio_val[i] << "," << cum_hedging_error[i] << "," << hedging_error[i]<< endl;
    }
    sim_stock_price.close();
}

int MarketDataHedge::dateDiff(string date1, string date2) {
    int day1, day2, month1, month2, year1, year2;
    const int monthDays[12] = {31, 28, 31, 30, 31, 30,
                               31, 31, 30, 31, 30, 31};

    year1 = stoi(date1.substr(0,4));
    month1 = stoi(date1.substr(5,7));
    day1 = stoi(date1.substr(8,10));

    year2 = stoi(date2.substr(0,4));
    month2 = stoi(date2.substr(5,7));
    day2= stoi(date2.substr(8,10));

    int year_diff = year2 - year1;
    int month_diff = month2 - month1;
    int day_diff = day2 - day1;

    int days_apart = round((5./7.) * ((year_diff * 365) + (month_diff * 30) + (day_diff)));

    return days_apart;
}