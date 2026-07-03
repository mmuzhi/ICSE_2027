#include <string>
#include <map>
#include <vector>
#include <optional>

class AssessmentSystem {
public:
    struct StudentInfo {
        std::string name;
        int grade;
        std::string major;
        std::map<std::string, int> courses;
    };

private:
    std::map<std::string, StudentInfo> students;

public:
    AssessmentSystem() = default;

    void add_student(const std::string& name, int grade, const std::string& major) {
        students[name] = {name, grade, major, {}};
    }

    void add_course_score(const std::string& name, const std::string& course, int score) {
        auto it = students.find(name);
        if (it != students.end()) {
            it->second.courses[course] = score;
        }
    }

    std::optional<double> get_gpa(const std::string& name) {
        auto it = students.find(name);
        if (it != students.end() && !it->second.courses.empty()) {
            int total = 0;
            for (const auto& [c, s] : it->second.courses) {
                total += s;
            }
            return static_cast<double>(total) / it->second.courses.size();
        }
        return std::nullopt;
    }

    std::vector<std::string> get_all_students_with_fail_course() {
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

    std::optional<double> get_course_average(const std::string& course) {
        int total = 0;
        int count = 0;
        for (const auto& [name, student] : students) {
            auto cit = student.courses.find(course);
            if (cit != student.courses.end()) {
                total += cit->second;
                count++;
            }
        }
        if (count > 0) {
            return static_cast<double>(total) / count;
        }
        return std::nullopt;
    }

    std::optional<std::string> get_top_student() {
        std::optional<std::string> top_student;
        double top_gpa = 0;
        for (const auto& [name, student] : students) {
            auto gpa = get_gpa(name);
            if (gpa.has_value() && gpa.value() > top_gpa) {
                top_gpa = gpa.value();
                top_student = name;
            }
        }
        return top_student;
    }
};