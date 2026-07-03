#include <vector>
#include <chrono>
#include <ctime>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

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
private:
    vector<Event> events;

    std::chrono::system_clock::time_point get_midnight(std::chrono::system_clock::time_point tp) {
        auto tt = std::chrono::system_clock::to_time_t(tp);
        std::tm tmb = *localtime(&tt);
        tmb.tm_hour = 0;
        tmb.tm_min = 0;
        tmb.tm_sec = 0;
        return std::chrono::system_clock::from_time_t(mktime(&tmb));
    }

    bool same_day(const std::chrono::system_clock::time_point& t1, const std::chrono::system_clock::time_point& t2) {
        return get_midnight(t1) == get_midnight(t2);
    }

public:
    void add_event(const Event& event) {
        events.push_back(event);
    }

    void remove_event(const Event& event) {
        auto it = find(events.begin(), events.end(), event);
        if (it != events.end()) {
            events.erase(it);
        }
    }

    vector<Event> get_events(const std::chrono::system_clock::time_point& date) {
        vector<Event> events_on_date;
        for (const auto& event : events) {
            if (same_day(event.date, date)) {
                events_on_date.push_back(event);
            }
        }
        return events_on_date;
    }

    bool is_available(const std::chrono::system_clock::time_point& start_time, const std::chrono::system_clock::time_point& end_time) {
        for (const auto& event : events) {
            if (event.start_time < end_time && event.end_time > start_time) {
                return false;
            }
        }
        return true;
    }

    vector<pair<std::chrono::system_clock::time_point, std::chrono::system_clock::time_point>> get_available_slots(const std::chrono::system_clock::time_point& date) {
        vector<pair<std::chrono::system_clock::time_point, std::chrono::system_clock::time_point>> available_slots;
        auto start_of_day = get_midnight(date);
        auto end_of_day = start_of_day + std::chrono::days(1);

        auto current_start = start_of_day;
        while (current_start < end_of_day) {
            auto current_end = current_start + std::chrono::minutes(60);
            if (is_available(current_start, current_end)) {
                available_slots.push_back(make_pair(current_start, current_end));
            }
            current_start += std::chrono::minutes(60);
        }
        return available_slots;
    }

    vector<Event> get_upcoming_events(int num_events) {
        auto now = std::chrono::system_clock::now();
        vector<Event> upcoming_events;
        for (const auto& event : events) {
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