#include <unordered_map>
#include <map>
#include <string>
#include <any>
#include <set>
#include <vector>
#include <optional>

class HRManagementSystem {
public:
    std::unordered_map<int, std::map<std::string, std::any>> employees;

    HRManagementSystem() {}

    bool add_employee(int employeeId, const std::string& name, const std::string& position, const std::string& department, double salary) {
        auto it = employees.find(employeeId);
        if (it != employees.end()) {
            return false;
        }
        std::map<std::string, std::any> employeeInfo;
        employeeInfo["name"] = name;
        employeeInfo["position"] = position;
        employeeInfo["department"] = department;
        employeeInfo["salary"] = salary;
        employees[employeeId] = employeeInfo;
        return true;
    }

    bool remove_employee(int employeeId) {
        if (employees.erase(employeeId) == 1) {
            return true;
        }
        return false;
    }

    bool update_employee(int employeeId, const std::map<std::string, std::any>& updatedEmployeeInfo) {
        auto it = employees.find(employeeId);
        if (it == employees.end()) {
            return false;
        }
        static const std::set<std::string> validKeys = {"name", "position", "department", "salary"};
        for (const auto& kv : updatedEmployeeInfo) {
            if (validKeys.find(kv.first) == validKeys.end()) {
                return false;
            }
        }
        for (const auto& kv : updatedEmployeeInfo) {
            it->second[kv.first] = kv.second;
        }
        return true;
    }

    std::any getEmployee(int employeeId) {
        auto it = employees.find(employeeId);
        if (it == employees.end()) {
            return false;
        }
        return it->second;
    }

    std::unordered_map<int, std::map<std::string, std::any>> listEmployees() {
        std::unordered_map<int, std::map<std::string, std::any>> employeeData;
        for (const auto& entry : employees) {
            int employeeId = entry.first;
            std::map<std::string, std::any> employeeInfo = entry.second;
            employeeInfo["employee_ID"] = employeeId;
            employeeData[employeeId] = employeeInfo;
        }
        return employeeData;
    }
};