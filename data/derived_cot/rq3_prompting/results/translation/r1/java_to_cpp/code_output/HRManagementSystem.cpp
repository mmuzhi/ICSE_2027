#include <unordered_map>
#include <string>
#include <variant>
#include <memory>
#include <unordered_set>
#include <utility>

class HRManagementSystem {
public:
    // Type aliases for clarity
    using InnerValue = std::variant<std::string, double, int>;
    using InnerMap = std::unordered_map<std::string, InnerValue>;

    std::unordered_map<int, std::shared_ptr<InnerMap>> employees;

    HRManagementSystem() = default;

    bool addEmployee(int employeeId, const std::string& name, const std::string& position,
                     const std::string& department, double salary) {
        if (employees.count(employeeId)) {
            return false;
        }
        auto info = std::make_shared<InnerMap>();
        info->emplace("name", name);
        info->emplace("position", position);
        info->emplace("department", department);
        info->emplace("salary", salary);
        employees[employeeId] = std::move(info);
        return true;
    }

    bool removeEmployee(int employeeId) {
        return employees.erase(employeeId) > 0;
    }

    bool updateEmployee(int employeeId, const InnerMap& updatedEmployeeInfo) {
        auto it = employees.find(employeeId);
        if (it == employees.end()) {
            return false;
        }
        static const std::unordered_set<std::string> validKeys = {
            "name", "position", "department", "salary"
        };
        for (const auto& [key, _] : updatedEmployeeInfo) {
            if (!validKeys.count(key)) {
                return false;
            }
        }
        // Apply all updates
        for (const auto& [key, value] : updatedEmployeeInfo) {
            it->second->operator[](key) = value;
        }
        return true;
    }

    std::variant<bool, std::shared_ptr<InnerMap>> getEmployee(int employeeId) {
        auto it = employees.find(employeeId);
        if (it == employees.end()) {
            return false;
        }
        return it->second;  // shared_ptr
    }

    std::unordered_map<int, InnerMap> listEmployees() {
        std::unordered_map<int, InnerMap> result;
        for (const auto& [id, ptr] : employees) {
            InnerMap copy = *ptr;                     // deep copy of the inner map
            copy["employee_ID"] = id;                 // add the ID
            result.emplace(id, std::move(copy));
        }
        return result;
    }
};