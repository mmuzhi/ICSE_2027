#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <stdexcept>

struct Student {
    std::string name;
    std::string major;

    bool operator==(const Student& other) const {
        return name == other.name && major == other.major;
    }
};

class ClassRegistrationSystem {
private:
    std::vector<Student> students;
    std::map<std::string, std::vector<std::string>> students_registration_classes;

public:
    ClassRegistrationSystem() = default;

    int register_student(const Student& student) {
        if (std::find(students.begin(), students.end(), student) != students.end()) {
            return 0;
        }
        students.push_back(student);
        return 1;
    }

    std::vector<std::string>& register_class(const std::string& student_name, const std::string& class_name) {
        // If student not in map, insert empty vector
        auto& classes = students_registration_classes[student_name];
        classes.push_back(class_name);
        return classes;
    }

    std::vector<std::string> get_students_by_major(const std::string& major) const {
        std::vector<std::string> result;
        for (const auto& student : students) {
            if (student.major == major) {
                result.push_back(student.name);
            }
        }
        return result;
    }

    std::vector<std::string> get_all_major() const {
        std::vector<std::string> result;
        for (const auto& student : students) {
            if (std::find(result.begin(), result.end(), student.major) == result.end()) {
                result.push_back(student.major);
            }
        }
        return result;
    }

    std::string get_most_popular_class_in_major(const std::string& major) const {
        std::vector<std::string> class_list;
        for (const auto& student : students) {
            if (student.major == major) {
                // Use .at() to throw exception if student not registered, matching Python's KeyError
                const auto& classes = students_registration_classes.at(student.name);
                class_list.insert(class_list.end(), classes.begin(), classes.end());
            }
        }

        if (class_list.empty()) {
            throw std::invalid_argument("No classes found for the given major");
        }

        std::unordered_map<std::string, int> freq;
        for (const auto& cls : class_list) {
            freq[cls]++;
        }

        auto max_it = std::max_element(freq.begin(), freq.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; });

        return max_it->first;
    }
};