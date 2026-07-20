#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <vector>
#include <optional>

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

        std::string getName() const {
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
        students.insert_or_assign(name, Student(name, grade, major));
    }

    void addCourseScore(const std::string& name, const std::string& course, int score) {
        auto it = students.find(name);
        if (it != students.end()) {
            it->second.addCourseScore(course, score);
        }
    }

    std::optional<double> getGPA(const std::string& name) const {
        auto it = students.find(name);
        if (it != students.end()) {
            return it->second.calculateGPA();
        }
        return std::nullopt;
    }

    std::vector<std::string> getAllStudentsWithFailCourse() const {
        std::vector<std::string> failingStudents;
        for (const auto& pair : students) {
            if (pair.second.hasFailingCourse()) {
                failingStudents.push_back(pair.second.getName());
            }
        }
        return failingStudents;
    }

    std::optional<double> getCourseAverage(const std::string& course) const {
        int totalScore = 0;
        int count = 0;
        for (const auto& pair : students) {
            auto score = pair.second.getCourseScore(course);
            if (score.has_value()) {
                totalScore += score.value();
                count++;
            }
        }
        if (count > 0) {
            return static_cast<double>(totalScore) / count;
        }
        return std::nullopt;
    }

    std::optional<std::string> getTopStudent() const {
        std::optional<std::string> topStudent = std::nullopt;
        double topGPA = 0.0;
        for (const auto& pair : students) {
            auto gpa = pair.second.calculateGPA();
            if (gpa.has_value() && gpa.value() > topGPA) {
                topGPA = gpa.value();
                topStudent = pair.second.getName();
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

    // getAllStudentsWithFailCourse
    auto failing = system.getAllStudentsWithFailCourse();
    std::cout << "[";
    for (size_t i = 0; i < failing.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << failing[i];
    }
    std::cout << "]" << std::endl;

    // getCourseAverage
    auto avg1 = system.getCourseAverage("course 1");
    if (avg1.has_value()) {
        std::cout << std::fixed << std::setprecision(1) << avg1.value() << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }

    auto avg2 = system.getCourseAverage("course 2");
    if (avg2.has_value()) {
        std::cout << std::fixed << std::setprecision(1) << avg2.value() << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }

    // getGPA
    auto gpa1 = system.getGPA("student 1");
    if (gpa1.has_value()) {
        std::cout << std::fixed << std::setprecision(1) << gpa1.value() << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }

    auto gpa2 = system.getGPA("student 2");
    if (gpa2.has_value()) {
        std::cout << std::fixed << std::setprecision(1) << gpa2.value() << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }

    // getTopStudent
    auto top = system.getTopStudent();
    if (top.has_value()) {
        std::cout << top.value() << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }

    return 0;
}