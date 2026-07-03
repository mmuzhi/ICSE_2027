#include <chrono>
#include <ctime>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>

class TimeUtils {
private:
    std::chrono::system_clock::time_point datetime;

    // Helper function to convert time_point to a tm structure
    std::tm time_point_to_tm(const std::chrono::system_clock::time_point& tp) {
        std::time_t tt = std::chrono::system_clock::to_time_t(tp);
        std::tm tm_buf;
        std::memset(&tm_buf, 0, sizeof(std::tm));
        localtime_r(&tt, &tm_buf);
        return tm_buf;
    }

    // Helper function to convert tm to a time_point
    std::chrono::system_clock::time_point tm_to_time_point(const std::tm& tm_buf) {
        std::time_t tt = std::mktime(const_cast<std::tm*>(&tm_buf));
        return std::chrono::system_clock::from_time_t(tt);
    }

public:
    TimeUtils() {
        this->datetime = std::chrono::system_clock::now();
    }

    std::string get_current_time() {
        std::tm tm_buf = time_point_to_tm(datetime);
        char buffer[9];
        std::strftime(buffer, sizeof(buffer), "%H:%M:%S", &tm_buf);
        return std::string(buffer);
    }

    std::string get_current_date() {
        std::tm tm_buf = time_point_to_tm(datetime);
        char buffer[11];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tm_buf);
        return std::string(buffer);
    }

    std::string add_seconds(int seconds) {
        std::tm tm_buf = time_point_to_tm(datetime);
        tm_buf.tm_sec += seconds;
        // Normalize time structure
        auto normalized = std::localtime(&tm_buf);
        std::tm result = *normalized;
        return get_current_time(); // Reuses formatting logic
    }

    std::chrono::system_clock::time_point string_to_datetime(const std::string& string) {
        std::tm tm_buf = {};
        char format[] = "%Y-%m-%d %H:%M:%S";
        char buf[20];
        snprintf(buf, sizeof(buf), string.c_str());
        std::strptime(buf, format, &tm_buf);
        return tm_to_time_point(tm_buf);
    }

    std::string datetime_to_string(const std::chrono::system_clock::time_point& datetime) {
        std::tm tm_buf = time_point_to_tm(datetime);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm_buf);
        return std::string(buffer);
    }

    int get_minutes(const std::string& stringTime1, const std::string& stringTime2) {
        auto time1 = string_to_datetime(stringTime1);
        auto time2 = string_to_datetime(stringTime2);
        std::tm tm1 = time_point_to_tm(time1);
        std::tm tm2 = time_point_to_tm(time2);
        std::time_t t1 = std::mktime(const_cast<std::tm*>(&tm1));
        std::time_t t2 = std::mktime(const_cast<std::tm*>(&tm2));
        double minutes = std::difftime(t2, t1) / 60.0;
        return static_cast<int>(std::round(minutes));
    }

    std::string get_format_time(int year, int month, int day, int hour, int minute, int second) {
        std::tm tm_buf = {};
        tm_buf.tm_year = year - 1900;
        tm_buf.tm_mon = month - 1;
        tm_buf.tm_mday = day;
        tm_buf.tm_hour = hour;
        tm_buf.tm_min = minute;
        tm_buf.tm_sec = second;
        std::time_t tt = std::mktime(const_cast<std::tm*>(&tm_buf));
        if (tt == -1) throw std::runtime_error("Invalid date/time");
        return datetimeToString(std::chrono::system_clock::from_time_t(tt));
    }
};