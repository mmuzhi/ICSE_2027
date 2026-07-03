#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <optional>

class Student {
private:
    std::string name;
    int grade;
    std::string major;
    std::unordered_map<std::string, int> courses;

public:
    Student(std::string name, int grade, std::string major)
        : name(std::move(name)), grade(grade), major(std::move(major)) {}

    std::string getName() const { return name; }

    void addCourseScore(const std::string& course, int score) {
        courses[course] = score;
    }

    std::optional<double> calculateGPA() const {
        if (courses.empty()) {
            return std::nullopt;
        }
        int totalScore = 0;
        for (const auto& [c, score] : courses) {
            totalScore += score;
        }
        return static_cast<double>(totalScore) / courses.size();
    }

    bool hasFailingCourse() const {
        for (const auto& [c, score] : courses) {
            if (score < 60) {
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

class AssessmentSystem {
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
        for (auto& [n, student] : students) {
            if (student.hasFailingCourse()) {
                failingStudents.push_back(student.getName());
            }
        }
        return failingStudents;
    }

    std::optional<double> getCourseAverage(const std::string& course) {
        int totalScore = 0;
        int count = 0;
        for (auto& [n, student] : students) {
            auto score = student.getCourseScore(course);
            if (score.has_value()) {
                totalScore += score.value();
                count++;
            }
        }
        return count > 0 ? std::optional<double>(static_cast<double>(totalScore) / count) : std::nullopt;
    }

    std::string getTopStudent() {
        std::string topStudent;
        double topGPA = 0;
        for (auto& [n, student] : students) {
            auto gpa = student.calculateGPA();
            if (gpa.has_value() && gpa.value() > topGPA) {
                topGPA = gpa.value();
                topStudent = student.getName();
            }
        }
        return topStudent;
    }
};

static void printJavaDouble(double d) {
    long long i = static_cast<long long>(d);
    if (d == static_cast<double>(i)) {
        std::cout << i << ".0" << std::endl;
    } else {
        std::cout << d << std::endl;
    }
}

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
        if (i > 0) std::cout << ", ";
        std::cout << failing[i];
    }
    std::cout << "]" << std::endl;

    auto avg1 = system.getCourseAverage("course 1");
    if (avg1.has_value()) printJavaDouble(avg1.value());
    else std::cout << "null" << std::endl;

    auto avg2 = system.getCourseAverage("course 2");
    if (avg2.has_value()) printJavaDouble(avg2.value());
    else std::cout << "null" << std::endl;

    auto gpa1 = system.getGPA("student 1");
    if (gpa1.has_value()) printJavaDouble(gpa1.value());
    else std::cout << "null" << std::endl;

    auto gpa2 = system.getGPA("student 2");
    if (gpa2.has_value()) printJavaDouble(gpa2.value());
    else std::cout << "null" << std::endl;

    std::string top = system.getTopStudent();
    if (top.empty()) std::cout << "null" << std::endl;
    else std::cout << top << std::endl;

    return 0;
}