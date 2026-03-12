#include "av_ts_client_daily.hpp"

AlphaVantageTimeSeriesClientDaily::AlphaVantageTimeSeriesClientDaily(
            const std::string& apiKey,
            const std::string& symbol, 
            const std::string& output_size,
            const std::string& datatype
        ) : 
        //Call the base class constructor to initialize the common member variables
        AlphaVantageTimeSeriesClient("TIME_SERIES_DAILY", apiKey, symbol, output_size, datatype) {
    url = constructURL();
};