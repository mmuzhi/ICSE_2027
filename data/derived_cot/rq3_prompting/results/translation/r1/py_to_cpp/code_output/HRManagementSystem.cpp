#include <unordered_map>
#include <string>
#include <variant>
#include <unordered_set>

class HRManagementSystem {
private:
    // Each employee is stored as a map from string key to value (int or string)
    using EmployeeInfo = std::unordered_map<std::string, std::variant<int, std::string>>;
    std::unordered_map<int, EmployeeInfo> employees;

    static const std::unordered_set<std::string> valid_keys;

public:
    HRManagementSystem() {}

    // Add a new employee; returns false if employee already exists
    bool add_employee(int employee_id,
                      const std::string& name,
                      const std::string& position,
                      const std::string& department,
                      int salary) {
        if (employees.find(employee_id) != employees.end()) {
            return false;
        }
        EmployeeInfo info;
        info["name"] = name;
        info["position"] = position;
        info["department"] = department;
        info["salary"] = salary;   // int stored in variant
        employees[employee_id] = std::move(info);
        return true;
    }

    // Remove an employee; returns false if not found
    bool remove_employee(int employee_id) {
        auto it = employees.find(employee_id);
        if (it != employees.end()) {
            employees.erase(it);
            return true;
        }
        return false;
    }

    // Update an existing employee with the given info (only known keys allowed)
    bool update_employee(int employee_id, const EmployeeInfo& employee_info) {
        EmployeeInfo* emp = get_employee(employee_id);
        if (!emp) {
            return false;
        }
        // Validate that all keys in the update are known
        for (const auto& [key, value] : employee_info) {
            if (valid_keys.find(key) == valid_keys.end()) {
                return false;
            }
        }
        // Apply the updates
        for (const auto& [key, value] : employee_info) {
            (*emp)[key] = value;
        }
        return true;
    }

    // Get a pointer to the employee's info, or nullptr if not found.
    // This matches Python's behavior of returning a mutable dict (when found).
    EmployeeInfo* get_employee(int employee_id) {
        auto it = employees.find(employee_id);
        if (it != employees.end()) {
            return &(it->second);
        }
        return nullptr;
    }

    // List all employees; each entry includes an extra "employee_ID" key
    std::unordered_map<int, EmployeeInfo> list_employees() const {
        std::unordered_map<int, EmployeeInfo> result;
        for (const auto& [id, info] : employees) {
            EmployeeInfo entry = info;
            entry["employee_ID"] = id;   // int stored in variant
            result[id] = std::move(entry);
        }
        return result;
    }
};

// Definition of the valid keys set
const std::unordered_set<std::string> HRManagementSystem::valid_keys = {
    "name", "position", "department", "salary"
};