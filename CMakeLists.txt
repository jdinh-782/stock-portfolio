cmake_minimum_required(VERSION 3.22)
project(stock_portfolio)


# for matplotlibcpp
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
find_package(PythonLibs 2.7 REQUIRED)
include_directories(${PYTHON3_INCLUDE_DIRS} ${NumPy_INCLUDE_DIRS})
if(NOT PythonLibs_FOUND)
    message(WARNING "PythonLibs 2.7 not found. Make sure you have installed python 2.7.
       If that doesn't solve the problem, consult
       https://github.com/lava/matplotlib-cpp")
endif()

include_directories(/usr/local/opt/curl/include/)

set(CMAKE_CXX_STANDARD 23)

set(CURL_LIBRARY, "-lcurl")
find_package(CURL REQUIRED)


add_executable(stock_portfolio main.cpp API.hpp Date.hpp)

include_directories(stock_portfolio PRIVATE ${PYTHON_INCLUDE_DIRS} ${CURL_INCLUDE_DIR})
target_link_libraries(stock_portfolio
                        PRIVATE
                            ${PYTHON_LIBRARIES}
                            Python3::NumPy
                        ${CURL_LIBRARIES}
)