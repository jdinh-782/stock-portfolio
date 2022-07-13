//
// Created by Johnson Dinh on 7/12/22.
//

#ifndef STOCK_PORTFOLIO_DATA_HPP
#define STOCK_PORTFOLIO_DATA_HPP

#include "xtensor.hpp"
#include "fstream"


class Data {
    public:
        Data();
        Data(std::string file_name);

        std::vector<std::string> get_dates();
        std::vector<double> get_open_data();
        std::vector<double> get_close_data();
        std::vector<double> get_high_data();
        std::vector<double> get_low_data();

        std::string get_trend();

    private:
        std::string _file_name;
        std::vector<double> open_data;
        std::vector<double> close_data;
        std::vector<double> high_data;
        std::vector<double> low_data;
        std::vector<std::string> _dates;
        xt::xarray<std::string> _data;
        unsigned int _shape = 0;

    void load_data();

};

Data::Data() {
    _file_name = "";
    open_data = {};
    _dates = {};
    _shape = _data.shape(0);
}

Data::Data(std::string file_name) {
    this->_file_name = file_name;
    open_data = {};
    _dates = {};
    _shape = _data.shape(0);

    load_data();
}

void Data::load_data() {
    std::ifstream file;
    file.open(_file_name);

    _data = xt::load_csv<std::string>(file);
    // std::cout << _data << std::endl;

    _shape = _data.shape(0);
    file.close();
}

std::vector<std::string> Data::get_dates() {
    for (int i = 1; i < _shape; i++)
        _dates.push_back(_data(i, 0));

    return _dates;
}

std::vector<double> Data::get_open_data() {
    for (int i = 1; i < _shape; i++) {
        double val = std::stod(_data(i, 1));
        open_data.push_back(val);
    }

    return open_data;
}

std::vector<double> Data::get_close_data() {
    for (int i = 1; i < _shape; i++) {
        double val = std::stod(_data(i, 4));
        close_data.push_back(val);
    }

    return close_data;
}

std::vector<double> Data::get_high_data() {
    for (int i = 1; i < _shape; i++) {
        double val = std::stod(_data(i, 2));
        high_data.push_back(val);
    }

    return high_data;
}

std::vector<double> Data::get_low_data() {
    for (int i = 1; i < _shape; i++) {
        double val = std::stod(_data(i, 3));
        low_data.push_back(val);
    }

    return low_data;
}

std::string Data::get_trend() {
    std::vector<std::size_t> open_data_shape = {1, open_data.size()};
    auto a = xt::adapt(open_data, open_data_shape);

    auto trend = xt::all(xt::diff(a) > 0);
    std::string line_color = "r-";

    if (trend == 1)
        line_color = "g-";

    return line_color;
}

#endif //STOCK_PORTFOLIO_DATA_HPP
