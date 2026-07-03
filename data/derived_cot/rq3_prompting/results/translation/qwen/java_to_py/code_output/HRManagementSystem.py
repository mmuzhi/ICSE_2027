class HRManagementSystem:
    def __init__(self):
        self.employees = {}  # mapping from employeeId to dict of employee info

    def add_employee(self, employee_id: int, name: str, position: str, department: str, salary: float) -> bool:
        if employee_id in self.employees:
            return False
        employee_info = {'name': name, 'position': position, 'department': department, 'salary': salary}
        self.employees[employee_id] = employee_info
        return True

    def remove_employee(self, employee_id: int) -> bool:
        return True if self.employees.pop(employee_id, None) is not None else False

    def update_employee(self, employee_id: int, updated_info: dict) -> bool:
        if employee_id not in self.employees:
            return False
        valid_keys = {'name', 'position', 'department', 'salary'}
        for key in updated_info.keys():
            if key not in valid_keys:
                return False
        self.employees[employee_id].update(updated_info)
        return True

    def get_employee(self, employee_id: int) -> dict | bool:
        return self.employees.get(employee_id, False)

    def list_employees(self) -> dict:
        return {
            emp_id: {'employee_ID': emp_id, **emp_data}
            for emp_id, emp_data in self.employees.items()
        }