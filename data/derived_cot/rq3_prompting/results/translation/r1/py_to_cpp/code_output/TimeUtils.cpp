#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <cstring>

class TimeUtils {
public:
    TimeUtils() : datetime(std::chrono::system_clock::now()) {}

    std::string get_current_time() {
        std::tm local_tm = to_tm(datetime);
        return format_time(local_tm, "%H:%M:%S");
    }

    std::string get_current_date() {
        std::tm local_tm = to_tm(datetime);
        return format_time(local_tm, "%Y-%m-%d");
    }

    std::string add_seconds(int seconds) {
        auto new_tp = datetime + std::chrono::seconds(seconds);
        std::tm local_tm = to_tm(new_tp);
        return format_time(local_tm, "%H:%M:%S");
    }

    std::chrono::system_clock::time_point string_to_datetime(const std::string& str) {
        std::tm tm = {};
        std::istringstream ss(str);
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
        time_t tt = std::mktime(&tm);
        return std::chrono::system_clock::from_time_t(tt);
    }

    std::string datetime_to_string(const std::chrono::system_clock::time_point& dt) {
        std::tm local_tm = to_tm(dt);
        return format_time(local_tm, "%Y-%m-%d %H:%M:%S");
    }

    int get_minutes(const std::string& string_time1, const std::string& string_time2) {
        auto tp1 = string_to_datetime(string_time1);
        auto tp2 = string_to_datetime(string_time2);
        auto diff = tp2 - tp1;
        // replicate Python's timedelta.seconds (always between 0 and 86399)
        long long total_sec = std::chrono::duration_cast<std::chrono::seconds>(diff).count();
        long long sec_mod = total_sec % 86400;
        if (sec_mod < 0) sec_mod += 86400;
        double minutes = sec_mod / 60.0;
        return py_round(minutes);
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
        time_t tt = std::mktime(&tm);
        auto tp = std::chrono::system_clock::from_time_t(tt);
        return datetime_to_string(tp);
    }

private:
    std::chrono::system_clock::time_point datetime;

    static std::tm to_tm(const std::chrono::system_clock::time_point& tp) {
        time_t tt = std::chrono::system_clock::to_time_t(tp);
        std::tm result;
        memcpy(&result, std::localtime(&tt), sizeof(std::tm));
        return result;
    }

    static std::string format_time(const std::tm& tm, const std::string& fmt) {
        char buf[64];
        strftime(buf, sizeof(buf), fmt.c_str(), &tm);
        return std::string(buf);
    }

    static int py_round(double x) {
        double y = std::floor(x);
        double frac = x - y;
        if (frac < 0.5) return static_cast<int>(y);
        if (frac > 0.5) return static_cast<int>(y) + 1;
        // frac == 0.5: round half to even
        int y_int = static_cast<int>(y);
        return (y_int % 2 == 0) ? y_int : y_int + 1;
    }
};

// Note: The code below is not part of the translation, only for potential testing.
// #include <iostream>
// int main() {
//     TimeUtils tu;
//     std::cout << tu.get_current_time() << std::endl;
//     std::cout << tu.get_current_date() << std::endl;
//     std::cout << tu.add_seconds(600) << std::endl;
//     auto dt = tu.string_to_datetime("2001-7-18 1:1:1");
//     std::cout << tu.datetime_to_string(dt) << std::endl;
//     std::cout << tu.get_minutes("2001-7-18 1:1:1", "2001-7-18 2:1:1") << std::endl;
//     std::cout << tu.get_format_time(2001, 7, 18, 1, 1, 1) << std::endl;
//     return 0;
// }