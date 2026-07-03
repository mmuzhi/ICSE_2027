class SQLGenerator:
    def __init__(self, table_name):
        self.table_name = table_name

    def select(self, fields=None, condition=""):
        if fields is None:
            fields = []
        if fields:
            fields_str = ", ".join(fields)
        else:
            fields_str = "*"
        sql = f"SELECT {fields_str} FROM {self.table_name}"
        if condition:
            sql += f" WHERE {condition}"
        return sql + ";"

    def insert(self, data):
        fields = []
        values = []
        for key in sorted(data.keys()):
            fields.append(key)
            values.append(f"'{data[key]}'")
        sql = f"INSERT INTO {self.table_name} ({', '.join(fields)}) VALUES ({', '.join(values)})"
        return sql + ";"

    def update(self, data, condition):
        set_parts = []
        for key in sorted(data.keys()):
            set_parts.append(f"{key} = '{data[key]}'")
        sql = f"UPDATE {self.table_name} SET {', '.join(set_parts)}"
        if condition:
            sql += f" WHERE {condition}"
        return sql + ";"

    def delete_query(self, condition):
        sql = f"DELETE FROM {self.table_name}"
        if condition:
            sql += f" WHERE {condition}"
        return sql + ";"

    def select_female_under_age(self, age):
        condition = f"age < {age} AND gender = 'female'"
        return self.select([], condition)

    def select_by_age_range(self, min_age, max_age):
        condition = f"age BETWEEN {min_age} AND {max_age}"
        return self.select([], condition)