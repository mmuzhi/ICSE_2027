class SQLQueryBuilder:

    @staticmethod
    def select(table, columns=['*'], where_conditions=[]):
        if columns == ['*']:
            query = 'SELECT *'
        else:
            query = 'SELECT ' + ', '.join(columns)
        query += f' FROM {table}'
        if where_conditions:
            conditions = ' AND '.join([f"{col}='{val}'" for col, val in where_conditions])
            query += f' WHERE {conditions}'
        return query

    @staticmethod
    def insert(table, data):
        columns = ', '.join([col for col, _ in data])
        values = ', '.join([f"'{val}'" for _, val in data])
        return f'INSERT INTO {table} ({columns}) VALUES ({values})'

    @staticmethod
    def delete(table, where_conditions=[]):
        query = f'DELETE FROM {table}'
        if where_conditions:
            conditions = ' AND '.join([f"{col}='{val}'" for col, val in where_conditions])
            query += f' WHERE {conditions}'
        return query

    @staticmethod
    def update(table, data, where_conditions=[]):
        set_clause = ', '.join([f"{col}='{val}'" for col, val in data])
        query = f'UPDATE {table} SET {set_clause}'
        if where_conditions:
            conditions = ' AND '.join([f"{col}='{val}'" for col, val in where_conditions])
            query += f' WHERE {conditions}'
        return query