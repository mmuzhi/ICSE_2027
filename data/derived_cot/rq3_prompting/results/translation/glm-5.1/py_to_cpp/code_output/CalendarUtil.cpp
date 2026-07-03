#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <ctime>
#include <utility>

struct Event {
    std::chrono::system_clock::time_point date;
    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::time_point end_time;
    std::string description;

    bool operator==(const Event& other) const {
        return date == other.date && start_time == other.start_time && end_time == other.end_time && description == other.description;
    }
};

class CalendarUtil {
public:
    std::vector<Event> events;

    CalendarUtil() = default;

    void add_event(const Event& event) {
        events.push_back(event);
    }

    void remove_event(const Event& event) {
        auto it = std::find(events.begin(), events.end(), event);
        if (it != events.end()) {
            events.erase(it);
        }
    }

    std::vector<Event> get_events(std::chrono::system_clock::time_point date) {
        std::vector<Event> events_on_date;
        for (const auto& event : events) {
            if (same_date(event.date, date)) {
                events_on_date.push_back(event);
            }
        }
        return events_on_date;
    }

    bool is_available(std::chrono::system_clock::time_point start_time, std::chrono::system_clock::time_point end_time) {
        for (const auto& event : events) {
            if (start_time < event.end_time && end_time > event.start_time) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::pair<std::chrono::system_clock::time_point, std::chrono::system_clock::time_point>> get_available_slots(std::chrono::system_clock::time_point date) {
        std::vector<std::pair<std::chrono::system_clock::time_point, std::chrono::system_clock::time_point>> available_slots;
        std::time_t date_c = std::chrono::system_clock::to_time_t(date);
        std::tm date_tm = *std::localtime(&date_c);
        
        std::tm start_tm = date_tm;
        start_tm.tm_hour = 0; start_tm.tm_min = 0; start_tm.tm_sec = 0; start_tm.tm_isdst = -1;
        auto start_time = std::chrono::system_clock::from_time_t(std::mktime(&start_tm));

        std::tm end_tm = date_tm;
        end_tm.tm_hour = 23; end_tm.tm_min = 59; end_tm.tm_sec = 0; end_tm.tm_isdst = -1;
        auto end_time = std::chrono::system_clock::from_time_t(std::mktime(&end_tm));

        while (start_time < end_time) {
            auto slot_end_time = start_time + std::chrono::minutes(60);
            if (is_available(start_time, slot_end_time)) {
                available_slots.push_back({start_time, slot_end_time});
            }
            start_time += std::chrono::minutes(60);
        }
        return available_slots;
    }

    std::vector<Event> get_upcoming_events(int num_events) {
        auto now = std::chrono::system_clock::now();
        std::vector<Event> upcoming_events;
        for (const auto& event : events) {
            if (event.start_time >= now) {
                upcoming_events.push_back(event);
            }
            if (static_cast<int>(upcoming_events.size()) == num_events) {
                break;
            }
        }
        return upcoming_events;
    }

private:
    static bool same_date(std::chrono::system_clock::time_point t1, std::chrono::system_clock::time_point t2) {
        std::time_t time1 = std::chrono::system_clock::to_time_t(t1);
        std::time_t time2 = std::chrono::system_clock::to_time_t(t2);
        std::tm tm1 = *std::localtime(&time1);
        std::tm tm2 = *std::localtime(&time2);
        return tm1.tm_year == tm2.tm_year && tm1.tm_mon == tm2.tm_mon && tm1.tm_mday == tm2.tm_mday;
    }
};