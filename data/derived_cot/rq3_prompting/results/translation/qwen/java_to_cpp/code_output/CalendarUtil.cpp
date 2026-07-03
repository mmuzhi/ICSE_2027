#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
#include <utility> // for std::pair
#include <ctime>    // for std::localtime

using namespace std::chrono;

struct LocalDateTime {
    time_point tp;

    LocalDateTime() : tp(system_clock::now()) {}
    LocalDateTime(const time_point& t) : tp(t) {}

    bool isBefore(const LocalDateTime& other) const {
        return tp < other.tp;
    }

    bool isAfter(const LocalDateTime& other) const {
        return tp > other.tp;
    }

    bool operator==(const LocalDateTime& other) const {
        return tp == other.tp;
    }

    bool operator<(const LocalDateTime& other) const {
        return tp < other.tp;
    }

    LocalDateTime plusHours(int hours) const {
        return LocalDateTime(tp + hours);
    }

    struct Date {
        int year;
        int month;
        int day;
    };

    Date getDate() const {
        auto tt = system_clock::to_time_t(tp);
        auto tm = localtime(&tt);
        return {tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday};
    }
};

struct Event {
    LocalDateTime date;
    LocalDateTime start_time;
    LocalDateTime end_time;
    std::string description;

    Event(const LocalDateTime& date, const LocalDateTime& start_time, const LocalDateTime& end_time, const std::string& description)
        : date(date), start_time(start_time), end_time(end_time), description(description) {}

    bool operator==(const Event& other) const {
        return date == other.date && start_time == other.start_time && end_time == other.end_time && description == other.description;
    }

    bool operator<(const Event& other) const {
        return date < other.date || (date == other.date && start_time < other.start_time);
    }
};

class CalendarUtil {
    std::vector<Event> events;

public:
    void addEvent(const Event& event) {
        events.push_back(event);
    }

    void removeEvent(const Event& event) {
        auto it = std::find_if(events.begin(), events.end(), [&](const Event& e) {
            return e == event;
        });
        if (it != events.end()) {
            events.erase(it);
        }
    }

    std::vector<Event> getEvents(const LocalDateTime& date) {
        std::vector<Event> result;
        for (const auto& event : events) {
            if (event.date.getDate().year == date.getDate().year &&
                event.date.getDate().month == date.getDate().month &&
                event.date.getDate().day == date.getDate().day) {
                result.push_back(event);
            }
        }
        return result;
    }

    bool isAvailable(const LocalDateTime& start_time, const LocalDateTime& end_time) {
        for (const auto& event : events) {
            if (start_time.isBefore(event.end_time) && end_time.isAfter(event.start_time)) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::pair<LocalDateTime, LocalDateTime>> getAvailableSlots(const LocalDateTime& date) {
        std::vector<std::pair<LocalDateTime, LocalDateTime>> availableSlots;
        LocalDateTime start_time = date.getDate() == LocalDateTime().getDate() ? 
            date : LocalDateTime(date.getDate().year, date.getDate().month, date.getDate().day);
        LocalDateTime end_time = LocalDateTime().endOfDay();

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
        auto now = LocalDateTime();
        std::vector<Event> result;
        for (const auto& event : events) {
            if (event.start_time.isAfter(now)) {
                result.push_back(event);
                if (result.size() == num_events) break;
            }
        }
        return result;
    }
};