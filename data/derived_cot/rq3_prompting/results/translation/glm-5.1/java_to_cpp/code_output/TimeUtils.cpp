#pragma once

#include <chrono>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <cstring>

class TimeUtils {
public:
    std::tm datetime;

    TimeUtils() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        datetime = *std::localtime(&now_time);
    }

    std::string getCurrentTime() {
        std::ostringstream oss;
        oss << std::put_time(&datetime, "%H:%M:%S");
        return oss.str();
    }

    std::string getCurrentDate() {
        std::ostringstream oss;
        oss << std::put_time(&datetime, "%Y-%m-%d");
        return oss.str();
    }

    std::string addSeconds(int seconds) {
        std::time_t t = std::mktime(&datetime);
        t += seconds;
        std::tm newDatetime = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&newDatetime, "%H:%M:%S");
        return oss.str();
    }

    std::tm stringToDatetime(const std::string& str) {
        std::tm tm = {};
        int year, month, day, hour, minute, second;
        if (std::sscanf(str.c_str(), "%d-%d-%d %d:%d:%d",
                        &year, &month, &day, &hour, &minute, &second) == 6) {
            tm.tm_year = year - 1900;
            tm.tm_mon = month - 1;
            tm.tm_mday = day;
            tm.tm_hour = hour;
            tm.tm_min = minute;
            tm.tm_sec = second;
            tm.tm_isdst = -1;
            std::mktime(&tm);
        }
        return tm;
    }

    std::string datetimeToString(const std::tm& dt) {
        std::tm copy = dt;
        std::ostringstream oss;
        oss << std::put_time(&copy, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    int getMinutes(const std::string& stringTime1, const std::string& stringTime2) {
        std::tm time1 = stringToDatetime(stringTime1);
        std::tm time2 = stringToDatetime(stringTime2);
        std::time_t t1 = std::mktime(&time1);
        std::time_t t2 = std::mktime(&time2);
        double seconds = std::difftime(t2, t1);
        long minutes = static_cast<long>(seconds) / 60;
        return static_cast<int>(minutes);
    }

    std::string getFormatTime(int year, int month, int day, int hour, int minute, int second) {
        std::tm timeItem = {};
        timeItem.tm_year = year - 1900;
        timeItem.tm_mon = month - 1;
        timeItem.tm_mday = day;
        timeItem.tm_hour = hour;
        timeItem.tm_min = minute;
        timeItem.tm_sec = second;
        timeItem.tm_isdst = -1;
        std::ostringstream oss;
        oss << std::put_time(&timeItem, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
};