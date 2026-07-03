class SQLGenerator:

    def __init__(self, table_name):
        self.table_name = table_name

    def select(self, fields=None, condition=''):
        if fields is None:
            fields = []
        if not fields:
            fields_str = '*'
        else:
            fields_str = ', '.join(fields)
        sql = 'SELECT ' + fields_str + ' FROM ' + self.table_name
        if condition:
            sql += ' WHERE ' + condition
        sql += ';'
        return sql

    def insert(self, data):
        keys = sorted(data.keys())
        fields_str = ', '.join(keys)
        values_str = ', '.join(("'" + data[key] + "'" for key in keys))
        sql = 'INSERT INTO ' + self.table_name + ' (' + fields_str + ') VALUES (' + values_str + ');'
        return sql

    def update(self, data, condition):
        keys = sorted(data.keys())
        set_items = []
        for key in keys:
            set_items.append(f"{key} = '{data[key]}'")
        set_str = ', '.join(set_items)
        sql = 'UPDATE ' + self.table_name + ' SET ' + set_str
        if condition:
            sql += ' WHERE ' + condition
        sql += ';'
        return sql

    def delete(self, condition):
        sql = 'DELETE FROM ' + self.table_name
        if condition:
            sql += ' WHERE ' + condition
        sql += ';'
        return sql

    def select_female_under_age(self, age):
        condition = f"age < {age} AND gender = 'female'"
        return self.select(condition=condition)

    def select_by_age_range(self, min_age, max_age):
        condition = f'age BETWEEN {min_age} AND {max_age}'
        return self.select(condition=condition)