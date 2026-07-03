#include <string>
#include <unordered_map>
#include <vector>
#include <optional>

struct Student {
    std::string name;
    int grade;
    std::string major;
    std::unordered_map<std::string, int> courses;
};

class AssessmentSystem {
private:
    std::unordered_map<std::string, Student> students;

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

    std::optional<double> get_gpa(const std::string& name) const {
        auto it = students.find(name);
        if (it != students.end() && !it->second.courses.empty()) {
            double sum = 0;
            for (const auto& pair : it->second.courses) {
                sum += pair.second;
            }
            return sum / it->second.courses.size();
        }
        return std::nullopt;
    }

    std::vector<std::string> get_all_students_with_fail_course() const {
        std::vector<std::string> fail_students;
        for (const auto& pair : students) {
            const std::string& name = pair.first;
            const Student& student = pair.second;
            for (const auto& course_pair : student.courses) {
                if (course_pair.second < 60) {
                    fail_students.push_back(name);
                    break;
                }
            }
        }
        return fail_students;
    }

    std::optional<double> get_course_average(const std::string& course) const {
        double total = 0;
        int count = 0;
        for (const auto& pair : students) {
            const Student& student = pair.second;
            auto course_it = student.courses.find(course);
            if (course_it != student.courses.end()) {
                total += course_it->second;
                count += 1;
            }
        }
        if (count > 0) {
            return total / count;
        }
        return std::nullopt;
    }

    std::optional<std::string> get_top_student() const {
        std::optional<std::string> top_student = std::nullopt;
        double top_gpa = 0;
        for (const auto& pair : students) {
            const std::string& name = pair.first;
            std::optional<double> gpa_opt = get_gpa(name);
            if (gpa_opt.has_value() && gpa_opt.value() > top_gpa) {
                top_gpa = gpa_opt.value();
                top_student = name;
            }
        }
        return top_student;
    }
};