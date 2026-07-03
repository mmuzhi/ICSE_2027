#include <string>
#include <map>
#include <optional>

class HRManagementSystem {
private:
    std::map<int, std::map<std::string, std::string>> employees;

public:
    // Constructor
    HRManagementSystem() = default;

    // Add an employee
    bool add_employee(int employee_id, const std::string& name, const std::string& position, const std::string& department, int salary) {
        if (employees.find(employee_id) != employees.end()) {
            return false;
        }
        std::map<std::string, std::string> emp_data;
        emp_data["name"] = name;
        emp_data["position"] = position;
        emp_data["department"] = department;
        emp_data["salary"] = std::to_string(salary);
        employees[employee_id] = emp_data;
        return true;
    }

    // Remove an employee
    bool remove_employee(int employee_id) {
        if (employees.find(employee_id) != employees.end()) {
            employees.erase(employee_id);
            return true;
        }
        return false;
    }

    // Update an employee
    bool update_employee(int employee_id, const std::map<std::string, std::string>& employee_info) {
        auto it = employees.find(employee_id);
        if (it == employees.end()) {
            return false;
        }
        const auto& emp = it->second;
        for (const auto& kv : employee_info) {
            std::string key = kv.first;
            if (key == "name") {
                emp[key] = kv.second;
            } else if (key == "position") {
                emp[key] = kv.second;
            } else if (key == "department") {
                emp[key] = kv.second;
            } else if (key == "salary") {
                emp[key] = kv.second;
            } else {
                return false;
            }
        }
        it->second = emp;
        return true;
    }

    // Get an employee
    std::optional<std::map<std::string, std::string>> get_employee(int employee_id) {
        auto it = employees.find(employee_id);
        if (it != employees.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    // List employees
    std::map<int, std::map<std::string, std::string>> list_employees() {
        std::map<int, std::map<std::string, std::string>> employee_data;
        for (const auto& kv : employees) {
            int id = kv.first;
            const auto& emp = kv.second;
            std::map<std::string, std::string> emp_data;
            emp_data["employee_ID"] = std::to_string(id);
            emp_data["name"] = emp.at("name");
            emp_data["position"] = emp.at("position");
            emp_data["department"] = emp.at("department");
            emp_data["salary"] = emp.at("salary");
            employee_data[id] = emp_data;
        }
        return employee_data;
    }
};