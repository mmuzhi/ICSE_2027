class SQLGenerator:
    def __init__(self, table_name):
        self.table_name = table_name

    def select(self, fields=None, condition=None):
        fields_str = "*"
        if fields is not None and fields:
            fields_str = ", ".join(fields)
        sql = f"SELECT {fields_str} FROM {self.table_name}"
        if condition is not None:
            sql += f" WHERE {condition}"
        return sql + ";"

    def insert(self, data):
        if not data:
            raise ValueError("Data dictionary cannot be empty")
        fields = ", ".join(data.keys())
        values = ", ".join(f"'{v}'" for v in data.values())
        return f"INSERT INTO {self.table_name} ({fields}) VALUES ({values});"

    def update(self, data, condition=None):
        if not data:
            raise ValueError("Data dictionary cannot be empty")
        set_clause = ", ".join(f"{k} = '{v}'" for k, v in data.items())
        sql = f"UPDATE {self.table_name} SET {set_clause}"
        if condition is not None:
            sql += f" WHERE {condition}"
        return sql + ";"

    def delete_query(self, condition=None):
        sql = f"DELETE FROM {self.table_name}"
        if condition is not None:
            sql += f" WHERE {condition}"
        return sql + ";"

    def select_female_under_age(self, age):
        condition = f"age < {age} AND gender = 'female'"
        return self.select(condition=condition)

    def select_by_age_range(self, min_age, max_age):
        condition = f"age BETWEEN {min_age} AND {max_age}"
        return self.select(condition=condition)