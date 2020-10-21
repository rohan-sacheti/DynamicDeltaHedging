#include <iostream>
#include "vector"
#include "StdNormalCDF.h"
#include "BlackScholes.h"
#include <random>
#include "SampleStock.h"
#include "MarketDataHedge.h"


using namespace std;
#include <fstream>
#include <string>
#include <sstream>

int main() {
    StdNormalCDF test1;
    cout << test1.norm_distribution(0.296);

    BlackScholes bs(102, 100, 0.03, 2, 0.15);

    cout << "Call price: " << bs.call_price() << endl;
    cout << "Put price: " << bs.put_price() << endl;
    cout << "Delta price: " << bs.delta() << endl;
    cout << "Vega price: " << bs.vega   () << endl;

    cout << "*****************************************" << endl;
    cout << "*************** PART I ******************" << endl;
    cout << "*****************************************" << endl;

    SampleStock test2;
    test2.saveSampleStock();

    cout << "*******************************************" << endl;
    cout << "**************** PART II ******************" << endl;
    cout << "*******************************************" << endl;

    MarketDataHedge test3("2011-07-05", "2011-07-29", "2011-09-17", 500);
    test3.getResults();

    return 0;
}
