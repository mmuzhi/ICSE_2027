#ifndef HR_MANAGEMENT_SYSTEM_H
#define HR_MANAGEMENT_SYSTEM_H

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <any>

class HRManagementSystem {
public:
    std::unordered_map<int, std::unordered_map<std::string, std::any>> employees;

    HRManagementSystem() = default;

    bool addEmployee(int employeeId, const std::string& name, const std::string& position,
                     const std::string& department, double salary) {
        if (employees.count(employeeId)) {
            return false;
        } else {
            std::unordered_map<std::string, std::any> employeeInfo;
            employeeInfo["name"] = name;
            employeeInfo["position"] = position;
            employeeInfo["department"] = department;
            employeeInfo["salary"] = salary;
            employees[employeeId] = std::move(employeeInfo);
            return true;
        }
    }

    bool removeEmployee(int employeeId) {
        if (employees.count(employeeId)) {
            employees.erase(employeeId);
            return true;
        } else {
            return false;
        }
    }

    bool updateEmployee(int employeeId, const std::unordered_map<std::string, std::any>& updatedEmployeeInfo) {
        auto it = employees.find(employeeId);
        if (it == employees.end()) {
            return false;
        } else {
            static const std::unordered_set<std::string> validKeys = {"name", "position", "department", "salary"};
            for (const auto& [key, value] : updatedEmployeeInfo) {
                if (!validKeys.count(key)) {
                    return false;
                }
            }
            for (const auto& [key, value] : updatedEmployeeInfo) {
                it->second[key] = value;
            }
            return true;
        }
    }

    std::any getEmployee(int employeeId) {
        auto it = employees.find(employeeId);
        if (it == employees.end()) {
            return false;
        } else {
            return it->second;
        }
    }

    std::unordered_map<int, std::unordered_map<std::string, std::any>> listEmployees() {
        std::unordered_map<int, std::unordered_map<std::string, std::any>> employeeData;
        for (const auto& [employeeId, employeeInfo] : employees) {
            std::unordered_map<std::string, std::any> newInfo = employeeInfo;
            newInfo["employee_ID"] = employeeId;
            employeeData[employeeId] = std::move(newInfo);
        }
        return employeeData;
    }
};

#endif // HR_MANAGEMENT_SYSTEM_H