from typing import Dict, Any, Union

class HRManagementSystem:
    def __init__(self) -> None:
        self.employees: Dict[int, Dict[str, Any]] = {}

    def addEmployee(self, employeeId: int, name: str, position: str, department: str, salary: float) -> bool:
        if employeeId in self.employees:
            return False
        else:
            self.employees[employeeId] = {
                "name": name,
                "position": position,
                "department": department,
                "salary": salary
            }
            return True

    def removeEmployee(self, employeeId: int) -> bool:
        if employeeId in self.employees:
            del self.employees[employeeId]
            return True
        else:
            return False

    def updateEmployee(self, employeeId: int, updatedEmployeeInfo: Dict[str, Any]) -> bool:
        employeeInfo = self.employees.get(employeeId)
        if employeeInfo is None:
            return False
        else:
            validKeys = {"name", "position", "department", "salary"}
            for key in updatedEmployeeInfo.keys():
                if key not in validKeys:
                    return False
            employeeInfo.update(updatedEmployeeInfo)
            return True

    def getEmployee(self, employeeId: int) -> Union[Dict[str, Any], bool]:
        employeeInfo = self.employees.get(employeeId)
        if employeeInfo is None:
            return False
        else:
            return employeeInfo

    def listEmployees(self) -> Dict[int, Dict[str, Any]]:
        employeeData: Dict[int, Dict[str, Any]] = {}
        for employeeId, employeeInfo in self.employees.items():
            # Shallow copy equivalent to new HashMap<>(entry.getValue())
            newInfo = employeeInfo.copy()
            newInfo["employee_ID"] = employeeId
            employeeData[employeeId] = newInfo
        return employeeData