#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <optional>
#include <sstream>
#include <iomanip>
#include <cmath>

// Helper: convert double to string like Java's Double.toString
static std::string doubleToString(double d) {
    if (std::isnan(d)) return "NaN";
    if (std::isinf(d)) return (d > 0) ? "Infinity" : "-Infinity";
    std::ostringstream oss;
    // Use fixed with enough precision to represent the number exactly.
    oss << std::fixed << std::setprecision(16) << d;
    std::string s = oss.str();
    auto dot = s.find('.');
    if (dot != std::string::npos) {
        // Remove trailing zeros after decimal point
        auto last = s.find_last_not_of('0');
        if (last > dot) {
            s.erase(last + 1);
        } else {
            // All zeros after dot: keep one zero to indicate decimal.
            s.erase(dot + 2);
        }
    } else {
        // No decimal point: add ".0"
        s += ".0";
    }
    return s;
}

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
        if (courses.empty()) return std::nullopt;
        int totalScore = 0;
        for (const auto& p : courses) {
            totalScore += p.second;
        }
        return static_cast<double>(totalScore) / courses.size();
    }

    bool hasFailingCourse() const {
        for (const auto& p : courses) {
            if (p.second < 60) return true;
        }
        return false;
    }

    std::optional<int> getCourseScore(const std::string& course) const {
        auto it = courses.find(course);
        if (it != courses.end()) return it->second;
        return std::nullopt;
    }
};

class AssessmentSystem {
private:
    std::unordered_map<std::string, Student> students;

public:
    void addStudent(const std::string& name, int grade, const std::string& major) {
        students.emplace(name, Student(name, grade, major));
    }

    void addCourseScore(const std::string& name, const std::string& course, int score) {
        auto it = students.find(name);
        if (it != students.end()) {
            it->second.addCourseScore(course, score);
        }
    }

    std::optional<std::string> getGPA(const std::string& name) const {
        auto it = students.find(name);
        if (it == students.end()) return std::nullopt;
        auto gpa = it->second.calculateGPA();
        if (!gpa) return std::nullopt;
        return doubleToString(*gpa);
    }

    std::vector<std::string> getAllStudentsWithFailCourse() const {
        std::vector<std::string> failing;
        for (const auto& p : students) {
            if (p.second.hasFailingCourse()) {
                failing.push_back(p.second.getName());
            }
        }
        return failing;
    }

    std::optional<std::string> getCourseAverage(const std::string& course) const {
        int totalScore = 0;
        int count = 0;
        for (const auto& p : students) {
            auto score = p.second.getCourseScore(course);
            if (score) {
                totalScore += *score;
                ++count;
            }
        }
        if (count == 0) return std::nullopt;
        return doubleToString(static_cast<double>(totalScore) / count);
    }

    std::optional<std::string> getTopStudent() const {
        std::optional<std::string> topStudent;
        double topGPA = 0.0;
        for (const auto& p : students) {
            auto gpa = p.second.calculateGPA();
            if (gpa && *gpa > topGPA) {
                topGPA = *gpa;
                topStudent = p.second.getName();
            }
        }
        return topStudent;
    }
};

// Helper to print a vector<string> like Java's ArrayList.toString()
static void printVector(const std::vector<std::string>& v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << v[i];
    }
    std::cout << "]";
}

int main() {
    AssessmentSystem system;
    system.addStudent("student 1", 3, "SE");
    system.addStudent("student 2", 2, "SE");
    system.addCourseScore("student 1", "course 1", 86);
    system.addCourseScore("student 2", "course 1", 59);
    system.addCourseScore("student 1", "course 2", 78);
    system.addCourseScore("student 2", "course 2", 90);

    // getAllStudentsWithFailCourse
    printVector(system.getAllStudentsWithFailCourse());
    std::cout << std::endl;

    // getCourseAverage
    auto avg1 = system.getCourseAverage("course 1");
    std::cout << (avg1 ? *avg1 : "null") << std::endl;

    auto avg2 = system.getCourseAverage("course 2");
    std::cout << (avg2 ? *avg2 : "null") << std::endl;

    // getGPA
    auto gpa1 = system.getGPA("student 1");
    std::cout << (gpa1 ? *gpa1 : "null") << std::endl;

    auto gpa2 = system.getGPA("student 2");
    std::cout << (gpa2 ? *gpa2 : "null") << std::endl;

    // getTopStudent
    auto top = system.getTopStudent();
    std::cout << (top ? *top : "null") << std::endl;

    return 0;
}