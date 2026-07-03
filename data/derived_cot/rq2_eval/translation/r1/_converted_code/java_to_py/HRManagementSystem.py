class HRManagementSystem:

    def __init__(self):
        self.employees = {}

    def add_employee(self, employeeId, name, position, department, salary):
        if employeeId in self.employees:
            return False
        else:
            employeeInfo = {'name': name, 'position': position, 'department': department, 'salary': salary}
            self.employees[employeeId] = employeeInfo
            return True

    def remove_employee(self, employeeId):
        if employeeId in self.employees:
            del self.employees[employeeId]
            return True
        else:
            return False

    def update_employee(self, employeeId, updatedEmployeeInfo):
        if employeeId not in self.employees:
            return False
        validKeys = {'name', 'position', 'department', 'salary'}
        for key in updatedEmployeeInfo.keys():
            if key not in validKeys:
                return False
        self.employees[employeeId].update(updatedEmployeeInfo)
        return True

    def get_employee(self, employeeId):
        if employeeId not in self.employees:
            return False
        else:
            return self.employees[employeeId]

    def list_employees(self):
        employeeData = {}
        for empId, empInfo in self.employees.items():
            newInfo = empInfo.copy()
            newInfo['employee_ID'] = empId
            employeeData[empId] = newInfo
        return employeeData