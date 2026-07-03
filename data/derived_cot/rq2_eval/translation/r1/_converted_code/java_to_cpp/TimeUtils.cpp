#include <chrono>
#include <format>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <limits>

class TimeUtils {
    std::chrono::local_seconds datetime;

public:
    TimeUtils() {
        auto now = std::chrono::system_clock::now();
        auto zone = std::chrono::current_zone();
        auto local_now = zone->to_local(now);
        datetime = std::chrono::floor<std::chrono::seconds>(local_now);
    }

    std::string get_current_time() {
        return std::format("{:%H:%M:%S}", datetime);
    }

    std::string get_current_date() {
        return std::format("{:%Y-%m-%d}", datetime);
    }

    std::string add_seconds(int seconds) {
        auto new_time = datetime + std::chrono::seconds(seconds);
        return std::format("{:%H:%M:%S}", new_time);
    }

    std::chrono::local_seconds string_to_datetime(const std::string& str) {
        std::istringstream in(str);
        std::chrono::local_seconds tp;
        in >> std::chrono::parse("%Y-%m-%d %H:%M:%S", tp);
        if (in.fail()) {
            throw std::runtime_error("Failed to parse datetime string: " + str);
        }
        return tp;
    }

    std::string datetime_to_string(const std::chrono::local_seconds& datetime) {
        return std::format("{:%Y-%m-%d %H:%M:%S}", datetime);
    }

    int get_minutes(const std::string& stringTime1, const std::string& stringTime2) {
        auto time1 = string_to_datetime(stringTime1);
        auto time2 = string_to_datetime(stringTime2);
        auto diff = time2 - time1;
        auto minutes = std::chrono::duration_cast<std::chrono::minutes>(diff).count();

        if (minutes > std::numeric_limits<int>::max() || minutes < std::numeric_limits<int>::min()) {
            throw std::overflow_error("Minutes difference is too large for int");
        }
        return static_cast<int>(minutes);
    }

    std::string get_format_time(int year, int month, int day, int hour, int minute, int second) {
        using namespace std::chrono;
        year_month_day ymd{year_month_day{year/month/day}};
        if (!ymd.ok()) {
            throw std::runtime_error("Invalid date components");
        }
        local_seconds timeItem = local_days{ymd} + hours{hour} + minutes{minute} + seconds{second};
        return datetime_to_string(timeItem);
    }
};