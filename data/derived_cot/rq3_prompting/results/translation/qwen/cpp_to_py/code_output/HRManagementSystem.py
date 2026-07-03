class HRManagementSystem:
    def __init__(self):
        self.employees = {}

    def add_employee(self, employee_id, name, position, department, salary):
        if employee_id in self.employees:
            return False
        self.employees[employee_id] = {
            "name": name,
            "position": position,
            "department": department,
            "salary": salary
        }
        return True

    def remove_employee(self, employee_id):
        if employee_id not in self.employees:
            return False
        del self.employees[employee_id]
        return True

    def update_employee(self, employee_id, employee_info):
        if employee_id not in self.employees:
            return False
        
        for key in employee_info:
            if key not in self.employees[employee_id]:
                return False
        
        for key, value in employee_info.items():
            self.employees[employee_id][key] = value
        
        return True

    def get_employee(self, employee_id):
        if employee_id not in self.employees:
            return None
        return self.employees[employee_id]

    def list_employees(self):
        result = {}
        for emp_id, emp_data in self.employees.items():
            employee_details = {
                "employee_ID": emp_id
            }
            for key, value in emp_data.items():
                employee_details[key] = value
            result[emp_id] = employee_details
        return result