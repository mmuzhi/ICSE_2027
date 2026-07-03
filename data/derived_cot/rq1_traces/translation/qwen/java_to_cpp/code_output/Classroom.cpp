#include <vector>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

// Define the Course class with start and end times as std::chrono::time_point
class Course {
public:
    std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> startTime;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> endTime;

    Course() : startTime(std::chrono::system_clock::now().time_since_epoch()), endTime(std::chrono::system_clock::now().time_since_epoch()) {}
};

// Define the Classroom class
class Classroom {
private:
    int id;
    std::vector<Course> courses;

public:
    Classroom(int id) : id(id) {}

    // Add a course if not already present
    void addCourse(const Course& course) {
        for (const auto& c : courses) {
            if (c.startTime == course.startTime && c.endTime == course.endTime) {
                return; // Course already exists
            }
        }
        courses.push_back(course);
    }

    // Remove a course by matching start and end times
    void removeCourse(const Course& course) {
        for (auto it = courses.begin(); it != courses.end(); ++it) {
            if (it->startTime == course.startTime && it->endTime == course.endTime) {
                courses.erase(it);
                return;
            }
        }
    }

    // Check if the classroom is free at the specified time
    bool isFreeAt(const std::string& checkTimeStr) {
        // Parse the input time string into a time_point
        std::istringstream iss(checkTimeStr);
        std::chrono::system_clock::time_point tp;
        tp = std::chrono::from_stream(iss);
        if (!iss.eof() || !iss.good()) {
            return false; // Parsing failed
        }

        // Convert to seconds for easier comparison
        auto checkTime = std::chrono::time_point_cast<std::chrono::seconds>(tp);

        for (const auto& course : courses) {
            // Convert course times to seconds
            auto courseStartTime = std::chrono::time_point_cast<std::chrono::seconds>(course.startTime);
            auto courseEndTime = std::chrono::time_point_cast<std::chrono::seconds>(course.endTime);

            // Check if the checkTime falls within the course's active time
            if (!(checkTime < courseStartTime) && !(checkTime > courseEndTime)) {
                return false; // Classroom is not free
            }
        }
        return true; // Classroom is free
    }

    // Check if a new course conflicts with existing courses
    bool checkCourseConflict(const Course& newCourse) {
        auto newStart = std::chrono::time_point_cast<std::chrono::seconds>(newCourse.startTime);
        auto newEnd = std::chrono::time_point_cast<std::chrono::seconds>(newCourse.endTime);

        for (const auto& course : courses) {
            auto courseStart = std::chrono::time_point_cast<std::chrono::seconds>(course.startTime);
            auto courseEnd = std::chrono::time_point_cast<std::chrono::seconds>(course.endTime);

            // Check for overlap between new course and existing course
            if (!(newEnd < courseStart) && !(newStart > courseEnd)) {
                return false; // Conflict detected
            }
        }
        return true; // No conflict
    }
};