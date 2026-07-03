#include <any>
#include <string>
#include <unordered_map>

using EmployeeData = std::unordered_map<std::string, std::any>;

class HRManagementSystem {
private:
    std::unordered_map<int, EmployeeData> employees;

public:
    HRManagementSystem() {}

    bool add_employee(int employee_id, const std::string& name, const std::string& position, const std::string& department, int salary) {
        if (employees.find(employee_id) != employees.end()) {
            return false;
        }
        EmployeeData data;
        data["name"] = name;
        data["position"] = position;
        data["department"] = department;
        data["salary"] = salary;
        employees[employee_id] = data;
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

    bool update_employee(int employee_id, const EmployeeData& employee_info) {
        auto it = employees.find(employee_id);
        if (it == employees.end()) {
            return false;
        }
        EmployeeData& employee = it->second;
        for (const auto& kv : employee_info) {
            if (employee.find(kv.first) == employee.end()) {
                return false;
            }
        }
        for (const auto& kv : employee_info) {
            employee[kv.first] = kv.second;
        }
        return true;
    }

    EmployeeData* get_employee(int employee_id) {
        auto it = employees.find(employee_id);
        if (it != employees.end()) {
            return &it->second;
        }
        return nullptr;
    }

    std::unordered_map<int, EmployeeData> list_employees() {
        std::unordered_map<int, EmployeeData> result;
        for (const auto& kv : employees) {
            int id = kv.first;
            EmployeeData listed = kv.second;
            listed["employee_ID"] = id;
            result[id] = listed;
        }
        return result;
    }
};