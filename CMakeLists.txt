cmake_minimum_required(VERSION 3.22)
project(stock_portfolio)

include_directories(/usr/local/opt/curl/include/)

set(CMAKE_CXX_STANDARD 23)

set(CURL_LIBRARY, "-lcurl")
find_package(CURL REQUIRED)

add_executable(stock_portfolio main.cpp API.hpp)

include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(stock_portfolio ${CURL_LIBRARIES})