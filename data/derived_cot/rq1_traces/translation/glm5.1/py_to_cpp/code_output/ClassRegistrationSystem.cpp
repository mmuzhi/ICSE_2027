#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <stdexcept>

class ClassRegistrationSystem {
public:
    std::vector<std::map<std::string, std::string>> students;
    std::map<std::string, std::vector<std::string>> students_registration_classes;

    ClassRegistrationSystem() = default;

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
        students_registration_classes[student_name].push_back(class_name);
        return students_registration_classes[student_name];
    }

    std::vector<std::string> get_students_by_major(const std::string& major) {
        std::vector<std::string> student_list;
        for (const auto& student : students) {
            if (student.at("major") == major) {
                student_list.push_back(student.at("name"));
            }
        }
        return student_list;
    }

    std::vector<std::string> get_all_major() {
        std::vector<std::string> major_list;
        for (const auto& student : students) {
            const std::string& m = student.at("major");
            if (std::find(major_list.begin(), major_list.end(), m) == major_list.end()) {
                major_list.push_back(m);
            }
        }
        return major_list;
    }

    std::string get_most_popular_class_in_major(const std::string& major) {
        std::vector<std::string> class_list;
        for (const auto& student : students) {
            if (student.at("major") == major) {
                // .at() throws std::out_of_range if key missing, matching Python's KeyError
                const auto& classes = students_registration_classes.at(student.at("name"));
                class_list.insert(class_list.end(), classes.begin(), classes.end());
            }
        }

        // Python's max() on empty sequence raises ValueError
        if (class_list.empty()) {
            throw std::runtime_error("max() arg is an empty sequence");
        }

        // Equivalent to: max(set(class_list), key=class_list.count)
        std::map<std::string, int> counts;
        for (const auto& cls : class_list) {
            counts[cls]++;
        }

        std::string most_popular;
        int max_count = -1;
        for (const auto& [cls, count] : counts) {
            if (count > max_count) {
                max_count = count;
                most_popular = cls;
            }
        }

        return most_popular;
    }
};