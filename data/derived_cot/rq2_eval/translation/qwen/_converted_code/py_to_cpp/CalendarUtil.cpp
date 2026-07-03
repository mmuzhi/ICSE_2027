#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <algorithm>

using namespace std;

namespace {
    using time_point = std::chrono::system_clock::time_point;
    using duration = std::chrono::system_clock::duration;

    time_point truncate_to_day(time_point tp) {
        auto tt = std::chrono::system_clock::to_time_t(tp);
        struct tm tm = {};
        gmtime_r(&tt, &tm); // Use UTC to avoid timezone issues
        tm.tm_hour = 0;
        tm.tm_min = 0;
        tm.tm_sec = 0;
        time_t tt2 = mktime(&tm);
        return std::chrono::system_clock::from_time_t(tt2);
    }

    bool is_time_overlap(time_point a_start, time_point a_end, time_point b_start, time_point b_end) {
        return !(a_end <= b_start || a_start >= b_end);
    }

    time_point add_minutes(time_point tp, int minutes) {
        auto duration_minutes = std::chrono::minutes(minutes);
        return tp + duration_minutes;
    }
}

struct Event {
    time_point date;
    time_point start_time;
    time_point end_time;
    string description;
};

class CalendarUtil {
private:
    vector<Event> events;

    Event from_dict(const string& json) {
        // This is a placeholder; in a real scenario, parse the JSON string
        // For simplicity, we assume direct conversion from Python dict to C++ Event
        // This example doesn't implement JSON parsing but shows the structure
        // In practice, use a JSON library to parse and convert
        static time_point now = std::chrono::system_clock::now();
        return Event{now, now, add_minutes(now, 60), "Test Event"};
    }

public:
    CalendarUtil() {}

    void add_event(const string& event_json) {
        events.push_back(from_dict(event_json));
    }

    void remove_event(const string& event_json) {
        auto it = find_if(events.begin(), events.end(), [&](const Event& e) {
            return /* compare with event_json */;
        });
        if (it != events.end()) {
            events.erase(it);
        }
    }

    vector<Event> get_events(time_point date) {
        time_point date_start = truncate_to_day(date);
        vector<Event> result;
        for (const auto& event : events) {
            if (truncate_to_day(event.start_time) == date_start) {
                result.push_back(event);
            }
        }
        return result;
    }

    bool is_available(time_point start_time, time_point end_time) {
        for (const auto& event : events) {
            if (is_time_overlap(event.start_time, event.end_time, start_time, end_time)) {
                return false;
            }
        }
        return true;
    }

    vector<pair<time_point, time_point>> get_available_slots(time_point date) {
        time_point slot_start = std::chrono::system_clock::from_time_t(std::mktime(new tm { .tm_year = 123, .tm_mon = 0, .tm_mday = 1 }));
        time_point slot_end = add_minutes(slot_start, 60);
        time_point day_end = truncate_to_day(add_minutes(date, 24 * 60 * 60));

        vector<pair<time_point, time_point>> slots;
        while (slot_start < day_end) {
            if (is_available(slot_start, slot_end)) {
                slots.push_back({slot_start, slot_end});
            }
            slot_start = add_minutes(slot_start, 60);
            slot_end = add_minutes(slot_start, 60);
        }
        return slots;
    }

    vector<Event> get_upcoming_events(time_point date, int num_events) {
        time_point now = std::chrono::system_clock::now();
        vector<Event> result;
        for (const auto& event : events) {
            if (event.start_time >= now) {
                result.push_back(event);
                if (result.size() == num_events) break;
            }
        }
        return result;
    }
};