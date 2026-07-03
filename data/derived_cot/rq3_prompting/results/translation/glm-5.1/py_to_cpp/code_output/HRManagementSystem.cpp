#include <map>
#include <string>
#include <variant>
#include <optional>

class HRManagementSystem {
public:
    using Value = std::variant<std::string, int>;
    using EmployeeInfo = std::map<std::string, Value>;
    using EmployeeMap = std::map<int, EmployeeInfo>;

private:
    EmployeeMap employees;

public:
    HRManagementSystem() = default;

    bool add_employee(int employee_id, const std::string& name, const std::string& position,
                      const std::string& department, int salary) {
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
        auto it = employees.find(employee_id);
        if (it != employees.end()) {
            employees.erase(it);
            return true;
        }
        return false;
    }

    bool update_employee(int employee_id, const EmployeeInfo& employee_info) {
        auto it = employees.find(employee_id);
        if (it == employees.end()) {
            return false;
        }
        EmployeeInfo& emp = it->second;
        for (const auto& [key, value] : employee_info) {
            if (emp.find(key) == emp.end()) {
                return false;
            }
        }
        for (const auto& [key, value] : employee_info) {
            emp[key] = value;
        }
        return true;
    }

    std::optional<EmployeeInfo> get_employee(int employee_id) {
        auto it = employees.find(employee_id);
        if (it != employees.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    EmployeeMap list_employees() {
        EmployeeMap employee_data;
        for (const auto& [employee_id, employee_info] : employees) {
            EmployeeInfo employee_details;
            employee_details["employee_ID"] = employee_id;
            for (const auto& [key, value] : employee_info) {
                employee_details[key] = value;
            }
            employee_data[employee_id] = employee_details;
        }
        return employee_data;
    }
};