from typing import List, Dict, Optional

class SQLGenerator:
    def __init__(self, table_name: str) -> None:
        self.table_name = table_name

    def select(self, fields: Optional[List[str]] = None, condition: str = "") -> str:
        if fields is None or len(fields) == 0:
            fields_str = "*"
        else:
            fields_str = ", ".join(fields)

        sql = f"SELECT {fields_str} FROM {self.table_name}"
        if condition:
            sql += f" WHERE {condition}"
        return sql + ";"

    def insert(self, data: Dict[str, str]) -> str:
        # Sort keys to match std::map iteration order (sorted by key)
        sorted_keys = sorted(data.keys())
        fields_list = []
        values_list = []
        for key in sorted_keys:
            fields_list.append(key)
            values_list.append(f"'{data[key]}'")
        fields_str = ", ".join(fields_list)
        values_str = ", ".join(values_list)
        sql = f"INSERT INTO {self.table_name} ({fields_str}) VALUES ({values_str})"
        return sql + ";"

    def update(self, data: Dict[str, str], condition: str) -> str:
        # Sort keys to match std::map iteration order
        sorted_keys = sorted(data.keys())
        set_parts = []
        for key in sorted_keys:
            set_parts.append(f"{key} = '{data[key]}'")
        set_clause = ", ".join(set_parts)
        sql = f"UPDATE {self.table_name} SET {set_clause}"
        if condition:
            sql += f" WHERE {condition}"
        return sql + ";"

    def delete_query(self, condition: str) -> str:
        sql = f"DELETE FROM {self.table_name}"
        if condition:
            sql += f" WHERE {condition}"
        return sql + ";"

    def select_female_under_age(self, age: int) -> str:
        condition = f"age < {age} AND gender = 'female'"
        # Equivalent to select({}, condition) in C++
        return self.select(condition=condition)

    def select_by_age_range(self, min_age: int, max_age: int) -> str:
        condition = f"age BETWEEN {min_age} AND {max_age}"
        return self.select(condition=condition)