#include <unordered_map>
#include <string>
#include <vector>
#include <optional>
#include <algorithm>

struct Student {
    int grade;
    std::string major;
    std::unordered_map<std::string, int> courses;
};

class AssessmentSystem {
public:
    AssessmentSystem() = default;

    void add_student(const std::string& name, int grade, const std::string& major) {
        students[name] = {grade, major, {}};
    }

    void add_course_score(const std::string& name, const std::string& course, int score) {
        if (students.find(name) != students.end()) {
            students[name].courses[course] = score;
        }
    }

    std::optional<double> get_gpa(const std::string& name) const {
        if (students.find(name) == students.end()) {
            return std::nullopt;
        }
        const auto& student = students.at(name);
        if (student.courses.empty()) {
            return std::nullopt;
        }
        double sum = 0.0;
        for (const auto& score : student.courses) {
            sum += score.second;
        }
        return sum / student.courses.size();
    }

    std::vector<std::string> get_all_students_with_fail_course() const {
        std::vector<std::string> result;
        for (const auto& [name, student] : students) {
            for (const auto& [course, score] : student.courses) {
                if (score < 60) {
                    result.push_back(name);
                    break;
                }
            }
        }
        return result;
    }

    std::optional<double> get_course_average(const std::string& course) const {
        if (students.empty()) {
            return std::nullopt;
        }
        double sum = 0.0;
        int count = 0;
        for (const auto& [name, student] : students) {
            if (student.courses.find(course) != student.courses.end()) {
                sum += student.courses.at(course);
                count++;
            }
        }
        if (count == 0) {
            return std::nullopt;
        }
        return sum / count;
    }

    std::optional<std::string> get_top_student() const {
        if (students.empty()) {
            return std::nullopt;
        }
        std::string top_name = "";
        double top_gpa = -1.0;
        for (const auto& [name, student] : students) {
            auto current_gpa = get_gpa(name);
            if (!current_gpa.has_value()) {
                continue;
            }
            if (current_gpa.value() > top_gpa) {
                top_gpa = current_gpa.value();
                top_name = name;
            }
        }
        if (top_gpa == -1.0) {
            return std::nullopt;
        }
        return top_name;
    }

private:
    std::unordered_map<std::string, Student> students;
};