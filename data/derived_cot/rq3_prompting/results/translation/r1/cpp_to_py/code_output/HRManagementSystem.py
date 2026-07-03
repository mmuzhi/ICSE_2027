class HRManagementSystem:
    def __init__(self):
        self.employees = {}  # int -> dict[str, str|int]

    def add_employee(self, employee_id: int, name: str, position: str,
                     department: str, salary: int) -> bool:
        if employee_id in self.employees:
            return False
        self.employees[employee_id] = {
            "name": name,
            "position": position,
            "department": department,
            "salary": salary
        }
        return True

    def remove_employee(self, employee_id: int) -> bool:
        if employee_id in self.employees:
            del self.employees[employee_id]
            return True
        return False

    def update_employee(self, employee_id: int,
                        employee_info: dict) -> bool:
        if employee_id not in self.employees:
            return False
        emp_dict = self.employees[employee_id]
        # Check that all keys in employee_info already exist
        for key in employee_info:
            if key not in emp_dict:
                return False
        # Update each key
        for key, value in employee_info.items():
            emp_dict[key] = value
        return True

    def get_employee(self, employee_id: int):
        """Return a copy of the employee dict, or None if not found."""
        if employee_id in self.employees:
            return self.employees[employee_id].copy()
        return None

    def list_employees(self) -> dict:
        """Return a new dict of all employees, each with an added 'employee_ID' key."""
        result = {}
        for emp_id, info in self.employees.items():
            employee_data = info.copy()
            employee_data["employee_ID"] = emp_id
            result[emp_id] = employee_data
        return result