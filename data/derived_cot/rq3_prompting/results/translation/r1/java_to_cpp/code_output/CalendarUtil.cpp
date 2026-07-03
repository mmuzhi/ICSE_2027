#include <algorithm>
#include <ctime>
#include <functional>
#include <string>
#include <utility>
#include <vector>

// Lightweight date-only structure
struct DateOnly {
    int year;
    int month;
    int day;

    bool operator==(const DateOnly& other) const {
        return year == other.year && month == other.month && day == other.day;
    }

    bool operator<(const DateOnly& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
};

// DateTime with minute precision (seconds and nanoseconds ignored)
struct DateTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;

    DateTime() : year(0), month(0), day(0), hour(0), minute(0) {}
    DateTime(int y, int m, int d, int h, int min)
        : year(y), month(m), day(d), hour(h), minute(min) {}

    // convert to local date (ignoring time)
    DateOnly toLocalDate() const {
        return {year, month, day};
    }

    // create a new DateTime with the same date but given hour/minute
    DateTime withHour(int h) const {
        return {year, month, day, h, minute};
    }
    DateTime withMinute(int m) const {
        return {year, month, day, hour, m};
    }

    // add hours (handles day/month/year overflow)
    DateTime plusHours(int h) const {
        int newHour = hour + h;
        int newDay = day;
        int newMonth = month;
        int newYear = year;
        while (newHour >= 24) {
            newHour -= 24;
            newDay += 1;
            // simple month/year rollover (not fully general, but sufficient for 1-hour increments)
            if (newDay > daysInMonth(newMonth, newYear)) {
                newDay = 1;
                newMonth += 1;
                if (newMonth > 12) {
                    newMonth = 1;
                    newYear += 1;
                }
            }
        }
        return {newYear, newMonth, newDay, newHour, minute};
    }

    // comparison operators (strict)
    bool operator<(const DateTime& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        if (day != other.day) return day < other.day;
        if (hour != other.hour) return hour < other.hour;
        return minute < other.minute;
    }
    bool operator>(const DateTime& other) const { return other < *this; }
    bool operator<=(const DateTime& other) const { return !(other < *this); }
    bool operator>=(const DateTime& other) const { return !(*this < other); }
    bool operator==(const DateTime& other) const {
        return year == other.year && month == other.month && day == other.day &&
               hour == other.hour && minute == other.minute;
    }
    bool operator!=(const DateTime& other) const { return !(*this == other); }

    // convenience wrappers matching Java's isBefore/isAfter
    bool isBefore(const DateTime& other) const { return *this < other; }
    bool isAfter(const DateTime& other) const { return *this > other; }

    // current local date-time
    static DateTime now() {
        std::time_t t = std::time(nullptr);
        struct tm* local = std::localtime(&t);
        return {local->tm_year + 1900, local->tm_mon + 1, local->tm_mday,
                local->tm_hour, local->tm_min};
    }

private:
    static int daysInMonth(int month, int year) {
        static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
            return 29;
        return days[month - 1];
    }
};

// std::hash specializations
namespace std {
    template<> struct hash<DateOnly> {
        size_t operator()(const DateOnly& d) const {
            size_t h = d.year;
            h = h * 31 + d.month;
            h = h * 31 + d.day;
            return h;
        }
    };
    template<> struct hash<DateTime> {
        size_t operator()(const DateTime& dt) const {
            size_t h = dt.year;
            h = h * 31 + dt.month;
            h = h * 31 + dt.day;
            h = h * 31 + dt.hour;
            h = h * 31 + dt.minute;
            return h;
        }
    };
}

// Event class
class Event {
public:
    DateTime date;
    DateTime start_time;
    DateTime end_time;
    std::string description;

    Event(const DateTime& date, const DateTime& start_time, const DateTime& end_time,
          const std::string& description)
        : date(date), start_time(start_time), end_time(end_time), description(description) {}

    bool operator==(const Event& other) const {
        return date == other.date &&
               start_time == other.start_time &&
               end_time == other.end_time &&
               description == other.description;
    }
};

namespace std {
    template<> struct hash<Event> {
        size_t operator()(const Event& e) const {
            size_t h = hash<DateTime>()(e.date);
            h = h * 31 + hash<DateTime>()(e.start_time);
            h = h * 31 + hash<DateTime>()(e.end_time);
            h = h * 31 + hash<std::string>()(e.description);
            return h;
        }
    };
}

// Calendar utility class
class CalendarUtil {
public:
    std::vector<Event> events;

    void addEvent(const Event& event) {
        events.push_back(event);
    }

    void removeEvent(const Event& event) {
        auto it = std::find(events.begin(), events.end(), event);
        if (it != events.end()) {
            events.erase(it);
        }
    }

    std::vector<Event> getEvents(const DateTime& date) {
        DateOnly targetDate = date.toLocalDate();
        std::vector<Event> result;
        for (const auto& ev : events) {
            if (ev.date.toLocalDate() == targetDate) {
                result.push_back(ev);
            }
        }
        return result;
    }

    bool isAvailable(const DateTime& start_time, const DateTime& end_time) {
        return std::none_of(events.begin(), events.end(),
            [&](const Event& ev) {
                return start_time.isBefore(ev.end_time) && end_time.isAfter(ev.start_time);
            });
    }

    // Returns available 1-hour slots for the given date (using only date part)
    std::vector<std::pair<DateTime, DateTime>> getAvailableSlots(const DateTime& date) {
        std::vector<std::pair<DateTime, DateTime>> slots;
        DateTime slot_start = date.withHour(0).withMinute(0);
        DateTime day_end = date.withHour(23).withMinute(59);

        while (slot_start.isBefore(day_end)) {
            DateTime slot_end = slot_start.plusHours(1);
            if (isAvailable(slot_start, slot_end)) {
                slots.push_back({slot_start, slot_end});
            }
            slot_start = slot_end;
        }
        return slots;
    }

    std::vector<Event> getUpcomingEvents(int num_events) {
        DateTime now = DateTime::now();
        std::vector<Event> result;
        for (const auto& ev : events) {
            if (ev.start_time.isAfter(now)) {
                result.push_back(ev);
                if (static_cast<int>(result.size()) == num_events) break;
            }
        }
        return result;
    }
};