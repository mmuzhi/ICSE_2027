#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <functional>

class ClassRegistrationSystem {
public:
    class Student {
    public:
        std::string name;
        std::string major;

        Student(std::string name, std::string major) : name(std::move(name)), major(std::move(major)) {}

        bool operator==(const Student& other) const {
            return name == other.name && major == other.major;
        }

        struct Hash {
            size_t operator()(const Student& s) const {
                size_t h1 = std::hash<std::string>{}(s.name);
                size_t h2 = std::hash<std::string>{}(s.major);
                return h1 ^ (h2 << 1);
            }
        };
    };

private:
    std::vector<Student> students;
    std::unordered_map<std::string, std::vector<std::string>> studentsRegistrationClasses;

public:
    ClassRegistrationSystem() = default;

    int registerStudent(const Student& student) {
        auto it = std::find(students.begin(), students.end(), student);
        if (it != students.end()) {
            return 0;
        } else {
            students.push_back(student);
            return 1;
        }
    }

    std::vector<std::string> registerClass(const std::string& studentName, const std::string& className) {
        if (studentsRegistrationClasses.find(studentName) != studentsRegistrationClasses.end()) {
            studentsRegistrationClasses[studentName].push_back(className);
        } else {
            studentsRegistrationClasses[studentName] = std::vector<std::string>{className};
        }
        return studentsRegistrationClasses[studentName];
    }

    std::vector<std::string> getStudentsByMajor(const std::string& major) {
        std::vector<std::string> studentList;
        for (const auto& student : students) {
            if (student.major == major) {
                studentList.push_back(student.name);
            }
        }
        return studentList;
    }

    std::vector<std::string> getAllMajor() {
        std::unordered_set<std::string> majorSet;
        for (const auto& student : students) {
            majorSet.insert(student.major);
        }
        return std::vector<std::string>(majorSet.begin(), majorSet.end());
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
        auto maxIt = std::max_element(classCount.begin(), classCount.end(),
            [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                return a.second < b.second;
            });
        return maxIt->first;
    }

    void setStudents(const std::vector<Student>& students) {
        this->students = students;
    }

    void setStudentClasses(const std::unordered_map<std::string, std::vector<std::string>>& studentClasses) {
        this->studentsRegistrationClasses = studentClasses;
    }
};