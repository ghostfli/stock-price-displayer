#ifndef AV_TS_CLIENT_HPP
#define AV_TS_CLIENT_HPP

#include <string>
#include <map>

//Static map to determine if a function is premium or not. This can be used to determine if we need to include the interval and output_size parameters in the URL construction.
static std::map<std::string, bool> FunctionIsPremium = {
    {"TIME_SERIES_INTRADAY", true},
    {"TIME_SERIES_DAILY", false},
    {"TIME_SERIES_DAILY_ADJUSTED", true},
    {"TIME_SERIES_WEEKLY", false},
    {"TIME_SERIES_WEEKLY_ADJUSTED", false},
    {"TIME_SERIES_MONTHLY", false},
    {"TIME_SERIES_MONTHLY_ADJUSTED", false},
};

class AlphaVantageTimeSeriesClient {
    protected:
        //Member variables
        std::string function; //The function to call, e.g. TIME_SERIES_DAILY, TIME_SERIES_INTRADAY, etc.
        std::string apiKey; //The API key to use for the request. This should be stored securely in a real application, e.g. in an environment variable or a secure vault.
        std::string symbol; //The stock symbol to query, e.g. AAPL, MSFT, etc.  
        std::string output_size; //The size of the output, either "compact" (the latest 100 data points) or "full" (the full-length time series).
        std::string datatype; //The format of the response, either "json" or "csv".
    
    public:
        std::string url;

        AlphaVantageTimeSeriesClient(
            const std::string&function, 
            const std::string& apiKey, 
            const std::string& symbol, 
            const std::string& output_size="compact", 
            const std::string& datatype="json");
            
        virtual std::string constructURL() const;
};

#endif //AV_TS_CLIENT_HPP