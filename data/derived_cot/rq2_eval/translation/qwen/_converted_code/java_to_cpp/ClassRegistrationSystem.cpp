#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <utility>

class ClassRegistrationSystem {
private:
    struct Student {
        std::string name;
        std::string major;

        bool operator==(const Student& other) const {
            return name == other.name && major == other.major;
        }
    };

    std::vector<Student> students;
    std::unordered_map<std::string, std::vector<std::string>> studentsRegistrationClasses;

public:
    ClassRegistrationSystem() = default;

    int register_student(const Student& student) {
        if (std::find(students.begin(), students.end(), student) != students.end()) {
            return 0;
        }
        students.push_back(student);
        return 1;
    }

    std::vector<std::string> registerClass(const std::string& studentName, const std::string& className) {
        auto& studentClasses = studentsRegistrationClasses[studentName];
        studentClasses.push_back(className);
        return studentClasses;
    }

    std::vector<std::string> getStudentsByMajor(const std::string& major) {
        std::vector<std::string> result;
        for (const auto& student : students) {
            if (student.major == major) {
                result.push_back(student.name);
            }
        }
        return result;
    }

    std::vector<std::string> getAllMajor() {
        std::set<std::string> uniqueMajors;
        for (const auto& student : students) {
            uniqueMajors.insert(student.major);
        }
        return std::vector<std::string>(uniqueMajors.begin(), uniqueMajors.end());
    }

    std::string get_most_popular_class_in_major(const std::string& major) {
        std::map<std::string, int> classCount;
        for (const auto& student : students) {
            if (student.major == major) {
                const auto& classes = studentsRegistrationClasses.find(student.name);
                if (classes != studentsRegistrationClasses.end()) {
                    for (const auto& className : classes->second) {
                        classCount[className]++;
                    }
                }
            }
        }
        if (classCount.empty()) return "";
        auto maxEntry = *classCount.begin();
        for (const auto& entry : classCount) {
            if (entry.second > maxEntry.second) {
                maxEntry = entry;
            }
        }
        return maxEntry.first;
    }

    // Setter methods for tests
    void setStudents(const std::vector<Student>& students) {
        this->students = students;
    }

    void setStudentClasses(const std::unordered_map<std::string, std::vector<std::string>>& studentClasses) {
        this->studentsRegistrationClasses = studentClasses;
    }
};