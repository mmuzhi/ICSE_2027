#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <utility>

class LocalDateTime {
public:
    int year, month, day, hour, minute;

    LocalDateTime() : year(0), month(0), day(0), hour(0), minute(0) {}

    LocalDateTime(int y, int mo, int d, int h, int mi)
        : year(y), month(mo), day(d), hour(h), minute(mi) {}

    static LocalDateTime now() {
        auto now_time = std::chrono::system_clock::now();
        std::time_t tt = std::chrono::system_clock::to_time_t(now_time);
        std::tm* local_tm = std::localtime(&tt);
        return LocalDateTime(
            local_tm->tm_year + 1900,
            local_tm->tm_mon + 1,
            local_tm->tm_mday,
            local_tm->tm_hour,
            local_tm->tm_min
        );
    }

    bool toLocalDateEquals(const LocalDateTime& other) const {
        return year == other.year && month == other.month && day == other.day;
    }

    LocalDateTime withHour(int h) const {
        LocalDateTime result = *this;
        result.hour = h;
        return result;
    }

    LocalDateTime withMinute(int m) const {
        LocalDateTime result = *this;
        result.minute = m;
        return result;
    }

    LocalDateTime plusHours(int h) const {
        LocalDateTime result = *this;
        result.hour += h;
        return result;
    }

    bool isBefore(const LocalDateTime& other) const {
        return compare(other) < 0;
    }

    bool isAfter(const LocalDateTime& other) const {
        return compare(other) > 0;
    }

    bool operator==(const LocalDateTime& other) const {
        return year == other.year && month == other.month && day == other.day &&
               hour == other.hour && minute == other.minute;
    }

    bool operator!=(const LocalDateTime& other) const {
        return !(*this == other);
    }

    int compare(const LocalDateTime& other) const {
        if (year != other.year) return year < other.year ? -1 : 1;
        if (month != other.month) return month < other.month ? -1 : 1;
        if (day != other.day) return day < other.day ? -1 : 1;
        if (hour != other.hour) return hour < other.hour ? -1 : 1;
        if (minute != other.minute) return minute < other.minute ? -1 : 1;
        return 0;
    }
};

class Event {
public:
    LocalDateTime date;
    LocalDateTime start_time;
    LocalDateTime end_time;
    std::string description;

    Event() = default;
    Event(LocalDateTime date, LocalDateTime start_time, LocalDateTime end_time, std::string description)
        : date(date), start_time(start_time), end_time(end_time), description(std::move(description)) {}

    bool operator==(const Event& other) const {
        return date == other.date &&
               start_time == other.start_time &&
               end_time == other.end_time &&
               description == other.description;
    }

    bool operator!=(const Event& other) const {
        return !(*this == other);
    }
};

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

    std::vector<Event> getEvents(const LocalDateTime& date) {
        std::vector<Event> result;
        for (const auto& event : events) {
            if (event.date.toLocalDateEquals(date)) {
                result.push_back(event);
            }
        }
        return result;
    }

    bool isAvailable(const LocalDateTime& start_time, const LocalDateTime& end_time) {
        return std::none_of(events.begin(), events.end(), [&](const Event& event) {
            return start_time.isBefore(event.end_time) && end_time.isAfter(event.start_time);
        });
    }

    std::vector<std::pair<LocalDateTime, LocalDateTime>> getAvailableSlots(const LocalDateTime& date) {
        std::vector<std::pair<LocalDateTime, LocalDateTime>> availableSlots;
        LocalDateTime start_time = date.withHour(0).withMinute(0);
        LocalDateTime end_time = date.withHour(23).withMinute(59);

        while (start_time.isBefore(end_time)) {
            LocalDateTime slot_end_time = start_time.plusHours(1);
            if (isAvailable(start_time, slot_end_time)) {
                availableSlots.push_back({start_time, slot_end_time});
            }
            start_time = slot_end_time;
        }

        return availableSlots;
    }

    std::vector<Event> getUpcomingEvents(int num_events) {
        LocalDateTime now = LocalDateTime::now();
        std::vector<Event> result;
        for (const auto& event : events) {
            if (event.start_time.isAfter(now)) {
                result.push_back(event);
                if (static_cast<int>(result.size()) >= num_events) break;
            }
        }
        return result;
    }
};