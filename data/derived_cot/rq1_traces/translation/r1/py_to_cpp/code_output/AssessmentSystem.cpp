#include <vector>
#include <string>
#include <unordered_map>
#include <optional>

class AssessmentSystem {
private:
    struct Student {
        std::string name;
        int grade;
        std::string major;
        std::unordered_map<std::string, int> courses;
    };

    std::vector<std::string> insertion_order;
    std::unordered_map<std::string, Student> students;

public:
    void add_student(const std::string& name, int grade, const std::string& major) {
        if (students.find(name) == students.end()) {
            insertion_order.push_back(name);
        }
        students[name] = Student{name, grade, major, {}};
    }

    void add_course_score(const std::string& name, const std::string& course, int score) {
        auto it = students.find(name);
        if (it != students.end()) {
            it->second.courses[course] = score;
        }
    }

    std::optional<double> get_gpa(const std::string& name) {
        auto it = students.find(name);
        if (it == students.end()) {
            return std::nullopt;
        }
        const auto& courses = it->second.courses;
        if (courses.empty()) {
            return std::nullopt;
        }
        double sum = 0.0;
        for (const auto& pair : courses) {
            sum += pair.second;
        }
        return sum / courses.size();
    }

    std::vector<std::string> get_all_students_with_fail_course() {
        std::vector<std::string> result;
        for (const auto& name : insertion_order) {
            const auto& student = students.at(name);
            for (const auto& course : student.courses) {
                if (course.second < 60) {
                    result.push_back(name);
                    break;
                }
            }
        }
        return result;
    }

    std::optional<double> get_course_average(const std::string& course) {
        double total = 0.0;
        int count = 0;
        for (const auto& name : insertion_order) {
            const auto& student = students.at(name);
            auto it = student.courses.find(course);
            if (it != student.courses.end()) {
                total += it->second;
                count++;
            }
        }
        if (count == 0) {
            return std::nullopt;
        }
        return total / count;
    }

    std::optional<std::string> get_top_student() {
        std::optional<std::string> top_student = std::nullopt;
        double top_gpa = 0.0;

        for (const auto& name : insertion_order) {
            auto gpa_opt = get_gpa(name);
            if (gpa_opt) {
                double gpa = *gpa_opt;
                if (gpa > top_gpa) {
                    top_gpa = gpa;
                    top_student = name;
                }
            }
        }

        return top_student;
    }
};