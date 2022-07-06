#include <iostream>
#include "API.hpp"



int main() {
    yahooAPI::YahooFinanceAPI api;  // create an API object

    api.download_ticker_data("qqq", "2020-01-01", "2020-10-07");
    api.set_interval(MONTHLY);



    return 0;
}
