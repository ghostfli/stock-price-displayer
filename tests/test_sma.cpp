#include <cassert>
#include <cmath>
#include <iostream>
#include "../src/analysis/sma.hpp"

static TimeSeriesData makeTS(const std::vector<std::pair<std::string, double>>& closes) {
    TimeSeriesData ts;
    ts.symbol = "TEST";
    for (const auto& [date, close] : closes)
        ts.bars[date] = DailyBar{0, 0, 0, close, 0};
    return ts;
}

static bool near(double a, double b) { return std::fabs(a - b) < 1e-9; }

int main() {
    // Basic 3-day SMA over 5 bars
    {
        auto ts = makeTS({
            {"2026-01-01", 10.0},
            {"2026-01-02", 20.0},
            {"2026-01-03", 30.0},
            {"2026-01-04", 40.0},
            {"2026-01-05", 50.0},
        });
        auto result = sma(ts, 3);
        assert(result.size() == 3);
        assert(near(result.at("2026-01-03"), 20.0)); // (10+20+30)/3
        assert(near(result.at("2026-01-04"), 30.0)); // (20+30+40)/3
        assert(near(result.at("2026-01-05"), 40.0)); // (30+40+50)/3
    }

    // Window == 1: result equals input
    {
        auto ts = makeTS({{"2026-01-01", 5.0}, {"2026-01-02", 7.0}});
        auto result = sma(ts, 1);
        assert(result.size() == 2);
        assert(near(result.at("2026-01-01"), 5.0));
        assert(near(result.at("2026-01-02"), 7.0));
    }

    // Window larger than data: no results
    {
        auto ts = makeTS({{"2026-01-01", 1.0}, {"2026-01-02", 2.0}});
        auto result = sma(ts, 5);
        assert(result.empty());
    }

    // Invalid window throws
    {
        auto ts = makeTS({{"2026-01-01", 1.0}});
        bool threw = false;
        try { sma(ts, 0); } catch (const std::invalid_argument&) { threw = true; }
        assert(threw);
    }

    std::cout << "All SMA tests passed.\n";
}
