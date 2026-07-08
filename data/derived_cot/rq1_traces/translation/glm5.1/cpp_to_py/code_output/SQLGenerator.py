class SQLGenerator:
    def __init__(self, table_name):
        self.table_name = table_name

    def select(self, fields=None, condition=""):
        if fields is None:
            fields = []
        if fields:
            fields_str = fields[0]
            for i in range(1, len(fields)):
                fields_str += ", " + fields[i]
        else:
            fields_str = "*"

        sql = "SELECT " + fields_str + " FROM " + self.table_name
        if condition:
            sql += " WHERE " + condition
        return sql + ";"

    def insert(self, data):
        # std::map iterates in sorted key order
        sorted_items = sorted(data.items(), key=lambda x: x[0])
        fields_list = []
        values_list = []
        for key, value in sorted_items:
            fields_list.append(key)
            values_list.append("'" + value + "'")

        fields_str = ", ".join(fields_list)
        values_str = ", ".join(values_list)

        sql = "INSERT INTO " + self.table_name + " (" + fields_str + ") VALUES (" + values_str + ")"
        return sql + ";"

    def update(self, data, condition):
        # std::map iterates in sorted key order
        sorted_items = sorted(data.items(), key=lambda x: x[0])
        set_parts = []
        for key, value in sorted_items:
            set_parts.append(key + " = '" + value + "'")

        set_clause = ", ".join(set_parts)

        sql = "UPDATE " + self.table_name + " SET " + set_clause
        if condition:
            sql += " WHERE " + condition
        return sql + ";"

    def delete_query(self, condition):
        sql = "DELETE FROM " + self.table_name
        if condition:
            sql += " WHERE " + condition
        return sql + ";"

    def select_female_under_age(self, age):
        condition = "age < " + str(age) + " AND gender = 'female'"
        return self.select([], condition)

    def select_by_age_range(self, min_age, max_age):
        condition = "age BETWEEN " + str(min_age) + " AND " + str(max_age)
        return self.select([], condition)