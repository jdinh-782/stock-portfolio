#include "API.hpp"
#include "Date.hpp"
#include "Data.hpp"
#include "Plot.hpp"



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

    Data data(file_name);
    auto open_data = data.get_open_data();
    auto close_data = data.get_close_data();
    auto line_color = data.get_trend();

//    plt::figure_size(1280, 720);
//    plt::plot(open_data, line_color);
//    plt::grid(true);
//    plt::show();

    // work on predictions
    std::vector<std::size_t> shape = {1, open_data.size()};
    auto a = xt::adapt(open_data, shape);
    auto b = xt::adapt(close_data, shape);
    auto open_close = a - b;


    return 0;
}
