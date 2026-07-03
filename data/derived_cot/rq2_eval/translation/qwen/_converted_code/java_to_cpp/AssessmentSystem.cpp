#include <iostream>
#include <map>
#include <vector>
#include <optional>
#include <string>

class AssessmentSystem {
private:
    std::map<std::string, Student> students;

public:
    AssessmentSystem() = default;

    void add_student(const std::string& name, int grade, const std::string& major) {
        students[name] = Student(name, grade, major);
    }

    void add_course_score(const std::string& name, const std::string& course, int score) {
        if (students.find(name) != students.end()) {
            students[name].add_course_score(course, score);
        }
    }

    std::optional<double> getGPA(const std::string& name) {
        if (students.find(name) != students.end()) {
            return students[name].calculateGPA();
        }
        return std::nullopt;
    }

    std::vector<std::string> getAllStudentsWithFailCourse() {
        std::vector<std::string> failingStudents;
        for (const auto& entry : students) {
            if (entry.second.hasFailingCourse()) {
                failingStudents.push_back(entry.first);
            }
        }
        return failingStudents;
    }

    std::optional<double> getCourseAverage(const std::string& course) {
        int totalScore = 0;
        int count = 0;
        for (const auto& entry : students) {
            auto score = entry.second.getCourseScore(course);
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

    std::optional<std::string> getTopStudent() {
        std::string topStudent;
        double topGPA = -1.0; // Initialize to negative since GPA >= 0
        for (const auto& entry : students) {
            auto gpa = entry.second.calculateGPA();
            if (gpa.has_value() && gpa.value() > topGPA) {
                topGPA = gpa.value();
                topStudent = entry.first;
            }
        }
        if (topStudent.empty()) {
            return std::nullopt;
        }
        return topStudent;
    }

    class Student {
    private:
        std::string name;
        int grade;
        std::string major;
        std::map<std::string, int> courses;

    public:
        Student(const std::string& name, int grade, const std::string& major)
            : name(name), grade(grade), major(major) {}

        const std::string& getName() const { return name; }

        void add_course_score(const std::string& course, int score) {
            courses[course] = score;
        }

        std::optional<double> calculateGPA() const {
            if (courses.empty()) {
                return std::nullopt;
            }
            int totalScore = 0;
            for (const auto& score : courses) {
                totalScore += score.second;
            }
            return static_cast<double>(totalScore) / courses.size();
        }

        bool hasFailingCourse() const {
            for (const auto& score : courses) {
                if (score.second < 60) {
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
};

int main() {
    AssessmentSystem system;
    system.add_student("student 1", 3, "SE");
    system.add_student("student 2", 2, "SE");
    system.add_course_score("student 1", "course 1", 86);
    system.add_course_score("student 2", "course 1", 59);
    system.add_course_score("student 1", "course 2", 78);
    system.add_course_score("student 2", "course 2", 90);

    std::vector<std::string> failingStudents = system.getAllStudentsWithFailCourse();
    for (const auto& student : failingStudents) {
        std::cout << student << std::endl;
    }

    auto avg1 = system.getCourseAverage("course 1");
    if (avg1.has_value()) {
        std::cout << avg1.value() << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }

    auto avg2 = system.getCourseAverage("course 2");
    if (avg2.has_value()) {
        std::cout << avg2.value() << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }

    auto gpa1 = system.getGPA("student 1");
    if (gpa1.has_value()) {
        std::cout << gpa1.value() << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }

    auto gpa2 = system.getGPA("student 2");
    if (gpa2.has_value()) {
        std::cout << gpa2.value() << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }

    auto topStudent = system.getTopStudent();
    if (topStudent.has_value()) {
        std::cout << topStudent.value() << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }

    return 0;
}