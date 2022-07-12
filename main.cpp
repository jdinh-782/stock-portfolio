#include "API.hpp"
#include "Date.hpp"
#include "matplotlib-cpp/matplotlibcpp.h"
#include "xtensor.hpp"
#include "fstream"


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

    std::ifstream file;
    file.open("GME_1657598230.csv");

    auto data = xt::load_csv<std::string>(file);
    // std::cout << data << std::endl;

    std::vector<std::string> dates = {};
    unsigned int _shape = data.shape(0);

    for (int i = 1; i < _shape; i++)
        dates.push_back(data(i, 0));

    std::vector<double> open_data = {};
    for (int i = 1; i < _shape; i++) {
        double val = std::stod(data(i, 1));
        open_data.push_back(val);
    }

    plt::plot(open_data);
    plt::show();



    return 0;
}
