#include "av_ts_client_intraday.hpp"

AlphaVantageTimeSeriesClientIntraday::AlphaVantageTimeSeriesClientIntraday(
    const std::string& apiKey,
    const std::string& symbol, 
    const std::string& interval, 
    const std::string& adjusted,
    const std::string& extended_hours,
    const std::string& month,
    const std::string& entitlement) :
        
    //Call the base class constructor to initialize the common member variables
    AlphaVantageTimeSeriesClient("TIME_SERIES_INTRADAY", apiKey, symbol),
    interval(interval),
    adjusted(adjusted), 
    extended_hours(extended_hours),
    month(month),
    entitlement(entitlement){};