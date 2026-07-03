#include <unordered_map>
#include <any>
#include <set>
#include <string>
#include <variant>

class HRManagementSystem {
private:
    std::unordered_map<int, std::unordered_map<std::string, std::any>> employees;

public:
    HRManagementSystem() = default;

    bool addEmployee(int employeeId, const std::string& name, const std::string& position, const std::string& department, double salary) {
        if (employees.find(employeeId) != employees.end()) return false;
        std::unordered_map<std::string, std::any> employeeInfo;
        employeeInfo["name"] = name;
        employeeInfo["position"] = position;
        employeeInfo["department"] = department;
        employeeInfo["salary"] = salary;
        employees[employeeId] = employeeInfo;
        return true;
    }

    bool removeEmployee(int employeeId) {
        return employees.erase(employeeId) == 1;
    }

    bool updateEmployee(int employeeId, const std::unordered_map<std::string, std::any>& updatedInfo) {
        auto it = employees.find(employeeId);
        if (it == employees.end()) return false;
        const auto& existing = it->second;
        static const std::set<std::string> validKeys = {"name", "position", "department", "salary"};
        
        for (const auto& [key, value] : updatedInfo) {
            if (validKeys.find(key) == validKeys.end()) return false;
        }
        existing.insert_or_assign(updatedInfo.begin(), updatedInfo.end());
        return true;
    }

    std::variant<std::optional<std::unordered_map<std::string, std::any>>, bool> getEmployee(int employeeId) {
        auto it = employees.find(employeeId);
        if (it == employees.end()) return false;
        return it->second;
    }

    std::unordered_map<int, std::unordered_map<std::string, std::any>> listEmployees() {
        std::unordered_map<int, std::unordered_map<std::string, std::any>> result;
        for (const auto& [id, info] : employees) {
            auto newInfo = info;
            newInfo["employee_ID"] = std::to_string(id);
            result[id] = newInfo;
        }
        return result;
    }
};