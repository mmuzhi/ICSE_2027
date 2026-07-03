#include <vector>
#include <map>
#include <string>
#include <algorithm>

class ClassRegistrationSystem {
private:
    std::vector<std::map<std::string, std::string>> students;
    std::map<std::string, std::vector<std::string>> students_registration_classes;

public:
    int register_student(const std::map<std::string, std::string>& student) {
        for (const auto& s : students) {
            if (s == student) {
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
        std::vector<std::string> student_list;
        for (const auto& student : students) {
            if (student.find("major") != student.end() && student["major"] == major) {
                student_list.push_back(student["name"]);
            }
        }
        return student_list;
    }

    std::vector<std::string> get_all_major() {
        std::vector<std::string> major_list;
        for (const auto& student : students) {
            if (student.find("major") != student.end()) {
                std::string major = student["major"];
                if (std::find(major_list.begin(), major_list.end(), major) == major_list.end()) {
                    major_list.push_back(major);
                }
            }
        }
        return major_list;
    }

    std::string get_most_popular_class_in_major(const std::string& major) {
        std::vector<std::string> class_list;
        for (const auto& student : students) {
            if (student.find("major") != student.end() && student["major"] == major) {
                std::string student_name = student["name"];
                if (students_registration_classes.find(student_name) != students_registration_classes.end()) {
                    class_list.insert(class_list.end(), students_registration_classes[student_name].begin(), students_registration_classes[student_name].end());
                }
            }
        }

        if (class_list.empty()) {
            return "";
        }

        std::string most_popular;
        int max_count = 0;
        for (const auto& cls : class_list) {
            int count = std::count(class_list.begin(), class_list.end(), cls);
            if (count > max_count) {
                max_count = count;
                most_popular = cls;
            }
        }
        return most_popular;
    }
};