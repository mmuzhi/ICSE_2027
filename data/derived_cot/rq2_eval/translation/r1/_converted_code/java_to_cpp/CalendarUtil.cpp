#include <chrono>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

using namespace std::chrono;

using LocalDateTime = local_time<minutes>;

class Event {
public:
    LocalDateTime date;
    LocalDateTime start_time;
    LocalDateTime end_time;
    std::string description;

    Event(LocalDateTime date, LocalDateTime start_time, LocalDateTime end_time, const std::string& description)
        : date(date), start_time(start_time), end_time(end_time), description(description) {}

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
    void add_event(const Event& event) {
        events.push_back(event);
    }

    void remove_event(const Event& event) {
        auto it = std::find(events.begin(), events.end(), event);
        if (it != events.end()) {
            events.erase(it);
        }
    }

    std::vector<Event> getEvents(const LocalDateTime& date) {
        auto date_day = floor<days>(date);
        std::vector<Event> result;
        for (const auto& event : events) {
            if (floor<days>(event.date) == date_day) {
                result.push_back(event);
            }
        }
        return result;
    }

    bool is_available(const LocalDateTime& start_time, const LocalDateTime& end_time) {
        for (const auto& event : events) {
            if (start_time < event.end_time && end_time > event.start_time) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::pair<LocalDateTime, LocalDateTime>> getAvailableSlots(const LocalDateTime& date) {
        std::vector<std::pair<LocalDateTime, LocalDateTime>> availableSlots;
        auto start_time = floor<days>(date);
        auto end_time = start_time + hours(23) + minutes(59);

        while (start_time < end_time) {
            auto slot_end_time = start_time + hours(1);
            if (isAvailable(start_time, slot_end_time)) {
                availableSlots.push_back(std::make_pair(start_time, slot_end_time));
            }
            start_time = slot_end_time;
        }

        return availableSlots;
    }

    std::vector<Event> getUpcomingEvents(int num_events) {
        auto now = system_clock::now();
        auto current_zone = std::chrono::current_zone();
        auto local_now = current_zone->to_local(now);
        auto local_now_minutes = floor<minutes>(local_now);

        std::vector<Event> result;
        int count = 0;
        for (const auto& event : events) {
            if (event.start_time > local_now_minutes) {
                result.push_back(event);
                count++;
                if (count >= num_events) {
                    break;
                }
            }
        }
        return result;
    }
};