#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdio>

class TimeUtils {
public:
    TimeUtils() {
        datetime = std::chrono::system_clock::now();
    }

    std::string get_current_time() {
        auto time_t_val = std::chrono::system_clock::to_time_t(datetime);
        std::tm tm_val = *std::localtime(&time_t_val);
        std::ostringstream oss;
        oss << std::put_time(&tm_val, "%H:%M:%S");
        return oss.str();
    }

    std::string get_current_date() {
        auto time_t_val = std::chrono::system_clock::to_time_t(datetime);
        std::tm tm_val = *std::localtime(&time_t_val);
        std::ostringstream oss;
        oss << std::put_time(&tm_val, "%Y-%m-%d");
        return oss.str();
    }

    std::string add_seconds(int seconds) {
        auto new_datetime = datetime + std::chrono::seconds(seconds);
        auto time_t_val = std::chrono::system_clock::to_time_t(new_datetime);
        std::tm tm_val = *std::localtime(&time_t_val);
        std::ostringstream oss;
        oss << std::put_time(&tm_val, "%H:%M:%S");
        return oss.str();
    }

    std::tm string_to_datetime(const std::string& str) {
        std::tm tm_val = {};
        int year, month, day, hour, minute, second;
        std::sscanf(str.c_str(), "%d-%d-%d %d:%d:%d",
                    &year, &month, &day, &hour, &minute, &second);
        tm_val.tm_year = year - 1900;
        tm_val.tm_mon = month - 1;
        tm_val.tm_mday = day;
        tm_val.tm_hour = hour;
        tm_val.tm_min = minute;
        tm_val.tm_sec = second;
        tm_val.tm_isdst = -1;
        std::mktime(&tm_val);
        return tm_val;
    }

    std::string datetime_to_string(const std::tm& dt) {
        std::tm tm_val = dt;
        std::ostringstream oss;
        oss << std::put_time(&tm_val, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    int get_minutes(const std::string& string_time1, const std::string& string_time2) {
        std::tm tm1 = string_to_datetime(string_time1);
        std::tm tm2 = string_to_datetime(string_time2);
        std::time_t t1 = std::mktime(&tm1);
        std::time_t t2 = std::mktime(&tm2);
        long long total_seconds = static_cast<long long>(std::difftime(t2, t1));
        // Python's timedelta.seconds gives seconds component (0–86399), not total
        long long seconds_part = ((total_seconds % 86400) + 86400) % 86400;
        return static_cast<int>(std::round(static_cast<double>(seconds_part) / 60.0));
    }

    std::string get_format_time(int year, int month, int day, int hour, int minute, int second) {
        std::tm tm_val = {};
        tm_val.tm_year = year - 1900;
        tm_val.tm_mon = month - 1;
        tm_val.tm_mday = day;
        tm_val.tm_hour = hour;
        tm_val.tm_min = minute;
        tm_val.tm_sec = second;
        tm_val.tm_isdst = -1;
        std::mktime(&tm_val);
        std::ostringstream oss;
        oss << std::put_time(&tm_val, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

private:
    std::chrono::system_clock::time_point datetime;
};