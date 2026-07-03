class SQLGenerator:

    def __init__(self, table_name):
        self.table_name = table_name

    def select(self, fields=None, condition=''):
        if fields is None:
            fields_str = '*'
        else:
            fields_str = ', '.join(fields)
        sql = f'SELECT {fields_str} FROM {self.table_name}'
        if condition:
            sql += f' WHERE {condition}'
        return sql + ';'

    def insert(self, data):
        if not data:
            return 'INSERT INTO ' + self.table_name + ' () VALUES ()'
        fields = ', '.join(data.keys())
        values = ', '.join([f"'{v}'" for v in data.values()])
        return f'INSERT INTO {self.table_name} ({fields}) VALUES ({values}) ;'

    def update(self, data, condition=''):
        if not data:
            return 'UPDATE ' + self.table_name + ' SET  ;'
        set_parts = [f"{key} = '{value}'" for key, value in data.items()]
        set_clause = ', '.join(set_parts)
        sql = f'UPDATE {self.table_name} SET {set_clause}'
        if condition:
            sql += f' WHERE {condition}'
        return sql + ';'

    def delete(self, condition=''):
        sql = f'DELETE FROM {self.table_name}'
        if condition:
            sql += f' WHERE {condition}'
        return sql + ';'

    def select_female_under_age(self, age):
        condition = f"age < {age} AND gender = 'female'"
        return self.select(condition=condition)

    def select_by_age_range(self, min_age, max_age):
        condition = f'age BETWEEN {min_age} AND {max_age}'
        return self.select(condition=condition)