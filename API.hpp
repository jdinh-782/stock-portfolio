//
// Created by Johnson Dinh on 7/4/22.
//

// https://medium.com/analytics-vidhya/retrieving-historical-stock-data-in-c-2876ab9c5ff

#ifndef STOCK_PORTFOLIO_API_H
#define STOCK_PORTFOLIO_API_H

#include <string>
#include <curl/curl.h>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include "iostream"


enum Interval {
    WEEKLY,
    MONTHLY,
    DAILY
};


static const std::string EnumAPIValues[] {
        "1wk",
        "1mo",
        "1d"
};


std::string get_api_interval_value(int value) {
    return EnumAPIValues[value];
}


struct memory {
    char* memory;
    size_t size;
};

static size_t
writecallback(char* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct memory* mem = (struct memory*) userp;

    char* ptr = static_cast<char *>(realloc(mem->memory, mem->size + realsize + 1));
    if (ptr == NULL)
        return 0;

    mem->memory = ptr;
    memcpy(&mem->memory[mem->size], contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}


namespace yahooAPI {
    class YahooFinanceAPI {
        public:
            YahooFinanceAPI();

             void set_interval(Interval interval);
             void set_col_name(std::string name);

            std::string download_ticker_data(std::string ticker, std::string start, std::string end);

        private:
            std::string base_url;
            Interval _interval;
            std::string _col_name;

            std::string build_url(std::string ticker, std::string start_date, std::string end_date);
            std::string timestamp_from_string(std::string date);

            bool string_replace(std::string& str, const std::string from, const std::string to);
            void download_file(std::string url, std::string filename);
    };

    YahooFinanceAPI::YahooFinanceAPI() {
        this->base_url = "https://query1.finance.yahoo.com/v7/finance/download/{ticker}?period1={start_time}&period2="
                         "{end_time}&interval={interval}&events=history";
        this->_interval = DAILY;
        this->_col_name = "Open";
    }

    std::string YahooFinanceAPI::timestamp_from_string(std::string date) {
        struct std::tm time = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::istringstream ss(date);

        ss >> std::get_time(&time, "%Y-%m-%d");
        if (ss.fail()) {
            std::cerr << "ERROR: Cannot parse date string (" << date << "); required format %Y-%m-%d" << std::endl;
            exit(1);
        }
        time.tm_hour = 0;
        time.tm_min = 0;
        time.tm_sec = 0;
        std::time_t epoch = std::mktime(&time);

        return std::to_string(epoch);
    }

    bool YahooFinanceAPI::string_replace(std::string &str, const std::string from, const std::string to) {
        size_t start = str.find(from);
        if (start == std::string::npos)
            return false;
        str.replace(start, from.length(), to);
        return true;
    }

    std::string YahooFinanceAPI::build_url(std::string ticker, std::string start, std::string end) {
        std::string url = this->base_url;
        string_replace(url, "{ticker}", ticker);
        string_replace(url, "{start_time}", timestamp_from_string(start));
        string_replace(url, "{end_time}", timestamp_from_string(end));
        string_replace(url, "{interval}", get_api_interval_value(this->_interval));
        return url;
    }

    void YahooFinanceAPI::set_interval(Interval interval) {
        this->_interval = interval;
    }

    void YahooFinanceAPI::set_col_name(std::string name) {
        this->_col_name = name;
    }

    void YahooFinanceAPI::download_file(std::string url, std::string filename) {
            CURL* curl;
            CURLcode res;
            FILE* file;
            struct memory chunk;

            chunk.memory = NULL;
            chunk.size = 0;
            curl_global_init(CURL_GLOBAL_ALL);

            curl = curl_easy_init();
            if (curl) {
                file = fopen(filename.c_str(), "wb");
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

                res = curl_easy_perform(curl);

                if (res != CURLE_OK) {
                    fprintf(stderr, "curl_easy_perform() return %s\n", curl_easy_strerror(res));
                }
//                else {
//                    printf("We got %d bytes to our callback.\n", (int)chunk.size);
//                }
                free(chunk.memory);
                curl_easy_cleanup(curl);
                fclose(file);
            }
            curl_global_cleanup();
    }

    std::string YahooFinanceAPI::download_ticker_data(std::string ticker, std::string start, std::string end) {
        std::string url = build_url(ticker, start, end);
        std::time_t now = std::time(0);
        std::string output_file_name = ticker + "_" + std::to_string(now) + ".csv";

        download_file(url, output_file_name);
        // std::cout << url << std::endl;

        return output_file_name;
    }
}





#endif //STOCK_PORTFOLIO_API_H