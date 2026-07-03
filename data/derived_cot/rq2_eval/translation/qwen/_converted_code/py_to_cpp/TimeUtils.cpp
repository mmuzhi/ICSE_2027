#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <cmath>
#include <stdexcept>

class TimeUtils {
private:
    std::chrono::system_clock::time_point m_timePoint;

    static std::chrono::system_clock::time_point string_to_time_point(const std::string& str) {
        std::tm time_tm = {};
        std::istringstream ss(str);
        ss >> std::get_time(&time_tm, "%Y-%m-%d %H:%M:%S");
        if (ss.fail() || ss.get() != '\0') {
            throw std::runtime_error("Invalid datetime format");
        }
        return std::chrono::system_clock::from_time_t(std::mktime(&time_tm));
    }

    static std::string time_point_to_string(const std::chrono::system_clock::time_point& tp) {
        std::time_t tt = std::chrono::system_clock::to_time_t(tp);
        std::tm time_tm = *std::localtime(&tt);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &time_tm);
        return std::string(buffer);
    }

    static int get_minutes_between_time_points(const std::chrono::system_clock::time_point& time1, const std::chrono::system_clock::time_point& time2) {
        auto duration_seconds = std::chrono::duration_cast<std::chrono::seconds>(time2 - time1).count();
        auto seconds_part = duration_seconds % (3600 * 24);
        return static_cast<int>(std::round(static_cast<double>(seconds_part) / 60));
    }

public:
    TimeUtils() : m_timePoint(std::chrono::system_clock::now()) {}

    std::string get_current_time() {
        auto now = m_timePoint;
        std::time_t tt = std::chrono::system_clock::to_time_t(now);
        std::tm time_tm = *std::localtime(&tt);
        char buffer[9];
        std::strftime(buffer, sizeof(buffer), "%H:%M:%S", &time_tm);
        return std::string(buffer);
    }

    std::string get_current_date() {
        auto now = m_timePoint;
        std::time_t tt = std::chrono::system_clock::to_time_t(now);
        std::tm time_tm = *std::localtime(&tt);
        char buffer[11];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &time_tm);
        return std::string(buffer);
    }

    std::string add_seconds(int seconds) {
        auto new_time = m_timePoint + std::chrono::seconds(seconds);
        return time_point_to_string(new_time);
    }

    std::chrono::system_clock::time_point string_to_datetime(const std::string& string) {
        return string_to_time_point(string);
    }

    std::string datetime_to_string(const std::chrono::system_clock::time_point& datetime) {
        return time_point_to_string(datetime);
    }

    int get_minutes(const std::string& string_time1, const std::string& string_time2) {
        auto time1 = string_to_time_point(string_time1);
        auto time2 = string_to_time_point(string_time2);
        return get_minutes_between_time_points(time1, time2);
    }

    std::string get_format_time(int year, int month, int day, int hour, int minute, int second) {
        std::tm time_tm = {};
        time_tm.tm_year = year - 1900;
        time_tm.tm_mon = month - 1;
        time_tm.tm_mday = day;
        time_tm.tm_hour = hour;
        time_tm.tm_min = minute;
        time_tm.tm_sec = second;
        std::chrono::system_clock::time_point tp = std::chrono::system_clock::from_time_t(std::mktime(&time_tm));
        return time_point_to_string(tp);
    }
};