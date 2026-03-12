cmake_minimum_required(VERSION 3.10)
project(StockPriceDisplayer)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)

add_executable(StockPriceDisplayer
    main.cpp
    src/alpha_vantage_clients/av_ts_client.cpp
    src/alpha_vantage_clients/av_ts_client_daily/av_ts_client_daily.cpp
    src/alpha_vantage_clients/av_ts_client_intraday/av_ts_client_intraday.cpp
)

target_include_directories(StockPriceDisplayer PRIVATE src)
target_link_libraries(StockPriceDisplayer CURL::libcurl)

add_executable(test_sma tests/test_sma.cpp)
target_include_directories(test_sma PRIVATE src)