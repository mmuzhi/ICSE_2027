#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <optional>
#include <cmath>
#include <type_traits>

class AssessmentSystem {
public:
    class Student {
    private:
        std::string name;
        int grade;
        std::string major;
        std::unordered_map<std::string, int> courses;

    public:
        Student(const std::string& name, int grade, const std::string& major)
            : name(name), grade(grade), major(major) {}

        const std::string& getName() const {
            return name;
        }

        void addCourseScore(const std::string& course, int score) {
            courses[course] = score;
        }

        std::optional<double> calculateGPA() const {
            if (courses.empty()) {
                return std::nullopt;
            }
            int totalScore = 0;
            for (const auto& pair : courses) {
                totalScore += pair.second;
            }
            return static_cast<double>(totalScore) / courses.size();
        }

        bool hasFailingCourse() const {
            for (const auto& pair : courses) {
                if (pair.second < 60) {
                    return true;
                }
            }
            return false;
        }

        std::optional<int> getCourseScore(const std::string& course) const {
            auto it = courses.find(course);
            if (it != courses.end()) {
                return it->second;
            }
            return std::nullopt;
        }
    };

private:
    std::unordered_map<std::string, Student> students;

public:
    AssessmentSystem() = default;

    void addStudent(const std::string& name, int grade, const std::string& major) {
        students.emplace(name, Student(name, grade, major));
    }

    void addCourseScore(const std::string& name, const std::string& course, int score) {
        auto it = students.find(name);
        if (it != students.end()) {
            it->second.addCourseScore(course, score);
        }
    }

    std::optional<double> getGPA(const std::string& name) {
        auto it = students.find(name);
        if (it != students.end()) {
            return it->second.calculateGPA();
        }
        return std::nullopt;
    }

    std::vector<std::string> getAllStudentsWithFailCourse() {
        std::vector<std::string> failingStudents;
        for (const auto& pair : students) {
            if (pair.second.hasFailingCourse()) {
                failingStudents.push_back(pair.first);
            }
        }
        return failingStudents;
    }

    std::optional<double> getCourseAverage(const std::string& course) {
        int totalScore = 0;
        int count = 0;
        for (const auto& pair : students) {
            std::optional<int> score = pair.second.getCourseScore(course);
            if (score) {
                totalScore += *score;
                count++;
            }
        }
        if (count > 0) {
            return static_cast<double>(totalScore) / count;
        }
        return std::nullopt;
    }

    std::optional<std::string> getTopStudent() {
        std::optional<std::string> topStudent = std::nullopt;
        double topGPA = 0.0;
        for (const auto& pair : students) {
            std::optional<double> gpa = pair.second.calculateGPA();
            if (gpa && *gpa > topGPA) {
                topGPA = *gpa;
                topStudent = pair.first;
            }
        }
        return topStudent;
    }
};

int main() {
    AssessmentSystem system;
    system.addStudent("student 1", 3, "SE");
    system.addStudent("student 2", 2, "SE");
    system.addCourseScore("student 1", "course 1", 86);
    system.addCourseScore("student 2", "course 1", 59);
    system.addCourseScore("student 1", "course 2", 78);
    system.addCourseScore("student 2", "course 2", 90);

    auto failing = system.getAllStudentsWithFailCourse();
    std::cout << "[";
    for (size_t i = 0; i < failing.size(); i++) {
        std::cout << failing[i];
        if (i < failing.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;

    auto printOptional = [](const auto& opt) {
        if (!opt) {
            std::cout << "null" << std::endl;
            return;
        }
        using T = std::decay_t<decltype(*opt)>;
        if constexpr (std::is_same_v<T, double>) {
            if (std::floor(*opt) == *opt) {
                std::cout << static_cast<long long>(*opt) << ".0" << std::endl;
            } else {
                std::cout << *opt << std::endl;
            }
        } else {
            std::cout << *opt << std::endl;
        }
    };

    printOptional(system.getCourseAverage("course 1"));
    printOptional(system.getCourseAverage("course 2"));
    printOptional(system.getGPA("student 1"));
    printOptional(system.getGPA("student 2"));
    printOptional(system.getTopStudent());

    return 0;
}