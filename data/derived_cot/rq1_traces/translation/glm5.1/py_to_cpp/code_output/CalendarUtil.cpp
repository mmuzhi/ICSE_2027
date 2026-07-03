#include <chrono>
#include <vector>
#include <string>
#include <algorithm>

class CalendarUtil {
public:
    // Alias for better readability, matching Python's datetime objects
    using TimePoint = std::chrono::system_clock::time_point;

    // Struct replaces the Python dictionary for fixed schema and idiomatic C++ access
    struct Event {
        TimePoint date;
        TimePoint start_time;
        TimePoint end_time;
        std::string description;

        // Required to mimic Python's `if event in self.events:` and `list.remove()`
        bool operator==(const Event& other) const {
            return date == other.date &&
                   start_time == other.start_time &&
                   end_time == other.end_time &&
                   description == other.description;
        }
    };

    void add_event(const Event& event) {
        events.push_back(event);
    }

    void remove_event(const Event& event) {
        // Python's list.remove() removes the first matching occurrence.
        auto it = std::find(events.begin(), events.end(), event);
        if (it != events.end()) {
            events.erase(it);
        }
    }

    std::vector<Event> get_events(TimePoint date) const {
        std::vector<Event> events_on_date;
        // std::chrono::floor<std::chrono::days> extracts the date part, matching Python's .date()
        auto target_day = std::chrono::floor<std::chrono::days>(date);
        
        for (const auto& event : events) {
            auto event_day = std::chrono::floor<std::chrono::days>(event.date);
            if (event_day == target_day) {
                events_on_date.push_back(event);
            }
        }
        return events_on_date;
    }

    bool is_available(TimePoint start_time, TimePoint end_time) const {
        for (const auto& event : events) {
            if (start_time < event.end_time && end_time > event.start_time) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::pair<TimePoint, TimePoint>> get_available_slots(TimePoint date) const {
        std::vector<std::pair<TimePoint, TimePoint>> available_slots;
        
        // Equivalent to datetime(date.year, date.month, date.day, 0, 0)
        auto day = std::chrono::floor<std::chrono::days>(date);
        auto start_time = day;
        
        // Equivalent to datetime(date.year, date.month, date.day, 23, 59)
        auto end_time = day + std::chrono::hours(23) + std::chrono::minutes(59);

        while (start_time < end_time) {
            // Equivalent to timedelta(minutes=60)
            auto slot_end_time = start_time + std::chrono::hours(1);
            if (is_available(start_time, slot_end_time)) {
                available_slots.emplace_back(start_time, slot_end_time);
            }
            start_time += std::chrono::hours(1);
        }

        return available_slots;
    }

    std::vector<Event> get_upcoming_events(int num_events) const {
        auto now = std::chrono::system_clock::now();
        std::vector<Event> upcoming_events;
        
        for (const auto& event : events) {
            if (event.start_time >= now) {
                upcoming_events.push_back(event);
            }
            // Python iterates over the whole list and breaks when the length matches
            if (static_cast<int>(upcoming_events.size()) == num_events) {
                break;
            }
        }
        return upcoming_events;
    }

private:
    std::vector<Event> events;
};