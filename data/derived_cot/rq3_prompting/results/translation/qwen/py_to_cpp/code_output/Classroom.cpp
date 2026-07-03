#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <unordered_map>
#include <cctype>
#include <iostream>

struct Course {
    std::string name;
    int start_minutes;
    int end_minutes;
};

class Classroom {
private:
    int id;
    std::vector<Course> courses;

    int parse_time(const std::string& time_str) {
        if (time_str.size() != 5 || time_str[2] != ':') {
            throw std::runtime_error("Invalid time format");
        }
        try {
            int hours = std::stoi(time_str.substr(0, 2));
            int minutes = std::stoi(time_str.substr(3, 2));
            if (hours < 0 || hours >= 24 || minutes < 0 || minutes >= 60) {
                throw std::runtime_error("Invalid time value");
            }
            return hours * 60 + minutes;
        } catch (...) {
            throw std::runtime_error("Invalid time format");
        }
    }

    Course dict_to_course(const std::unordered_map<std::string, std::string>& course_dict) {
        Course course;
        if (course_dict.find("name") == course_dict.end() || 
            course_dict.find("start_time") == course_dict.end() ||
            course_dict.find("end_time") == course_dict.end()) {
            throw std::runtime_error("Invalid course dictionary");
        }
        course.name = course_dict.at("name");
        course.start_minutes = parse_time(course_dict.at("start_time"));
        course.end_minutes = parse_time(course_dict.at("end_time"));
        return course;
    }

    bool course_conflicts(const Course& a, const Course& b) {
        return (a.start_minutes <= b.start_minutes && a.end_minutes >= b.start_minutes) ||
               (a.start_minutes <= b.end_minutes && a.end_minutes >= b.end_minutes);
    }

public:
    Classroom(int id) : id(id) {}

    void add_course(const std::unordered_map<std::string, std::string>& course) {
        Course c = dict_to_course(course);
        bool exists = false;
        for (const auto& course_in_class : courses) {
            if (course_in_class.name == c.name && 
                course_in_class.start_minutes == c.start_minutes &&
                course_in_class.end_minutes == c.end_minutes) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            courses.push_back(c);
        }
    }

    void remove_course(const std::unordered_map<std::string, std::string>& course) {
        Course c = dict_to_course(course);
        auto it = std::find_if(courses.begin(), courses.end(), [&c](const Course& course_in_class) {
            return course_in_class.name == c.name &&
                   course_in_class.start_minutes == c.start_minutes &&
                   course_in_class.end_minutes == c.end_minutes;
        });
        if (it != courses.end()) {
            courses.erase(it);
        }
    }

    bool is_free_at(const std::string& check_time) {
        try {
            int check_minutes = parse_time(check_time);
            for (const auto& course : courses) {
                if (course.start_minutes <= check_minutes && course.end_minutes >= check_minutes) {
                    return false;
                }
            }
            return true;
        } catch (...) {
            throw std::runtime_error("Invalid time format");
        }
    }

    bool check_course_conflict(const std::unordered_map<std::string, std::string>& new_course) {
        try {
            Course new_c = dict_to_course(new_course);
            for (const auto& course : courses) {
                if (course_conflicts(course, new_c)) {
                    return false;
                }
            }
            return true;
        } catch (...) {
            throw std::runtime_error("Invalid course dictionary");
        }
    }
};