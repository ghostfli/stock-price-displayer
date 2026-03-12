#include "av_ts_client.hpp"

AlphaVantageTimeSeriesClient::AlphaVantageTimeSeriesClient(
            const std::string& function, 
            const std::string& apiKey, 
            const std::string& symbol, 
            const std::string& output_size,
            const std::string& datatype) :
            function(function),
            apiKey(apiKey),
            symbol(symbol),
            output_size(output_size),
            datatype(datatype){};


std::string AlphaVantageTimeSeriesClient::constructURL() const {
    return "https://www.alphavantage.co/query?function=" + function + "&symbol="
            + symbol + "&output_size=" + output_size + "&datatype=" + datatype + "&apikey=" + apiKey;
};