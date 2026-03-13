#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <cstdlib>
#include <curl/curl.h>

#include "fetch_daily_portfolio.hpp"
#include "src/analysis/sma.hpp"

int main() {
    const char* apiKeyEnv = std::getenv("AV_API_KEY");
    if (!apiKeyEnv) {
        std::cerr << "Error: AV_API_KEY environment variable not set." << std::endl;
        return 1;
    }
    const std::string apiKey = apiKeyEnv;

    // unique_ptr ensures curl_easy_cleanup is always called, even if an exception is thrown
    auto curl = std::unique_ptr<CURL, decltype(&curl_easy_cleanup)>(
                    curl_easy_init(), curl_easy_cleanup);
    CURLcode res = CURLE_OK;
    
    //Early check if CURL was initialized successfully
    if (!curl) {
        std::cerr << "Error: failed to initialize CURL." << std::endl;
        return 1;
    }

    try {
        Portfolio portfolio = fetchDailyPortfolio(curl.get(), res, apiKey, {"AAPL", "IBM"});

        for (auto& [symbol, position] : portfolio.positions) {
            auto sma20  = sma(position.tsData, 20);
            auto sma50  = sma(position.tsData, 50);
            auto sma200 = sma(position.tsData, 200);

            std::cout << "\n=== " << symbol << " SMA ===\n";
            for (auto& [date, bar] : position.tsData.bars) {
                std::cout << date << "  close: " << bar.close;
                if (sma20.count(date))  std::cout << "  SMA20: "  << sma20.at(date);
                if (sma50.count(date))  std::cout << "  SMA50: "  << sma50.at(date);
                if (sma200.count(date)) std::cout << "  SMA200: " << sma200.at(date);
                std::cout << "\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}