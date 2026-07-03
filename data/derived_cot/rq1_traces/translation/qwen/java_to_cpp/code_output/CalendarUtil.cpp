#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <utility> // for std::pair
#include <iostream>

namespace org {
namespace example {

struct Event {
    std::chrono::system_clock::time_point date;
    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::time_point end_time;
    std::string description;

    Event(std::chrono::system_clock::time_point d, std::chrono::system_clock::time_point s, std::chrono::system_clock::time_point e, std::string desc)
        : date(d), start_time(s), end_time(e), description(std::move(desc)) {}

    bool operator==(const Event& other) const {
        return date == other.date && start_time == other.start_time && end_time == other.end_time && description == other.description;
    }
};

class CalendarUtil {
    std::vector<Event> events;

public:
    void addEvent(const Event& event) {
        events.push_back(event);
    }

    void removeEvent(const Event& event) {
        auto it = std::find(events.begin(), events.end(), event);
        if (it != events.end()) {
            events.erase(it);
        }
    }

    std::vector<Event> getEvents(std::chrono::system_clock::time_point date) {
        auto d_start = truncateToDay(date);
        std::vector<Event> result;
        std::copy_if(events.begin(), events.end(), std::back_inserter(result), [d_start](const Event& e) {
            return truncateToDay(e.date) == d_start;
        });
        return result;
    }

    bool isAvailable(std::chrono::system_clock::time_point start_time, std::chrono::system_clock::time_point end_time) {
        return std::all_of(events.begin(), events.end(), [&](const Event& event) {
            return !(start_time < event.end_time && end_time > event.start_time);
        });
    }

    std::vector<std::pair<std::chrono::system_clock::time_point, std::chrono::system_clock::time_point>> getAvailableSlots(std::chrono::system_clock::time_point date) {
        auto d_start = truncateToDay(date);
        auto d_end = d_start + std::chrono::hours(24);

        std::vector<std::pair<std::chrono::system_clock::time_point, std::chrono::system_clock::time_point>> availableSlots;

        auto current_time = d_start;
        while (current_time < d_end) {
            auto slot_end_time = current_time + std::chrono::hours(1);
            if (isAvailable(current_time, slot_end_time)) {
                availableSlots.push_back(std::make_pair(current_time, slot_end_time));
            }
            current_time = slot_end_time;
        }

        return availableSlots;
    }

    std::vector<Event> getUpcomingEvents(int num_events) {
        auto now = std::chrono::system_clock::now();
        std::vector<Event> result;
        std::copy_if(events.begin(), events.end(), std::back_inserter(result), [now](const Event& event) {
            return event.start_time > now;
        });
        if (result.size() > num_events) {
            result.resize(num_events);
        }
        return result;
    }

private:
    std::chrono::system_clock::time_point truncateToDay(std::chrono::system_clock::time_point tp) {
        std::time_t tt = std::chrono::system_clock::to_time_t(tp);
        std::tm* ptm = std::localtime(&tt);
        ptm->tm_hour = 0;
        ptm->tm_min = 0;
        ptm->tm_sec = 0;
        std::time_t new_tt = std::mktime(ptm);
        return std::chrono::system_clock::from_time_t(new_tt);
    }
};
} // namespace example
} // namespace org