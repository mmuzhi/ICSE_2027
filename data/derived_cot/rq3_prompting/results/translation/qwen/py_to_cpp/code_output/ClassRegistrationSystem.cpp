#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

struct Student {
    std::string name;
    std::string major;
};

class ClassRegistrationSystem {
private:
    std::vector<Student> students;
    std::unordered_map<std::string, std::vector<std::string>> students_registration_classes;

public:
    int register_student(const Student& student) {
        for (const auto& s : students) {
            if (s.name == student.name && s.major == student.major) {
                return 0;
            }
        }
        students.push_back(student);
        return 1;
    }

    std::vector<std::string> register_class(const std::string& student_name, const std::string& class_name) {
        if (students_registration_classes.find(student_name) == students_registration_classes.end()) {
            students_registration_classes[student_name] = std::vector<std::string>();
        }
        students_registration_classes[student_name].push_back(class_name);
        return students_registration_classes[student_name];
    }

    std::vector<std::string> get_students_by_major(const std::string& major) {
        std::vector<std::string> result;
        for (const auto& student : students) {
            if (student.major == major) {
                result.push_back(student.name);
            }
        }
        return result;
    }

    std::vector<std::string> get_all_major() {
        std::vector<std::string> majors;
        for (const auto& student : students) {
            if (std::find(majors.begin(), majors.end(), student.major) == majors.end()) {
                majors.push_back(student.major);
            }
        }
        return majors;
    }

    std::string get_most_popular_class_in_major(const std::string& major) {
        std::vector<std::string> class_list;
        for (const auto& student : students) {
            if (student.major == major) {
                for (const auto& cls : students_registration_classes[student.name]) {
                    class_list.push_back(cls);
                }
            }
        }
        if (class_list.empty()) {
            return "";
        }

        std::unordered_map<std::string, int> class_count;
        for (const auto& cls : class_list) {
            class_count[cls]++;
        }

        int max_count = 0;
        for (const auto& kv : class_count) {
            if (kv.second > max_count) {
                max_count = kv.second;
            }
        }

        for (const auto& cls : class_list) {
            if (class_count[cls] == max_count) {
                return cls;
            }
        }

        return "";
    }
};