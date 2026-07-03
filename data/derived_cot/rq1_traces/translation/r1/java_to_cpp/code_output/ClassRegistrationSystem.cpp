#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <exception>

class NoSuchElementException : public std::exception {
public:
    const char* what() const noexcept override {
        return "NoSuchElementException";
    }
};

class ClassRegistrationSystem {
public:
    class Student {
    public:
        Student(std::string name, std::string major) : name(std::move(name)), major(std::move(major)) {}
        const std::string& getName() const { return name; }
        const std::string& getMajor() const { return major; }

        bool operator==(const Student& other) const {
            return name == other.name && major == other.major;
        }

    private:
        std::string name;
        std::string major;
    };

private:
    std::vector<Student> students;
    std::unordered_map<std::string, std::vector<std::string>> studentsRegistrationClasses;

public:
    ClassRegistrationSystem() = default;

    int registerStudent(const Student& student) {
        if (std::find(students.begin(), students.end(), student) != students.end()) {
            return 0;
        }
        students.push_back(student);
        return 1;
    }

    std::vector<std::string>& registerClass(const std::string& studentName, const std::string& className) {
        studentsRegistrationClasses[studentName].push_back(className);
        return studentsRegistrationClasses[studentName];
    }

    std::vector<std::string> getStudentsByMajor(const std::string& major) {
        std::vector<std::string> studentList;
        for (const auto& student : students) {
            if (student.getMajor() == major) {
                studentList.push_back(student.getName());
            }
        }
        return studentList;
    }

    std::vector<std::string> getAllMajor() {
        std::unordered_set<std::string> majorSet;
        for (const auto& student : students) {
            majorSet.insert(student.getMajor());
        }
        return std::vector<std::string>(majorSet.begin(), majorSet.end());
    }

    std::string getMostPopularClassInMajor(const std::string& major) {
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
            throw NoSuchElementException();
        }

        auto maxIt = std::max_element(classCount.begin(), classCount.end(),
            [](const auto& a, const auto& b) {
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