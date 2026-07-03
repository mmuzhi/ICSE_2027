#include <unordered_map>
#include <vector>
#include <optional>
#include <string>

struct Student {
    std::string name;
    int grade;
    std::string major;
    std::unordered_map<std::string, int> courses;
};

class AssessmentSystem {
public:
    AssessmentSystem() = default;

    void add_student(const std::string& name, int grade, const std::string& major) {
        students_[name] = {name, grade, major, {}};
    }

    void add_course_score(const std::string& name, const std::string& course, int score) {
        if (students_.find(name) != students_.end()) {
            students_[name].courses[course] = score;
        }
    }

    std::optional<double> get_gpa(const std::string& name) const {
        auto it = students_.find(name);
        if (it == students_.end()) {
            return std::nullopt;
        }
        const auto& student = it->second;
        if (student.courses.empty()) {
            return std::nullopt;
        }
        double total = 0;
        for (const auto& [course, score] : student.courses) {
            total += score;
        }
        return total / student.courses.size();
    }

    std::vector<std::string> get_all_students_with_fail_course() const {
        std::vector<std::string> result;
        for (const auto& [name, student] : students_) {
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
        double total = 0;
        int count = 0;
        for (const auto& [name, student] : students_) {
            if (student.courses.find(course) != student.courses.end()) {
                total += student.courses.at(course);
                count++;
            }
        }
        if (count == 0) {
            return std::nullopt;
        }
        return total / count;
    }

    std::optional<std::string> get_top_student() const {
        std::optional<std::string> top_student;
        double top_gpa = -1;
        for (const auto& [name, student] : students_) {
            auto gpa = get_gpa(name);
            if (gpa.has_value() && gpa.value() > top_gpa) {
                top_gpa = gpa.value();
                top_student = name;
            }
        }
        return top_student;
    }

private:
    std::unordered_map<std::string, Student> students_;
};