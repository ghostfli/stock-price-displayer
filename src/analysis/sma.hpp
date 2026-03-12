#ifndef SMA_HPP
#define SMA_HPP

#include <map>
#include <string>
#include <vector>
#include <stdexcept>
#include "../data/time_series_data.hpp"

// Returns a map of date -> SMA value for the given window size (in trading days).
// Dates with fewer than `window` preceding bars are omitted.
inline std::map<std::string, double> sma(const TimeSeriesData& ts, int window) {
    if (window <= 0)
        throw std::invalid_argument("SMA window must be > 0");

    // bars is a std::map keyed by date string "YYYY-MM-DD", which sorts chronologically
    std::vector<std::pair<std::string, double>> closes;
    closes.reserve(ts.bars.size());
    for (const auto& [date, bar] : ts.bars)
        closes.emplace_back(date, bar.close);
    // std::map iterates in ascending key order, so closes is already oldest -> newest

    std::map<std::string, double> result;
    for (int i = window - 1; i < static_cast<int>(closes.size()); ++i) {
        double sum = 0.0;
        for (int j = i - window + 1; j <= i; ++j)
            sum += closes[j].second;
        result[closes[i].first] = sum / window;
    }
    return result;
}

#endif // SMA_HPP
