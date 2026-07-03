class SQLQueryBuilder:
    @staticmethod
    def select(table, columns=["*"], where=()):
        if len(columns) == 1 and columns[0] == "*":
            query = "SELECT *"
        else:
            query = "SELECT " + ", ".join(columns)
        query += f" FROM {table}"
        if where:
            conditions = []
            for key, value in where:
                conditions.append(f"{key}='{value}'")
            query += f" WHERE {' AND '.join(conditions)}"
        return query

    @staticmethod
    def insert(table, data):
        if not data:
            return f"INSERT INTO {table} () VALUES ()"
        columns = [item[0] for item in data]
        values = [f"'{item[1]}'" for item in data]
        return f"INSERT INTO {table} ({', '.join(columns)}) VALUES ({', '.join(values)})"

    @staticmethod
    def delete_(table, where=()):
        query = f"DELETE FROM {table}"
        if where:
            conditions = []
            for key, value in where:
                conditions.append(f"{key}='{value}'")
            query += f" WHERE {' AND '.join(conditions)}"
        return query

    @staticmethod
    def update(table, data, where=()):
        if not data:
            return f"UPDATE {table} SET "
        set_parts = [f"{key}='{value}'" for key, value in data]
        query = f"UPDATE {table} SET {', '.join(set_parts)}"
        if where:
            conditions = []
            for key, value in where:
                conditions.append(f"{key}='{value}'")
            query += f" WHERE {' AND '.join(conditions)}"
        return query