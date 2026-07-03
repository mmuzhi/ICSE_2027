#include <unordered_map>
#include <unordered_set>
#include <string>
#include <any>
#include <memory>
#include <variant>

class HRManagementSystem {
public:
    using EmployeeData = std::unordered_map<std::string, std::any>;
    using EmployeeDataPtr = std::shared_ptr<EmployeeData>;
    using GetEmployeeResult = std::variant<bool, EmployeeDataPtr>;

    HRManagementSystem() = default;

    bool addEmployee(int employeeId, const std::string& name, const std::string& position, const std::string& department, double salary) {
        if (employees_.find(employeeId) != employees_.end()) {
            return false;
        }
        auto emp = std::make_shared<EmployeeData>();
        (*emp)["name"] = name;
        (*emp)["position"] = position;
        (*emp)["department"] = department;
        (*emp)["salary"] = salary;
        employees_[employeeId] = emp;
        return true;
    }

    bool removeEmployee(int employeeId) {
        return employees_.erase(employeeId) > 0;
    }

    bool updateEmployee(int employeeId, const EmployeeData& updatedEmployeeInfo) {
        auto it = employees_.find(employeeId);
        if (it == employees_.end()) {
            return false;
        }
        static const std::unordered_set<std::string> validKeys = {"name", "position", "department", "salary"};
        for (const auto& kv : updatedEmployeeInfo) {
            if (validKeys.find(kv.first) == validKeys.end()) {
                return false;
            }
        }
        auto& emp = it->second;
        for (const auto& kv : updatedEmployeeInfo) {
            (*emp)[kv.first] = kv.second;
        }
        return true;
    }

    GetEmployeeResult getEmployee(int employeeId) {
        auto it = employees_.find(employeeId);
        if (it == employees_.end()) {
            return false;
        }
        return it->second;
    }

    std::unordered_map<int, EmployeeData> listEmployees() {
        std::unordered_map<int, EmployeeData> result;
        for (const auto& kv : employees_) {
            EmployeeData emp = *(kv.second);
            emp["employee_ID"] = kv.first;
            result[kv.first] = std::move(emp);
        }
        return result;
    }

private:
    std::unordered_map<int, EmployeeDataPtr> employees_;
};