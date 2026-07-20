#include <cstdio>
#include <string>
#include <stdexcept>
#include <limits>
#include <ctime>

// Thread-safe alternative to std::localtime
std::tm localtime_safe(const std::time_t& t) {
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    return tm;
}

// Represents a date and time without timezone, equivalent to java.time.LocalDateTime
struct DateTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

// --- Howard Hinnant's calendrical algorithms (public domain) ---
// Returns days since 1970-01-01 in the proleptic Gregorian calendar.
int days_from_civil(int y, int m, int d) noexcept {
    y -= m <= 2;
    int era = (y >= 0 ? y : y - 399) / 400;
    unsigned yoe = static_cast<unsigned>(y - era * 400);
    unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
    unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return era * 146097 + static_cast<int>(doe) - 719468;
}

// Inverse of days_from_civil
void civil_from_days(int z, int& y, int& m, int& d) noexcept {
    z += 719468;
    int era = (z >= 0 ? z : z - 146096) / 146097;
    unsigned doe = static_cast<unsigned>(z - era * 146097);
    unsigned yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
    y = static_cast<int>(yoe) + era * 400;
    unsigned doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
    unsigned mp = (5 * doy + 2) / 153;
    d = static_cast<int>(doy - (153 * mp + 2) / 5 + 1);
    m = static_cast<int>(mp + (mp < 10 ? 3 : -9));
    y += (m <= 2);
}
// --- End of calendrical algorithms ---

// Converts a DateTime to total seconds since 1970-01-01 00:00:00 (proleptic Gregorian)
long long toEpochSeconds(const DateTime& dt) {
    int days = days_from_civil(dt.year, dt.month, dt.day);
    return days * 86400LL + dt.hour * 3600LL + dt.minute * 60LL + dt.second;
}

// Converts total seconds since 1970-01-01 back to a DateTime
DateTime fromEpochSeconds(long long secs) {
    int days = static_cast<int>(secs / 86400);
    int rem = static_cast<int>(secs % 86400);
    if (rem < 0) {
        rem += 86400;
        days -= 1;
    }
    DateTime dt;
    civil_from_days(days, dt.year, dt.month, dt.day);
    dt.hour = rem / 3600;
    rem %= 3600;
    dt.minute = rem / 60;
    dt.second = rem % 60;
    return dt;
}

class TimeUtils {
    DateTime datetime;   // Captured at construction time, equivalent to LocalDateTime.now()

public:
    TimeUtils() {
        std::time_t now = std::time(nullptr);
        std::tm tm = localtime_safe(now);
        datetime.year   = tm.tm_year + 1900;
        datetime.month  = tm.tm_mon + 1;
        datetime.day    = tm.tm_mday;
        datetime.hour   = tm.tm_hour;
        datetime.minute = tm.tm_min;
        datetime.second = tm.tm_sec;
    }

    // Returns the stored time in "HH:mm:ss" format
    std::string getCurrentTime() const {
        char buf[9];
        std::snprintf(buf, sizeof(buf), "%02d:%02d:%02d",
                      datetime.hour, datetime.minute, datetime.second);
        return buf;
    }

    // Returns the stored date in "yyyy-MM-dd" format
    std::string getCurrentDate() const {
        char buf[11];
        std::snprintf(buf, sizeof(buf), "%04d-%02d-%02d",
                      datetime.year, datetime.month, datetime.day);
        return buf;
    }

    // Adds seconds to the stored datetime and returns the new time in "HH:mm:ss" format
    std::string addSeconds(int seconds) const {
        long long total = toEpochSeconds(datetime) + seconds;
        DateTime new_dt = fromEpochSeconds(total);
        char buf[9];
        std::snprintf(buf, sizeof(buf), "%02d:%02d:%02d",
                      new_dt.hour, new_dt.minute, new_dt.second);
        return buf;
    }

    // Parses a string in "yyyy-M-d H:m:s" format into a DateTime
    DateTime stringToDatetime(const std::string& string) const {
        int year, month, day, hour, minute, second;
        if (std::sscanf(string.c_str(), "%d-%d-%d %d:%d:%d",
                        &year, &month, &day, &hour, &minute, &second) != 6) {
            throw std::invalid_argument("Invalid datetime format: " + string);
        }
        // Validate ranges (matching java.time.DateTimeException)
        if (month < 1 || month > 12)
            throw std::invalid_argument("Month out of range: " + std::to_string(month));
        if (day < 1 || day > 31)
            throw std::invalid_argument("Day out of range: " + std::to_string(day));
        int maxDay = 31;
        if (month == 4 || month == 6 || month == 9 || month == 11)
            maxDay = 30;
        else if (month == 2) {
            bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            maxDay = leap ? 29 : 28;
        }
        if (day > maxDay)
            throw std::invalid_argument("Day out of range: " + std::to_string(day));
        if (hour < 0 || hour > 23)
            throw std::invalid_argument("Hour out of range: " + std::to_string(hour));
        if (minute < 0 || minute > 59)
            throw std::invalid_argument("Minute out of range: " + std::to_string(minute));
        if (second < 0 || second > 59)
            throw std::invalid_argument("Second out of range: " + std::to_string(second));

        return DateTime{year, month, day, hour, minute, second};
    }

    // Formats a DateTime into "yyyy-MM-dd HH:mm:ss"
    std::string datetimeToString(const DateTime& dt) const {
        char buf[20];
        std::snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
                      dt.year, dt.month, dt.day,
                      dt.hour, dt.minute, dt.second);
        return buf;
    }

    // Returns the difference in whole minutes between two timestamps given as strings
    int getMinutes(const std::string& stringTime1, const std::string& stringTime2) const {
        DateTime time1 = stringToDatetime(stringTime1);
        DateTime time2 = stringToDatetime(stringTime2);
        long long secs1 = toEpochSeconds(time1);
        long long secs2 = toEpochSeconds(time2);
        long long diff = secs2 - secs1;
        long long minutes = diff / 60;   // truncates toward zero, like ChronoUnit.MINUTES.between
        if (minutes < std::numeric_limits<int>::min() ||
            minutes > std::numeric_limits<int>::max()) {
            throw std::overflow_error("Minutes difference exceeds int range");
        }
        return static_cast<int>(minutes);
    }

    // Constructs a formatted string from given date/time components
    std::string getFormatTime(int year, int month, int day,
                              int hour, int minute, int second) const {
        // Validate ranges (matching java.time.LocalDateTime.of)
        if (month < 1 || month > 12)
            throw std::invalid_argument("Month out of range");
        int maxDay = 31;
        if (month == 4 || month == 6 || month == 9 || month == 11)
            maxDay = 30;
        else if (month == 2) {
            bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            maxDay = leap ? 29 : 28;
        }
        if (day < 1 || day > maxDay)
            throw std::invalid_argument("Day out of range");
        if (hour < 0 || hour > 23)
            throw std::invalid_argument("Hour out of range");
        if (minute < 0 || minute > 59)
            throw std::invalid_argument("Minute out of range");
        if (second < 0 || second > 59)
            throw std::invalid_argument("Second out of range");

        DateTime dt{year, month, day, hour, minute, second};
        return datetimeToString(dt);
    }
};