#include <iostream>
#include <map>
#include <optional>
#include <string>

class HRManagementSystem {
private:
    std::map<int, std::map<std::string, std::string>> employees;

    // Helper method to get an employee's data map
    std::optional<std::map<std::string, std::string>> getEmployeeData(int employee_id) {
        auto it = employees.find(employee_id);
        if (it != employees.end()) {
            return it->second;
        }
        return std::nullopt;
    }

public:
    HRManagementSystem() {}

    bool add_employee(int employee_id, const std::string& name, const std::string& position, 
                     const std::string& department, int salary) {
        auto it = employees.find(employee_id);
        if (it != employees.end()) {
            return false;
        }
        employees[employee_id] = {
            {"name", name},
            {"position", position},
            {"department", department},
            {"salary", std::to_string(salary)}
        };
        return true;
    }

    bool remove_employee(int employee_id) {
        auto it = employees.find(employee_id);
        if (it != employees.end()) {
            employees.erase(it);
            return true;
        }
        return false;
    }

    bool update_employee(int employee_id, const std::map<std::string, std::string>& employee_info) {
        auto emp_data = getEmployeeData(employee_id);
        if (!emp_data.has_value()) {
            return false;
        }

        for (const auto& [key, value] : employee_info) {
            if (emp_data.value().find(key) == emp_data.value().end()) {
                return false;
            }
            emp_data.value()[key] = value;
        }
        return true;
    }

    std::optional<std::map<std::string, std::string>> get_employee(int employee_id) {
        return getEmployeeData(employee_id);
    }

    std::map<int, std::map<std::string, std::string>> list_employees() {
        std::map<int, std::map<std::string, std::string>> result;
        for (const auto& [id, emp_map] : employees) {
            std::map<std::string, std::string> details;
            details["employee_ID"] = std::to_string(id);
            details["name"] = emp_map["name"];
            details["position"] = emp_map["position"];
            details["department"] = emp_map["department"];
            details["salary"] = emp_map["salary"];
            result[id] = details;
        }
        return result;
    }
};