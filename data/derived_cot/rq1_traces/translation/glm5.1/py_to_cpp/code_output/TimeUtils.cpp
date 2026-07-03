#include <ctime>
#include <string>
#include <cmath>
#include <cstdio>

class TimeUtils {
private:
    static std::tm get_now() {
        std::time_t now = std::time(nullptr);
        return *std::localtime(&now);
    }

    static std::tm parse_datetime(const std::string& str) {
        std::tm tm = {};
        std::sscanf(str.c_str(), "%d-%d-%d %d:%d:%d",
                    &tm.tm_year, &tm.tm_mon, &tm.tm_mday,
                    &tm.tm_hour, &tm.tm_min, &tm.tm_sec);
        tm.tm_year -= 1900;
        tm.tm_mon -= 1;
        tm.tm_isdst = -1;
        std::mktime(&tm);
        return tm;
    }

    static std::string format_datetime(const std::tm& tm, const std::string& fmt) {
        char buf[64];
        std::strftime(buf, sizeof(buf), fmt.c_str(), &tm);
        return std::string(buf);
    }

    // Python-style floor division (differs from C++ truncation for negative values)
    static long floor_div(long a, long b) {
        long d = a / b;
        long r = a % b;
        if (r != 0 && ((a < 0) ^ (b < 0))) d--;
        return d;
    }

    // Python's round() uses banker's rounding (round half to even)
    static long long py_round(double x) {
        double abs_x = std::abs(x);
        double frac = abs_x - std::floor(abs_x);
        long long int_part = static_cast<long long>(std::floor(abs_x));

        long long abs_result;
        if (frac < 0.5) {
            abs_result = int_part;
        } else if (frac > 0.5) {
            abs_result = int_part + 1;
        } else {
            // Exactly halfway: round to even
            abs_result = (int_part % 2 == 0) ? int_part : int_part + 1;
        }

        return (x < 0) ? -abs_result : abs_result;
    }

public:
    std::tm datetime;

    TimeUtils() : datetime(get_now()) {}

    std::string get_current_time() {
        return format_datetime(datetime, "%H:%M:%S");
    }

    std::string get_current_date() {
        return format_datetime(datetime, "%Y-%m-%d");
    }

    std::string add_seconds(int seconds) {
        std::tm new_tm = datetime;
        new_tm.tm_isdst = -1;
        std::time_t t = std::mktime(&new_tm);
        t += seconds;
        new_tm = *std::localtime(&t);
        return format_datetime(new_tm, "%H:%M:%S");
    }

    std::tm string_to_datetime(const std::string& str) {
        return parse_datetime(str);
    }

    std::string datetime_to_string(const std::tm& dt) {
        return format_datetime(dt, "%Y-%m-%d %H:%M:%S");
    }

    int get_minutes(const std::string& string_time1, const std::string& string_time2) {
        std::tm tm1 = parse_datetime(string_time1);
        std::tm tm2 = parse_datetime(string_time2);
        tm1.tm_isdst = -1;
        tm2.tm_isdst = -1;
        std::time_t t1 = std::mktime(&tm1);
        std::time_t t2 = std::mktime(&tm2);
        double diff = std::difftime(t2, t1);
        long total_seconds = static_cast<long>(diff);
        // Replicate Python's timedelta.seconds (only the within-day component, 0–86399)
        long days = floor_div(total_seconds, 86400L);
        long py_seconds = total_seconds - days * 86400L;
        return static_cast<int>(py_round(static_cast<double>(py_seconds) / 60.0));
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
        return format_datetime(tm, "%Y-%m-%d %H:%M:%S");
    }
};