#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <utility>
#include <functional>
#include <stdexcept>

// Note: Requires C++20 for <chrono> calendar and timezone features
using LocalDateTime = std::chrono::local_time<std::chrono::seconds>;
using LocalDate = std::chrono::local_days;

class Event {
public:
    LocalDateTime date;
    LocalDateTime start_time;
    LocalDateTime end_time;
    std::string description;

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

namespace std {
    template <>
    struct hash<Event> {
        size_t operator()(const Event& e) const {
            size_t h1 = std::hash<LocalDateTime::rep>()(e.date.time_since_epoch().count());
            size_t h2 = std::hash<LocalDateTime::rep>()(e.start_time.time_since_epoch().count());
            size_t h3 = std::hash<LocalDateTime::rep>()(e.end_time.time_since_epoch().count());
            size_t h4 = std::hash<std::string>()(e.description);
            return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
        }
    };
}

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

    std::vector<Event> getEvents(LocalDateTime date) {
        std::vector<Event> result;
        LocalDate targetDate = std::chrono::floor<std::chrono::days>(date);
        std::copy_if(events.begin(), events.end(), std::back_inserter(result),
            [&targetDate](const Event& event) {
                return std::chrono::floor<std::chrono::days>(event.date) == targetDate;
            });
        return result;
    }

    bool isAvailable(LocalDateTime start_time, LocalDateTime end_time) {
        return std::none_of(events.begin(), events.end(),
            [&start_time, &end_time](const Event& event) {
                return start_time < event.end_time && end_time > event.start_time;
            });
    }

    std::vector<std::pair<LocalDateTime, LocalDateTime>> getAvailableSlots(LocalDateTime date) {
        std::vector<std::pair<LocalDateTime, LocalDateTime>> availableSlots;
        LocalDate day = std::chrono::floor<std::chrono::days>(date);
        LocalDateTime start_time = day + std::chrono::seconds(0);
        LocalDateTime end_time = day + std::chrono::hours(23) + std::chrono::minutes(59) + std::chrono::seconds(0);

        while (start_time < end_time) {
            LocalDateTime slot_end_time = start_time + std::chrono::hours(1);
            if (isAvailable(start_time, slot_end_time)) {
                availableSlots.emplace_back(start_time, slot_end_time);
            }
            start_time = slot_end_time;
        }

        return availableSlots;
    }

    std::vector<Event> getUpcomingEvents(int num_events) {
        if (num_events < 0) {
            throw std::invalid_argument("num_events cannot be negative");
        }
        
        LocalDateTime now = std::chrono::zoned_time{std::chrono::current_zone(), std::chrono::system_clock::now()}.get_local_time();
        std::vector<Event> result;
        for (const auto& event : events) {
            if (event.start_time > now) {
                result.push_back(event);
                if (result.size() >= static_cast<size_t>(num_events)) {
                    break;
                }
            }
        }
        return result;
    }
};