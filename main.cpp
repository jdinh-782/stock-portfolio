#include "API.hpp"
#include "Date.hpp"
#include "matplotlib-cpp/matplotlibcpp.h"
#include "xtensor.hpp"


namespace plt = matplotlibcpp;

int main() {
    Date d;
    auto current_date = d.get_date();
    d.split_date();
    auto starting_date = d.year_timeframe(1);

    std::cout << "current date: " << current_date << std::endl;
    std::cout << "starting date: " << starting_date << std::endl;

//    yahooAPI::YahooFinanceAPI api;  // create an API object

//    api.download_ticker_data("GME", starting_date, current_date);
//    api.set_interval(DAILY);

    // read file and create xtensor arrays



    return 0;
}
