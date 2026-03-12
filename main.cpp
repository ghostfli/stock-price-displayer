#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <curl/curl.h>

#include "fetch_daily_portfolio.hpp"
#include "src/analysis/sma.hpp"

int main() {
    //get the API key from environment variable
    const char* apiKeyEnv = std::getenv("AV_API_KEY");
    if (!apiKeyEnv) {
        std::cerr << "Error: AV_API_KEY environment variable not set." << std::endl;
        return 1;
    }
    //Set API key from environment variable
    const std::string apiKey = apiKeyEnv;
    //Initialize CURL
    CURL* curl = curl_easy_init();
    CURLcode res;

    if (curl) {
        //Fetch portfolio data for AAPL and IBM, then calculate and print SMAs
        Portfolio portfolio = fetchDailyPortfolio(curl, res, apiKey, {"AAPL", "IBM"});
        curl_easy_cleanup(curl);

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
    }

    return 0;
}
