#ifndef FETCH_PORTFOLIO_HPP
#define FETCH_PORTFOLIO_HPP

#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include "alpha_vantage_clients/av_ts_client_daily/av_ts_client_daily.hpp"
#include "data/time_series_data.hpp"
#include "data/portfolio.hpp"

static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Fetches daily time series data from Alpha Vantage for each symbol and returns a Portfolio.
// curl: an already-initialized CURL handle (from curl_easy_init)
// res: output parameter — set to the last CURLcode, CURLE_OK if all succeeded
// apiKey: your Alpha Vantage API key
// symbols: list of ticker symbols e.g. {"AAPL", "MSFT", "GOOG"}
Portfolio fetchDailyPortfolio(CURL* curl, CURLcode& res, const std::string& apiKey, const std::vector<std::string>& symbols) {
    Portfolio portfolio;

    for (const std::string& symbol : symbols) {
        std::string readBuffer;
        AlphaVantageTimeSeriesClientDaily client(apiKey, symbol);

        curl_easy_reset(curl);
        curl_easy_setopt(curl, CURLOPT_URL, client.url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "CURL error for " << symbol << ": " << curl_easy_strerror(res) << std::endl;
            continue;
        }

        auto jsonData = nlohmann::json::parse(readBuffer);

        // Check for API rate limit or error messages
        if (jsonData.contains("Note") || jsonData.contains("Information")) {
            std::string msg = jsonData.contains("Note")
                ? jsonData["Note"].get<std::string>()
                : jsonData["Information"].get<std::string>();
            std::cerr << "API error for " << symbol << ": " << msg << std::endl;
            continue;
        }

        TimeSeriesData tsData = TimeSeriesData::fromJSON(jsonData, symbol);
        if (tsData.bars.empty()) {
            std::cerr << "No data found for " << symbol << std::endl;
            continue;
        }

        portfolio.add(tsData, 0.0, 0.0); // shares and avgCost default to 0 — set after fetching

        // Respect Alpha Vantage free tier rate limit of 5 requests/min
        std::this_thread::sleep_for(std::chrono::milliseconds(13000));
    }

    return portfolio;
}

#endif // FETCH_PORTFOLIO_HPP
