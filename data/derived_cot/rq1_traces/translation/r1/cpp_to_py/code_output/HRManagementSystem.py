class HRManagementSystem:
    def __init__(self):
        self.employees = {}

    def add_employee(self, employee_id, name, position, department, salary):
        if employee_id in self.employees:
            return False
        else:
            self.employees[employee_id] = {
                "name": name,
                "position": position,
                "department": department,
                "salary": salary
            }
            return True

    def remove_employee(self, employee_id):
        if employee_id in self.employees:
            del self.employees[employee_id]
            return True
        else:
            return False

    def update_employee(self, employee_id, employee_info):
        if employee_id not in self.employees:
            return False
        employee_record = self.employees[employee_id]
        for key in employee_info.keys():
            if key not in employee_record:
                return False
        for key, value in employee_info.items():
            employee_record[key] = value
        return True

    def get_employee(self, employee_id):
        if employee_id in self.employees:
            return self.employees[employee_id]
        else:
            return None

    def list_employees(self):
        employee_data = {}
        for emp_id, emp_info in self.employees.items():
            details = {}
            details["employee_ID"] = emp_id
            for key, value in emp_info.items():
                details[key] = value
            employee_data[emp_id] = details
        return employee_data