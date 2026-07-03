#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>

class TimeUtils {
private:
    std::chrono::system_clock::time_point initial_time_point;

    std::tm time_point_to_tm(const std::chrono::system_clock::time_point& tp) {
        std::time_t t = std::chrono::system_clock::to_time_t(tp);
        std::tm tm_result;
#if defined(_WIN32)
        localtime_s(&tm_result, &t);
#else
        localtime_r(&t, &tm_result);
#endif
        return tm_result;
    }

    std::string format_time_point(const std::chrono::system_clock::time_point& tp, const char* fmt) {
        std::tm tm_result = time_point_to_tm(tp);
        std::ostringstream oss;
        oss << std::put_time(&tm_result, fmt);
        return oss.str();
    }

public:
    TimeUtils() : initial_time_point(std::chrono::system_clock::now()) {}

    std::string get_current_time() {
        return format_time_point(initial_time_point, "%H:%M:%S");
    }

    std::string get_current_date() {
        return format_time_point(initial_time_point, "%Y-%m-%d");
    }

    std::string add_seconds(int seconds) {
        auto new_time_point = initial_time_point + std::chrono::seconds(seconds);
        return format_time_point(new_time_point, "%H:%M:%S");
    }

    std::chrono::system_clock::time_point string_to_datetime(const std::string& s) {
        std::tm tm = {};
        std::istringstream ss(s);
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
        if (ss.fail()) {
            throw std::runtime_error("Failed to parse time string: " + s);
        }
        tm.tm_isdst = -1;
        std::time_t t = std::mktime(&tm);
        return std::chrono::system_clock::from_time_t(t);
    }

    std::string datetime_to_string(const std::chrono::system_clock::time_point& tp) {
        return format_time_point(tp, "%Y-%m-%d %H:%M:%S");
    }

    long get_minutes(const std::string& string_time1, const std::string& string_time2) {
        auto time1 = string_to_datetime(string_time1);
        auto time2 = string_to_datetime(string_time2);
        auto diff = time2 - time1;
        long long diff_seconds = std::chrono::duration_cast<std::chrono::seconds>(diff).count();
        long long seconds_mod = diff_seconds % 86400;
        if (seconds_mod < 0) {
            seconds_mod += 86400;
        }
        double minutes = static_cast<double>(seconds_mod) / 60.0;
        return static_cast<long>(std::round(minutes));
    }

    std::string get_format_time(int year, int month, int day, int hour, int minute, int second) {
        std::tm tm = {};
        tm.tm_year = year - 1900;
        tm.tm_mon = month - 1;
        tm.tm_mday = day;
        tm.tm_hour = hour;
        tm.tm_min = minute;
        tm.tm_sec = second;
        tm.tm_isdst = -1;
        std::mktime(&tm);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
};