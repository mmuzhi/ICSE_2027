#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <ctime>

class TimeUtils {
private:
    std::chrono::system_clock::time_point datetime;

    std::string formatTime(const std::chrono::system_clock::time_point& tp, const std::string& format) {
        std::time_t tt = std::chrono::system_clock::to_time_t(tp);
        std::tm tm_buffer = *std::localtime(&tt);
        char buffer[100];
        std::strftime(buffer, sizeof(buffer), format.c_str(), &tm_buffer);
        return std::string(buffer);
    }

public:
    TimeUtils() {
        datetime = std::chrono::system_clock::now();
    }

    std::string getCurrentTime() {
        return formatTime(datetime, "%H:%M:%S");
    }

    std::string getCurrentDate() {
        return formatTime(datetime, "%Y-%m-%d");
    }

    std::string addSeconds(int seconds) {
        std::chrono::system_clock::time_point new_datetime = datetime + std::chrono::seconds(seconds);
        return formatTime(new_datetime, "%H:%M:%S");
    }

    std::chrono::system_clock::time_point stringToDatetime(const std::string& str) {
        std::istringstream ss(str);
        int year, month, day, hour, minute, second;
        char c1, c2, c3, c4;

        ss >> year;
        ss >> c1;
        ss >> month;
        ss >> c2;
        ss >> day;
        ss >> hour;
        ss >> c3;
        ss >> minute;
        ss >> c4;
        ss >> second;

        if (c1 != '-' || c2 != '-' || c3 != ':' || c4 != ':') {
            throw std::runtime_error("Invalid format in stringToDatetime");
        }

        std::tm tm_buffer = {};
        tm_buffer.tm_year = year - 1900;
        tm_buffer.tm_mon = month - 1;
        tm_buffer.tm_mday = day;
        tm_buffer.tm_hour = hour;
        tm_buffer.tm_min = minute;
        tm_buffer.tm_sec = second;

        std::time_t tt = std::mktime(&tm_buffer);
        if (tt == std::time_t(-1)) {
            throw std::runtime_error("Invalid date/time");
        }

        return std::chrono::system_clock::from_time_t(tt);
    }

    std::string datetimeToString(const std::chrono::system_clock::time_point& datetime) {
        return formatTime(datetime, "%Y-%m-%d %H:%M:%S");
    }

    int getMinutes(const std::string& str1, const std::string& str2) {
        auto time1 = stringToDatetime(str1);
        auto time2 = stringToDatetime(str2);
        auto duration_seconds = std::chrono::duration_cast<std::chrono::seconds>(time2 - time1);
        auto total_seconds = duration_seconds.count();
        auto minutes = static_cast<int>(std::round(static_cast<double>(total_seconds) / 60));
        return minutes;
    }

    std::string getFormatTime(int year, int month, int day, int hour, int minute, int second) {
        std::tm tm_buffer = {};
        tm_buffer.tm_year = year - 1900;
        tm_buffer.tm_mon = month - 1;
        tm_buffer.tm_mday = day;
        tm_buffer.tm_hour = hour;
        tm_buffer.tm_min = minute;
        tm_buffer.tm_sec = second;

        std::time_t tt = std::mktime(&tm_buffer);
        if (tt == std::time_t(-1)) {
            throw std::runtime_error("Invalid date/time");
        }

        return formatTime(std::chrono::system_clock::from_time_t(tt), "%Y-%m-%d %H:%M:%S");
    }
};