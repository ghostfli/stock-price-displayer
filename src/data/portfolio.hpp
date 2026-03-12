#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP

#include <string>
#include <map>
#include "time_series_data.hpp"

struct Position {
    TimeSeriesData  tsData;
    double          shares;      // number of shares held
    double          avgCost;     // average cost per share (cost basis)

    double marketValue(const std::string& date) const {
        return shares * tsData.bars.at(date).close;
    }

    double unrealizedGain(const std::string& date) const {
        return marketValue(date) - (shares * avgCost);
    }
};

struct Portfolio {
    std::map<std::string, Position> positions; // key = symbol e.g. "AAPL"

    void add(const TimeSeriesData& tsData, double shares, double avgCost) {
        positions[tsData.symbol] = {tsData, shares, avgCost};
    }

    bool contains(const std::string& symbol) const {
        return positions.count(symbol) > 0;
    }

    const Position& get(const std::string& symbol) const {
        return positions.at(symbol);
    }
};

#endif // PORTFOLIO_HPP
