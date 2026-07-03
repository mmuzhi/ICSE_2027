#include <map>
#include <string>
#include <any>

class HRManagementSystem {
private:
    // A dictionary in Python is best represented by std::map in C++.
    // We use std::any to handle values that can be either std::string or int.
    using Dict = std::map<std::string, std::any>;
    std::map<int, Dict> employees;

public:
    HRManagementSystem() = default;

    bool add_employee(int employee_id, const std::string& name, const std::string& position, const std::string& department, int salary) {
        if (employees.find(employee_id) != employees.end()) {
            return false;
        }
        employees[employee_id] = {
            {"name", name},
            {"position", position},
            {"department", department},
            {"salary", salary}
        };
        return true;
    }

    bool remove_employee(int employee_id) {
        if (employees.find(employee_id) != employees.end()) {
            employees.erase(employee_id);
            return true;
        }
        return false;
    }

    bool update_employee(int employee_id, const Dict& employee_info) {
        Dict* employee = get_employee(employee_id);
        if (employee == nullptr) {
            return false;
        }

        // First pass: Check if all keys in employee_info exist in the employee record
        for (const auto& [key, value] : employee_info) {
            if (employee->find(key) == employee->end()) {
                return false;
            }
        }

        // Second pass: Update the values
        for (const auto& [key, value] : employee_info) {
            (*employee)[key] = value;
        }
        
        return true;
    }

    Dict* get_employee(int employee_id) {
        auto it = employees.find(employee_id);
        if (it != employees.end()) {
            return &(it->second); // Return pointer to preserve reference semantics
        }
        return nullptr; // nullptr is the C++ equivalent of returning False/None in this context
    }

    std::map<int, Dict> list_employees() {
        std::map<int, Dict> employee_data;
        if (!employees.empty()) {
            for (const auto& [employee_id, employee_info] : employees) {
                Dict employee_details;
                employee_details["employee_ID"] = employee_id;
                for (const auto& [key, value] : employee_info) {
                    employee_details[key] = value;
                }
                employee_data[employee_id] = employee_details;
            }
        }
        return employee_data;
    }
};