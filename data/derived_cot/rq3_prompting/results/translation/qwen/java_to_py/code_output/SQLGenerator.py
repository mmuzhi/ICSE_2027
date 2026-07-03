from typing import List, Dict, Optional

class SQLGenerator:
    def __init__(self, table_name: str):
        self.table_name = table_name

    def select(self, fields: Optional[List[str]], condition: Optional[str] = None) -> str:
        fields_str = '*' if fields is None else ', '.join(fields)
        sql = f'SELECT {fields_str} FROM {self.table_name}'
        if condition is not None:
            sql += f' WHERE {condition}'
        return sql + ';'

    def insert(self, data: Dict[str, str]) -> str:
        sorted_keys = sorted(data.keys())
        fields = ', '.join(sorted_keys)
        values = ', '.join(f"'{value}'" for value in data.values())
        return f'INSERT INTO {self.table_name} ({fields}) VALUES ({values});'

    def update(self, data: Dict[str, str], condition: str) -> str:
        sorted_entries = sorted(data.items())
        set_clause = ', '.join(f'{key} = \'{value}\''.replace('\'value\'', value) for key, value in sorted_entries)
        return f'UPDATE {self.table_name} SET {set_clause} WHERE {condition};'

    def delete(self, condition: str) -> str:
        return f'DELETE FROM {self.table_name} WHERE {condition};'

    def select_female_under_age(self, age: int) -> str:
        return f'SELECT * FROM {self.table_name} WHERE age < {age} AND gender = \'female\';'

    def select_by_age_range(self, min_age: int, max_age: int) -> str:
        return f'SELECT * FROM {self.table_name} WHERE age BETWEEN {min_age} AND {max_age};'