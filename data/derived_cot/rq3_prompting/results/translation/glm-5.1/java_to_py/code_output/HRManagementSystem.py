class HRManagementSystem:
    def __init__(self):
        self.employees = {}

    def addEmployee(self, employeeId, name, position, department, salary):
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

    def removeEmployee(self, employeeId):
        if employeeId in self.employees:
            del self.employees[employeeId]
            return True
        else:
            return False

    def updateEmployee(self, employeeId, updatedEmployeeInfo):
        if employeeId not in self.employees:
            return False
        valid_keys = {"name", "position", "department", "salary"}
        for key in updatedEmployeeInfo:
            if key not in valid_keys:
                return False
        self.employees[employeeId].update(updatedEmployeeInfo)
        return True

    def getEmployee(self, employeeId):
        if employeeId not in self.employees:
            return False
        else:
            return self.employees[employeeId]

    def listEmployees(self):
        employee_data = {}
        for eid, info in self.employees.items():
            new_info = info.copy()
            new_info["employee_ID"] = eid
            employee_data[eid] = new_info
        return employee_data