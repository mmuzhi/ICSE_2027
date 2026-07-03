#include <vector>
#include <unordered_map>
#include <string>
#include <set>
#include <algorithm>

class ClassRegistrationSystem {
private:
    struct Student {
        std::string name;
        std::string major;

        Student(std::string n, std::string m) : name(n), major(m) {}
    };

    std::vector<Student> students;
    std::unordered_map<std::string, std::vector<std::string>> studentsRegistrationClasses;

public:
    ClassRegistrationSystem() = default;

    int registerStudent(const Student& student) {
        for (const auto& s : students) {
            if (s.name == student.name && s.major == student.major) {
                return 0;
            }
        }
        students.push_back(student);
        return 1;
    }

    std::vector<std::string> registerClass(const std::string& studentName, const std::string& className) {
        if (studentsRegistrationClasses.find(studentName) == studentsRegistrationClasses.end()) {
            studentsRegistrationClasses[studentName] = { className };
        } else {
            studentsRegistrationClasses[studentName].push_back(className);
        }
        return studentsRegistrationClasses[studentName];
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

    std::string getMostPopularClassInMajor(const std::string& major) {
        std::unordered_map<std::string, int> classCount;

        for (const auto& student : students) {
            if (student.major == major) {
                auto it = studentsRegistrationClasses.find(student.name);
                if (it != studentsRegistrationClasses.end()) {
                    for (const auto& className : it->second) {
                        classCount[className]++;
                    }
                }
            }
        }

        if (classCount.empty()) {
            return "";
        }

        std::string mostPopular;
        int maxCount = 0;
        for (const auto& entry : classCount) {
            if (entry.second > maxCount) {
                maxCount = entry.second;
                mostPopular = entry.first;
            }
        }

        return mostPopular;
    }

    void setStudents(std::vector<Student> students) {
        this->students = std::move(students);
    }

    void setStudentClasses(std::unordered_map<std::string, std::vector<std::string>> studentClasses) {
        this->studentsRegistrationClasses = std::move(studentClasses);
    }
};