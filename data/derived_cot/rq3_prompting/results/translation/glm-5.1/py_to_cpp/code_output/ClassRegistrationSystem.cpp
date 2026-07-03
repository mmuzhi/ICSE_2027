#include <vector>
#include <map>
#include <string>
#include <algorithm>

class ClassRegistrationSystem {
public:
    std::vector<std::map<std::string, std::string>> students;
    std::map<std::string, std::vector<std::string>> students_registration_classes;

    ClassRegistrationSystem() {}

    int register_student(std::map<std::string, std::string> student) {
        if (std::find(students.begin(), students.end(), student) != students.end()) {
            return 0;
        } else {
            students.push_back(student);
            return 1;
        }
    }

    std::vector<std::string> register_class(const std::string& student_name, const std::string& class_name) {
        students_registration_classes[student_name].push_back(class_name);
        return students_registration_classes[student_name];
    }

    std::vector<std::string> get_students_by_major(const std::string& major) {
        std::vector<std::string> student_list;
        for (auto& student : students) {
            if (student["major"] == major) {
                student_list.push_back(student["name"]);
            }
        }
        return student_list;
    }

    std::vector<std::string> get_all_major() {
        std::vector<std::string> major_list;
        for (auto& student : students) {
            if (std::find(major_list.begin(), major_list.end(), student["major"]) == major_list.end()) {
                major_list.push_back(student["major"]);
            }
        }
        return major_list;
    }

    std::string get_most_popular_class_in_major(const std::string& major) {
        std::vector<std::string> class_list;
        for (auto& student : students) {
            if (student["major"] == major) {
                auto& classes = students_registration_classes.at(student["name"]);
                class_list.insert(class_list.end(), classes.begin(), classes.end());
            }
        }
        // Python: max(set(class_list), key=class_list.count)
        std::map<std::string, int> counts;
        for (auto& cls : class_list) {
            counts[cls]++;
        }
        std::string most_popular;
        int max_count = -1;
        for (auto& [cls, cnt] : counts) {
            if (cnt > max_count) {
                max_count = cnt;
                most_popular = cls;
            }
        }
        return most_popular;
    }
};