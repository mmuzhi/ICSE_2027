#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <stdexcept>

struct Student {
    std::string name;
    std::string major;
};

class ClassRegistrationSystem {
private:
    std::vector<Student> students_list;
    std::set<std::string> student_names;
    std::map<std::string, std::vector<std::string>> students_registration_classes;

public:
    ClassRegistrationSystem() {}

    int register_student(const Student& student) {
        if (student_names.find(student.name) != student_names.end()) {
            return 0;
        }
        students_list.push_back(student);
        student_names.insert(student.name);
        return 1;
    }

    std::vector<std::string>& register_class(const std::string& student_name, const std::string& class_name) {
        students_registration_classes[student_name].push_back(class_name);
        return students_registration_classes[student_name];
    }

    std::vector<std::string> get_students_by_major(const std::string& major) const {
        std::vector<std::string> result;
        for (const auto& student : students_list) {
            if (student.major == major) {
                result.push_back(student.name);
            }
        }
        return result;
    }

    std::vector<std::string> get_all_major() const {
        std::vector<std::string> majors;
        std::set<std::string> seen;
        for (const auto& student : students_list) {
            if (seen.find(student.major) == seen.end()) {
                seen.insert(student.major);
                majors.push_back(student.major);
            }
        }
        return majors;
    }

    std::string get_most_popular_class_in_major(const std::string& major) const {
        std::vector<std::string> all_classes;
        for (const auto& student : students_list) {
            if (student.major == major) {
                auto it_reg = students_registration_classes.find(student.name);
                if (it_reg != students_registration_classes.end()) {
                    all_classes.insert(all_classes.end(), it_reg->second.begin(), it_reg->second.end());
                }
            }
        }
        if (all_classes.empty()) {
            throw std::runtime_error("max() arg is an empty sequence");
        }
        std::map<std::string, int> freq;
        for (const auto& cls : all_classes) {
            freq[cls]++;
        }
        auto it = std::max_element(freq.begin(), freq.end(),
            [](const auto& a, const auto& b) {
                if (a.second != b.second) {
                    return a.second < b.second;
                }
                return a.first < b.first;
            });
        return it->first;
    }
};