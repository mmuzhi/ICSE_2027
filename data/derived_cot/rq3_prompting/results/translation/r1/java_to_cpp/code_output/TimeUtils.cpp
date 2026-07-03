#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cstdio>
#include <cmath>
#include <climits>

class TimeUtils {
public:
    TimeUtils() : datetime(std::chrono::system_clock::now()) {}

    std::string getCurrentTime() {
        return format(datetime, "%H:%M:%S");
    }

    std::string getCurrentDate() {
        return format(datetime, "%Y-%m-%d");
    }

    std::string addSeconds(int seconds) {
        auto new_tp = datetime + std::chrono::seconds(seconds);
        return format(new_tp, "%H:%M:%S");
    }

    std::chrono::system_clock::time_point stringToDatetime(const std::string& str) {
        int y, m, d, h, min, sec;
        if (std::sscanf(str.c_str(), "%d-%d-%d %d:%d:%d", &y, &m, &d, &h, &min, &sec) != 6) {
            throw std::invalid_argument("Invalid date-time format: " + str);
        }
        std::tm tm = {};
        tm.tm_year = y - 1900;
        tm.tm_mon = m - 1;
        tm.tm_mday = d;
        tm.tm_hour = h;
        tm.tm_min = min;
        tm.tm_sec = sec;
        tm.tm_isdst = -1;
        std::time_t t = std::mktime(&tm);
        if (t == static_cast<std::time_t>(-1)) {
            throw std::runtime_error("Failed to convert to time_t");
        }
        return std::chrono::system_clock::from_time_t(t);
    }

    std::string datetimeToString(const std::chrono::system_clock::time_point& dt) {
        return format(dt, "%Y-%m-%d %H:%M:%S");
    }

    int getMinutes(const std::string& stringTime1, const std::string& stringTime2) {
        auto tp1 = stringToDatetime(stringTime1);
        auto tp2 = stringToDatetime(stringTime2);
        auto diff_sec = std::chrono::duration_cast<std::chrono::seconds>(tp2 - tp1).count();

        // Floor division to match Java's ChronoUnit.MINUTES.between (floor toward negative infinity)
        long minutes;
        if (diff_sec < 0) {
            minutes = (diff_sec - 59) / 60;
        } else {
            minutes = diff_sec / 60;
        }

        // Replicate Math.round(minutes) then Math.toIntExact
        double rounded = std::round(static_cast<double>(minutes));
        if (rounded > INT_MAX || rounded < INT_MIN) {
            throw std::overflow_error("Minutes out of int range");
        }
        return static_cast<int>(rounded);
    }

    std::string getFormatTime(int year, int month, int day, int hour, int minute, int second) {
        std::tm tm = {};
        tm.tm_year = year - 1900;
        tm.tm_mon = month - 1;
        tm.tm_mday = day;
        tm.tm_hour = hour;
        tm.tm_min = minute;
        tm.tm_sec = second;
        tm.tm_isdst = -1;
        std::time_t t = std::mktime(&tm);
        if (t == static_cast<std::time_t>(-1)) {
            throw std::runtime_error("Failed to create time point");
        }
        auto tp = std::chrono::system_clock::from_time_t(t);
        return format(tp, "%Y-%m-%d %H:%M:%S");
    }

private:
    std::chrono::system_clock::time_point datetime;

    std::string format(const std::chrono::system_clock::time_point& tp, const std::string& fmt) {
        std::time_t t = std::chrono::system_clock::to_time_t(tp);
        std::tm* local = std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(local, fmt.c_str());
        return oss.str();
    }
};