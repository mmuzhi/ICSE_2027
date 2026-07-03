class HRManagementSystem:
    def __init__(self):
        self.employees = {}

    def add_employee(self, employee_id, name, position, department, salary):
        if employee_id in self.employees:
            return False
        employee_info = {
            "name": name,
            "position": position,
            "department": department,
            "salary": salary
        }
        self.employees[employee_id] = employee_info
        return True

    def remove_employee(self, employee_id):
        if employee_id in self.employees:
            del self.employees[employee_id]
            return True
        return False

    def update_employee(self, employee_id, updated_employee_info):
        if employee_id not in self.employees:
            return False
        valid_keys = {"name", "position", "department", "salary"}
        for key in updated_employee_info:
            if key not in valid_keys:
                return False
        self.employees[employee_id].update(updated_employee_info)
        return True

    def get_employee(self, employee_id):
        return self.employees.get(employee_id) if employee_id in self.employees else False

    def list_employees(self):
        employee_data = {}
        for emp_id, emp_info in self.employees.items():
            emp_info_copy = emp_info.copy()
            emp_info_copy["employee_ID"] = emp_id
            employee_data[emp_id] = emp_info_copy
        return employee_data