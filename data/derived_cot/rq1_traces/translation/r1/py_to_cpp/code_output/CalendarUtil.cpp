#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;
using namespace std::chrono;

// Helper functions for conversion
sys_days tm_to_sys_days(const tm& tm_time) {
    return sys_days{ year{tm_time.tm_year + 1900} / (tm_time.tm_mon + 1) / tm_time.tm_mday };
}

system_clock::time_point tm_to_time_point(const tm& tm_time) {
    auto tp = sys_days{ year{tm_time.tm_year + 1900} / (tm_time.tm_mon + 1) / tm_time.tm_mday }
              + hours{ tm_time.tm_hour } 
              + minutes{ tm_time.tm_min };
    return tp;
}

// Event structure
struct Event {
    sys_days date;
    system_clock::time_point start_time;
    system_clock::time_point end_time;
    string description;

    bool operator==(const Event& other) const {
        return date == other.date &&
               start_time == other.start_time &&
               end_time == other.end_time &&
               description == other.description;
    }
};

class CalendarUtil {
private:
    vector<Event> events;

    vector<Event> get_events(sys_days date) {
        vector<Event> events_on_date;
        for (const Event& event : events) {
            if (event.date == date) {
                events_on_date.push_back(event);
            }
        }
        return events_on_date;
    }

    bool is_available(const system_clock::time_point& start_time, const system_clock::time_point& end_time) {
        for (const Event& event : events) {
            if (start_time < event.end_time && end_time > event.start_time) {
                return false;
            }
        }
        return true;
    }

    vector<pair<system_clock::time_point, system_clock::time_point>> get_available_slots(sys_days date) {
        vector<pair<system_clock::time_point, system_clock::time_point>> available_slots;
        auto start_of_day = date;
        auto end_of_day = date + days{1};

        auto current = start_of_day;
        while (current < end_of_day) {
            auto next = current + hours{1};
            if (is_available(current, next)) {
                available_slots.push_back({current, next});
            }
            current = next;
        }
        return available_slots;
    }

public:
    CalendarUtil() = default;

    void add_event(const Event& event) {
        events.push_back(event);
    }

    void remove_event(const Event& event) {
        auto it = find(events.begin(), events.end(), event);
        if (it != events.end()) {
            events.erase(it);
        }
    }

    vector<Event> get_events(tm date_tm) {
        return get_events(tm_to_sys_days(date_tm));
    }

    bool is_available(tm start_tm, tm end_tm) {
        return is_available(tm_to_time_point(start_tm), tm_to_time_point(end_tm));
    }

    vector<pair<system_clock::time_point, system_clock::time_point>> get_available_slots(tm date_tm) {
        return get_available_slots(tm_to_sys_days(date_tm));
    }

    vector<Event> get_upcoming_events(int num_events) {
        auto now = system_clock::now();
        vector<Event> upcoming_events;
        for (const Event& event : events) {
            if (event.start_time >= now) {
                upcoming_events.push_back(event);
                if (upcoming_events.size() == num_events) {
                    break;
                }
            }
        }
        return upcoming_events;
    }
};