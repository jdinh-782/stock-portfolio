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

    yahooAPI::YahooFinanceAPI api;  // create an API object

    std::string file_name = api.download_ticker_data("GME", starting_date, current_date);
    api.set_interval(DAILY);

    std::ifstream file;
    file.open(file_name);

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
    std::vector<std::size_t> open_data_shape = {1, open_data.size()};
    auto a = xt::adapt(open_data, open_data_shape);

    auto trend = xt::all(xt::diff(a) > 0);
    std::string line_color = "r-";

    if (trend == 1)
        line_color = "g-";

    plt::figure_size(1280, 720);
    plt::plot(open_data, line_color);
    plt::grid(true);
    plt::show();




    return 0;
}
