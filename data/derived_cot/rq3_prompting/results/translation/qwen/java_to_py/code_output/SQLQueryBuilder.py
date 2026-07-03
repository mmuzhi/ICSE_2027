class SQLQueryBuilder:

    @staticmethod
    def select(table, columns=None, where=None):
        if columns is None:
            columns = ["*"]
        elif isinstance(columns, str):
            columns = [col.strip() for col in columns.split(",")]
        return SQLQueryBuilder._select(table, columns, where)

    @staticmethod
    def _select(table, columns, where=None):
        query = "SELECT "
        if columns and columns[0] != "*":
            query += ", ".join(columns)
        else:
            query += "*"
        query += f" FROM {table}"

        if where is not None and len(where) > 0:
            query += " WHERE "
            first = True
            for key, value in where.items():
                if not first:
                    query += " AND "
                query += f"{key}='{value}'"
                first = False
        return query

    @staticmethod
    def insert(table, data):
        query = f"INSERT INTO {table} ("
        values = " VALUES ("
        first = True
        for key, value in data.items():
            if not first:
                query += ", "
                values += ", "
            query += key
            values += f"'{value}'"
            first = False
        query += ")"
        query += values + ")"
        return query

    @staticmethod
    def delete(table, where=None):
        query = f"DELETE FROM {table}"
        if where is not None and len(where) > 0:
            query += " WHERE "
            first = True
            for key, value in where.items():
                if not first:
                    query += " AND "
                query += f"{key}='{value}'"
                first = False
        return query

    @staticmethod
    def update(table, data, where=None):
        query = f"UPDATE {table} SET "
        first = True
        for key, value in data.items():
            if not first:
                query += ", "
            query += f"{key}='{value}'"
            first = False
        if where is not None and len(where) > 0:
            query += " WHERE "
            first = True
            for key, value in where.items():
                if not first:
                    query += " AND "
                query += f"{key}='{value}'"
                first = False
        return query