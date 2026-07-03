#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <ctime>
#include <chrono>

class TimeUtils {
private:
    std::chrono::system_clock::time_point m_timePoint;

    // Helper to convert time_point to tm (local time)
    std::tm to_tm() const {
        std::tm tm_time = {};
        std::chrono::system_clock::time_point pt = m_timePoint;
        std::time_t tt = std::chrono::system_clock::to_time_t(pt);
        localtime_r(&tt, &tm_time);
        return tm_time;
    }

public:
    TimeUtils() : m_timePoint(std::chrono::system_clock::now()) {}

    std::string get_current_time() {
        std::tm tm_time = to_tm();
        char buffer[9];
        std::strftime(buffer, sizeof(buffer), "%H:%M:%S", &tm_time);
        return std::string(buffer);
    }

    std::string get_current_date() {
        std::tm tm_time = to_tm();
        char buffer[10];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tm_time);
        return std::string(buffer);
    }

    std::string add_seconds(int seconds) {
        std::chrono::seconds sec(seconds);
        std::chrono::system_clock::time_point new_time_point = m_timePoint + sec;
        std::tm tm_time = {};
        std::time_t tt = std::chrono::system_clock::to_time_t(new_time_point);
        localtime_r(&tt, &tm_time);
        char buffer[9];
        std::strftime(buffer, sizeof(buffer), "%H:%M:%S", &tm_time);
        return std::string(buffer);
    }

    std::chrono::system_clock::time_point string_to_datetime(const std::string& input) {
        std::tm tm_time = {};
        std::istringstream ss(input);
        ss >> std::get_time(&tm_time, "%Y-%m-%d %H:%M:%S");
        return std::chrono::system_clock::from_time_t(std::mktime(&tm_time));
    }

    std::string datetime_to_string(const std::chrono::system_clock::time_point& tp) {
        std::tm tm_time = {};
        std::time_t tt = std::chrono::system_clock::to_time_t(tp);
        localtime_r(&tt, &tm_time);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm_time);
        return std::string(buffer);
    }

    int get_minutes(const std::string& time_str1, const std::string& time_str2) {
        auto time1 = string_to_datetime(time_str1);
        auto time2 = string_to_datetime(time_str2);
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(time2 - time1);
        double total_seconds = duration.count();
        return static_cast<int>(std::round(total_seconds / 60.0));
    }

    std::string get_format_time(int year, int month, int day, int hour, int minute, int second) {
        std::tm tm_time = {};
        tm_time.tm_year = year - 1900;
        tm_time.tm_mon = month - 1;
        tm_time.tm_mday = day;
        tm_time.tm_hour = hour;
        tm_time.tm_min = minute;
        tm_time.tm_sec = second;
        std::time_t tt = std::mktime(&tm_time);
        return datetime_to_string(std::chrono::system_clock::from_time_t(tt));
    }
};

int main() {
    TimeUtils timeutils;
    std::cout << "Current Time: " << timeutils.get_current_time() << std::endl;
    std::cout << "Current Date: " << timeutils.get_current_date() << std::endl;
    std::cout << "After 600 seconds: " << timeutils.add_seconds(600) << std::endl;
    std::cout << "String to datetime: " << timeutils.string_to_datetime("2001-7-18 1:1:1") << std::endl;
    std::cout << "Datetime to string: " << timeutils.datetime_to_string(timeutils.m_timePoint) << std::endl;
    std::cout << "Minutes between times: " << timeutils.get_minutes("2001-7-18 1:1:1", "2001-7-18 2:1:1") << std::endl;
    std::cout << "Formatted time: " << timeutils.get_format_time(2001, 7, 18, 1, 1, 1) << std::endl;
    return 0;
}