#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <utility>

class DateTime {
public:
    int year, month, day, hour, minute, second;

    DateTime(int y, int mo, int d, int h = 0, int mi = 0, int s = 0)
        : year(y), month(mo), day(d), hour(h), minute(mi), second(s) {}

    DateTime() : year(0), month(0), day(0), hour(0), minute(0), second(0) {}

    struct Date {
        int year, month, day;
        bool operator==(const Date& other) const {
            return year == other.year && month == other.month && day == other.day;
        }
    };

    Date date() const {
        return {year, month, day};
    }

    bool operator<(const DateTime& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        if (day != other.day) return day < other.day;
        if (hour != other.hour) return hour < other.hour;
        if (minute != other.minute) return minute < other.minute;
        return second < other.second;
    }

    bool operator>(const DateTime& other) const { return other < *this; }
    bool operator<=(const DateTime& other) const { return !(*this > other); }
    bool operator>=(const DateTime& other) const { return !(*this < other); }

    bool operator==(const DateTime& other) const {
        return year == other.year && month == other.month && day == other.day &&
               hour == other.hour && minute == other.minute && second == other.second;
    }

    bool operator!=(const DateTime& other) const { return !(*this == other); }

    DateTime operator+(int minutes) const {
        DateTime res = *this;
        res.minute += minutes;

        // carry minutes -> hours
        while (res.minute >= 60) {
            res.minute -= 60;
            res.hour++;
        }

        // carry hours -> days (with simplified month/year handling)
        while (res.hour >= 24) {
            res.hour -= 24;
            res.day++;
            // simple month overflow (leap year handled for February)
            int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
            if (res.year % 4 == 0 && (res.year % 100 != 0 || res.year % 400 == 0))
                daysInMonth[1] = 29;
            if (res.day > daysInMonth[res.month - 1]) {
                res.day = 1;
                res.month++;
                if (res.month > 12) {
                    res.month = 1;
                    res.year++;
                }
            }
        }
        return res;
    }

    static DateTime now() {
        std::time_t t = std::time(nullptr);
        std::tm* tm = std::localtime(&t);
        return DateTime(tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                        tm->tm_hour, tm->tm_min, tm->tm_sec);
    }
};

struct Event {
    DateTime date;
    DateTime start_time;
    DateTime end_time;
    std::string description;

    bool operator==(const Event& other) const {
        return date == other.date &&
               start_time == other.start_time &&
               end_time == other.end_time &&
               description == other.description;
    }
};

class CalendarUtil {
private:
    std::vector<Event> events;

public:
    CalendarUtil() {}

    void add_event(const Event& event) {
        events.push_back(event);
    }

    void remove_event(const Event& event) {
        auto it = std::find(events.begin(), events.end(), event);
        if (it != events.end()) {
            events.erase(it);
        }
    }

    std::vector<Event> get_events(const DateTime& date) {
        std::vector<Event> result;
        for (const auto& ev : events) {
            if (ev.date.date() == date.date()) {
                result.push_back(ev);
            }
        }
        return result;
    }

    bool is_available(const DateTime& start_time, const DateTime& end_time) {
        for (const auto& ev : events) {
            if (start_time < ev.end_time && end_time > ev.start_time) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::pair<DateTime, DateTime>> get_available_slots(const DateTime& date) {
        std::vector<std::pair<DateTime, DateTime>> slots;
        DateTime start_time(date.year, date.month, date.day, 0, 0);
        DateTime end_time(date.year, date.month, date.day, 23, 59);

        while (start_time < end_time) {
            DateTime slot_end = start_time + 60; // 60 minutes
            if (is_available(start_time, slot_end)) {
                slots.push_back(std::make_pair(start_time, slot_end));
            }
            start_time = start_time + 60;
        }
        return slots;
    }

    std::vector<Event> get_upcoming_events(int num_events) {
        DateTime now = DateTime::now();
        std::vector<Event> upcoming;
        for (const auto& ev : events) {
            if (ev.start_time >= now) {
                upcoming.push_back(ev);
                if (static_cast<int>(upcoming.size()) == num_events) {
                    break;
                }
            }
        }
        return upcoming;
    }
};