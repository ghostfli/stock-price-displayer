#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <curl/curl.h>

#include "fetch_daily_portfolio.hpp"

int main() {
    const char* apiKeyEnv = std::getenv("AV_API_KEY");
    if (!apiKeyEnv) {
        std::cerr << "Error: AV_API_KEY environment variable not set." << std::endl;
        return 1;
    }
    const std::string apiKey = apiKeyEnv;

    CURL* curl = curl_easy_init();
    CURLcode res;

    if (curl) {
        Portfolio portfolio = fetchDailyPortfolio(curl, res, apiKey, {"AAPL", "IBM"});
        curl_easy_cleanup(curl);

        for (auto& [symbol, position] : portfolio.positions) {
           for (auto &[date, bar] : position.tsData.bars) {
               std::cout << symbol << " " << date 
                         << " Open: " << bar.open
                         << " High: " << bar.high
                         << " Low: " << bar.low
                         << " Close: " << bar.close
                         << " Volume: " << bar.volume
                         << std::endl;
           }
        }
    }

    return 0;
}
