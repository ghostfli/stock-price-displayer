#ifndef AV_TS_CLIENT_INTRADAY_HPP
#define AV_TS_CLIENT_INTRADAY_HPP

#include "../av_ts_client.hpp"

class AlphaVantageTimeSeriesClientIntraday : public AlphaVantageTimeSeriesClient {
    public:
        AlphaVantageTimeSeriesClientIntraday(
            const std::string& apiKey,
            const std::string& symbol, 
            const std::string& interval,
            const std::string& adjusted="true",
            const std::string& extended_hours="true",
            const std::string& month ="",
            const std::string& entitlement = ""
        );



    protected:
        std::string interval; //The interval for intraday data, e.g. 1min, 5min, 15min, 30min, 60min
        std::string adjusted; //Whether to include adjusted data (true/false)
        std::string extended_hours; //Whether to include extended hours data (true/false)
        std::string month; //The month for which to retrieve data (e.g. "2021-01" for January 2021). This is only applicable for the TIME_SERIES_INTRADAY function.
        std::string entitlement; //The entitlement level required to access the requested data. This is only applicable for the TIME_SERIES_INTRADAY function.
};

#endif // AV_TS_CLIENT_INTRADAY_HPP