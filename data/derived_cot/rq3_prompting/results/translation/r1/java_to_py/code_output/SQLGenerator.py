class SQLGenerator:
    def __init__(self, table_name):
        self.table_name = table_name

    def select(self, fields, condition):
        if fields is None:
            fields_str = "*"
        else:
            fields_str = ", ".join(fields)
        sql = f"SELECT {fields_str} FROM {self.table_name}"
        if condition is not None:
            sql += f" WHERE {condition}"
        return sql + ";"

    def insert(self, data):
        sorted_keys = sorted(data.keys())
        fields = ", ".join(sorted_keys)
        values = ", ".join(f"'{data[k]}'" for k in sorted_keys)
        return f"INSERT INTO {self.table_name} ({fields}) VALUES ({values});"

    def update(self, data, condition):
        sorted_keys = sorted(data.keys())
        set_clause = ", ".join(f"{k} = '{data[k]}'" for k in sorted_keys)
        return f"UPDATE {self.table_name} SET {set_clause} WHERE {condition};"

    def delete(self, condition):
        return f"DELETE FROM {self.table_name} WHERE {condition};"

    def selectFemaleUnderAge(self, age):
        return f"SELECT * FROM {self.table_name} WHERE age < {age} AND gender = 'female';"

    def selectByAgeRange(self, minAge, maxAge):
        return f"SELECT * FROM {self.table_name} WHERE age BETWEEN {minAge} AND {maxAge};"