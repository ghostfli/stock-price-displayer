#ifndef TIME_SERIES_DATA_HPP
#define TIME_SERIES_DATA_HPP

#include <string>
#include <map>
#include <nlohmann/json.hpp>

struct DailyBar {
    double open;
    double high;
    double low;
    double close;
    long   volume;
};

struct TimeSeriesData {
    std::string symbol;
    std::map<std::string, DailyBar> bars; // key = date string e.g. "2026-03-10", sorted ascending

    static TimeSeriesData fromJSON(const nlohmann::json& jsonData, const std::string& symbol) {
        TimeSeriesData result;
        result.symbol = symbol;
        const std::string meta = "Time Series (Daily)";
        if (jsonData.contains(meta)) {
            for (auto& [date, data] : jsonData[meta].items()) {
                DailyBar bar;
                bar.open   = std::stod(data["1. open"].get<std::string>());
                bar.high   = std::stod(data["2. high"].get<std::string>());
                bar.low    = std::stod(data["3. low"].get<std::string>());
                bar.close  = std::stod(data["4. close"].get<std::string>());
                bar.volume = std::stol(data["5. volume"].get<std::string>());
                result.bars[date] = bar;
            }
        }
        return result;
    }
};

#endif // TIME_SERIES_DATA_HPP
