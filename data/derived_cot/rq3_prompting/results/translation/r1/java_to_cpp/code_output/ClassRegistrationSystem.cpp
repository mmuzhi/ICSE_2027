#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <utility> // for std::pair

class ClassRegistrationSystem {
public:
    class Student {
    public:
        std::string name;
        std::string major;

        Student(std::string name, std::string major)
            : name(std::move(name)), major(std::move(major)) {}

        const std::string& getName() const { return name; }
        const std::string& getMajor() const { return major; }

        bool operator==(const Student& other) const {
            return name == other.name && major == other.major;
        }
    };

    // For using Student in unordered_set or unordered_map if needed.
    struct StudentHash {
        std::size_t operator()(const Student& s) const {
            return std::hash<std::string>()(s.name) ^ (std::hash<std::string>()(s.major) << 1);
        }
    };

    ClassRegistrationSystem() = default;

    int registerStudent(const Student& student) {
        if (std::find(students.begin(), students.end(), student) != students.end()) {
            return 0;
        } else {
            students.push_back(student);
            return 1;
        }
    }

    std::vector<std::string>& registerClass(const std::string& studentName, const std::string& className) {
        auto it = studentsRegistrationClasses.find(studentName);
        if (it != studentsRegistrationClasses.end()) {
            it->second.push_back(className);
            return it->second;
        } else {
            std::vector<std::string> newList = {className};
            auto [insertedIt, _] = studentsRegistrationClasses.emplace(studentName, std::move(newList));
            return insertedIt->second;
        }
    }

    std::vector<std::string> getStudentsByMajor(const std::string& major) const {
        std::vector<std::string> studentList;
        for (const auto& student : students) {
            if (student.getMajor() == major) {
                studentList.push_back(student.getName());
            }
        }
        return studentList;
    }

    std::vector<std::string> getAllMajor() const {
        std::unordered_set<std::string> majorSet;
        for (const auto& student : students) {
            majorSet.insert(student.getMajor());
        }
        return std::vector<std::string>(majorSet.begin(), majorSet.end());
    }

    std::string getMostPopularClassInMajor(const std::string& major) const {
        std::unordered_map<std::string, int> classCount;
        for (const auto& student : students) {
            if (student.getMajor() == major) {
                auto it = studentsRegistrationClasses.find(student.getName());
                if (it != studentsRegistrationClasses.end()) {
                    for (const auto& className : it->second) {
                        classCount[className]++;
                    }
                }
            }
        }
        if (classCount.empty()) {
            throw std::runtime_error("No classes found for the given major");
        }
        auto maxIt = std::max_element(
            classCount.begin(), classCount.end(),
            [](const std::pair<const std::string, int>& a, const std::pair<const std::string, int>& b) {
                return a.second < b.second;
            });
        return maxIt->first;
    }

    // Setter methods for tests
    void setStudents(const std::vector<Student>& s) {
        students = s;
    }

    void setStudentClasses(const std::unordered_map<std::string, std::vector<std::string>>& sc) {
        studentsRegistrationClasses = sc;
    }

private:
    std::vector<Student> students;
    std::unordered_map<std::string, std::vector<std::string>> studentsRegistrationClasses;
};