#ifndef AV_TS_CLIENT_DAILY_HPP
#define AV_TS_CLIENT_DAILY_HPP

#include "../av_ts_client.hpp"

class AlphaVantageTimeSeriesClientDaily : public AlphaVantageTimeSeriesClient {
    public:
        AlphaVantageTimeSeriesClientDaily(
            const std::string& apiKey,
            const std::string& symbol, 
            const std::string& output_size="compact",
            const std::string& datatype="json"
        );
};

#endif //AV_TS_CLIENT_DAILY_HPP