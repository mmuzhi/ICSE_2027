#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <optional>

namespace org::example {

class AssessmentSystem {
public:
    // Nested class Student
    class Student {
    private:
        std::string name;
        int grade;
        std::string major;
        std::unordered_map<std::string, int> courses;

    public:
        Student(const std::string& name, int grade, const std::string& major) 
            : name(name), grade(grade), major(major) {}

        const std::string& getName() const { return name; }

        void addCourseScore(const std::string& course, int score) {
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
            if (it == courses.end()) {
                return std::nullopt;
            }
            return it->second;
        }
    };

    std::unordered_map<std::string, Student> students;

    AssessmentSystem() = default;

    void addStudent(const std::string& name, int grade, const std::string& major) {
        students[name] = Student(name, grade, major);
    }

    void addCourseScore(const std::string& name, const std::string& course, int score) {
        if (students.find(name) != students.end()) {
            students[name].addCourseScore(course, score);
        }
    }

    std::optional<double> getGPA(const std::string& name) const {
        if (students.find(name) == students.end()) {
            return std::nullopt;
        }
        return students.at(name).calculateGPA();
    }

    std::vector<std::string> getAllStudentsWithFailCourse() const {
        std::vector<std::string> failingStudents;
        for (const auto& student : students) {
            if (student.second.hasFailingCourse()) {
                failingStudents.push_back(student.first);
            }
        }
        return failingStudents;
    }

    std::optional<double> getCourseAverage(const std::string& course) const {
        if (students.empty()) {
            return std::nullopt;
        }

        int totalScore = 0;
        int count = 0;
        for (const auto& student : students) {
            auto score = student.second.getCourseScore(course);
            if (score.has_value()) {
                totalScore += score.value();
                count++;
            }
        }
        if (count == 0) {
            return std::nullopt;
        }
        return static_cast<double>(totalScore) / count;
    }

    std::optional<std::string> getTopStudent() const {
        if (students.empty()) {
            return std::nullopt;
        }

        std::string topStudent;
        double topGPA = 0.0;

        for (const auto& student : students) {
            auto gpa = student.second.calculateGPA();
            if (gpa.has_value() && gpa.value() > topGPA) {
                topGPA = gpa.value();
                topStudent = student.first;
            }
        }

        return std::make_optional(topStudent);
    }

    static void main() {
        AssessmentSystem system;
        system.addStudent("student 1", 3, "SE");
        system.addStudent("student 2", 2, "SE");
        system.addCourseScore("student 1", "course 1", 86);
        system.addCourseScore("student 2", "course 1", 59);
        system.addCourseScore("student 1", "course 2", 78);
        system.addCourseScore("student 2", "course 2", 90);

        // The main method in C++ should be in a different way, but we are just translating the given code.
        // We'll print the results.
        auto failingStudents = system.getAllStudentsWithFailCourse();
        std::cout << "Failing students: ";
        for (const auto& student : failingStudents) {
            std::cout << student << " ";
        }
        std::cout << std::endl;

        auto avgCourse1 = system.getCourseAverage("course 1");
        if (avgCourse1.has_value()) {
            std::cout << "Course 1 average: " << avgCourse1.value() << std::endl;
        } else {
            std::cout << "Course 1 average: null" << std::endl;
        }

        auto avgCourse2 = system.getCourseAverage("course 2");
        if (avgCourse2.has_value()) {
            std::cout << "Course 2 average: " << avgCourse2.value() << std::endl;
        } else {
            std::cout << "Course 2 average: null" << std::endl;
        }

        auto gpa1 = system.getGPA("student 1");
        if (gpa1.has_value()) {
            std::cout << "Student 1 GPA: " << gpa1.value() << std::endl;
        } else {
            std::cout << "Student 1 GPA: null" << std::endl;
        }

        auto gpa2 = system.getGPA("student 2");
        if (gpa2.has_value()) {
            std::cout << "Student 2 GPA: " << gpa2.value() << std::endl;
        } else {
            std::cout << "Student 2 GPA: null" << std::endl;
        }

        auto top = system.getTopStudent();
        if (top.has_value()) {
            std::cout << "Top student: " << top.value() << std::endl;
        } else {
            std::cout << "Top student: null" << std::endl;
        }
    }
};

} // namespace org::example

int main() {
    org::example::AssessmentSystem::main();
    return 0;
}