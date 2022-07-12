//
// Created by Johnson Dinh on 7/10/22.
//

#ifndef STOCK_PORTFOLIO_DATE_HPP
#define STOCK_PORTFOLIO_DATE_HPP

#include "iostream"
#include "string"
#include "chrono"
#include "ctime"



class Date {
    public:
        Date();
        std::string get_date();
        std::string year_timeframe(int num_years);
        std::string month_timeframe(int num_months);
        std::string day_timeframe(int num_days);

        void split_date();

    private:
        std::string _year;
        std::string _month;
        std::string _day;
        std::string current_date;
        std::string starting_date;

};


Date::Date() {
    _year = "2022";
    _month = "07";
    _day = "11";
    current_date = "";
    starting_date = "";
}

std::string Date::get_date() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream os;
    os << std::put_time(&tm, "%Y-%m-%d");
    current_date = os.str();

    return current_date;
}

void Date::split_date() {
    int i = 0;
    std::string s = "";

    // get year
    for (i; i < current_date.size(); i++) {
        if (current_date[i] == '-') {
            _year = s;
            s = "";
            i += 1;
            break;
        }
        else
            s += current_date[i];
    }

    // get month
    for (i; i < current_date.size(); i++) {
        if (current_date[i] == '-') {
            _month = s;
            s = "";
            i += 1;
            break;
        }
        else
            s += current_date[i];
    }

    // get day
    for (i; i < current_date.size(); i++) {
        if (current_date[i] == '-' || current_date[i] == '\0' || current_date[i] == ' ')
            break;
        else
            s += current_date[i];
    }
    _day = s;

    // std::cout << _year << " " << _month << " " << _day << std::endl;
}

// get starting_date from 1, 3, 5 years ago
std::string Date::year_timeframe(int num_years) {
    int starting_year = std::stoi(_year) - num_years;

    starting_date = std::to_string(starting_year) + "-" + _month + "-" + _day;

    return starting_date;
}

// get starting_date from 1, 3, 5 months ago
std::string Date::month_timeframe(int num_months) {
    int starting_year = std::stoi(_year);
    int starting_month = std::stoi(_month) - num_months;
    std::string updated_month;

    if (starting_month == 0) {
        starting_year -= 1;
        starting_month = 12;
    }
    else if (starting_month < 0) {
        starting_year -= 1;
        starting_month = abs(12 + starting_month);
    }

    if (starting_month < 10)
        updated_month = "0" + std::to_string(starting_month);
    else
        updated_month = std::to_string(starting_month);

    starting_date = std::to_string(starting_year) + "-" + updated_month + "-" + _day;

    return starting_date;
}

// get starting_date from 1, 7 days ago
std::string Date::day_timeframe(int num_days) {
    int starting_year = std::stoi(_year);
    int starting_month = std::stoi(_month);
    int starting_day = std::stoi(_day) - num_days;
    int month_days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    std::string updated_month, updated_day;

    if (starting_day == 0) {
        if (starting_month == 1) {
            starting_year -= 1;
            starting_day = 31;
            starting_month = 12;
        }
        else {
            starting_month -= 1;
            starting_day = month_days[std::stoi(_month)];
        }
    }
    else if (starting_day < 0) {
        if (starting_month == 1) {
            starting_year -= 1;
            starting_month = 12;
            starting_day = 32 - num_days;
        }
        else {
            starting_month -= 1;
            starting_day = month_days[starting_month] - abs(starting_day);
        }
    }

    if (starting_month < 10)
        updated_month = "0" + std::to_string(starting_month);
    else
        updated_month = std::to_string(starting_month);

    if (starting_day < 10)
        updated_day = "0" + std::to_string(starting_day);
    else
        updated_day = std::to_string(starting_day);

    starting_date = std::to_string(starting_year) + "-" + updated_month + "-" + updated_day;

    return starting_date;
}


#endif //STOCK_PORTFOLIO_DATE_HPP
