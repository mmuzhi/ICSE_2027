import re


class SQLQueryBuilder:

    @staticmethod
    def select(table, columns, where=None):
        if columns is None:
            columns = "*"
        if isinstance(columns, str):
            columns = re.split(r',\s*', columns)

        if columns:
            col_str = ", ".join(columns)
        else:
            col_str = "*"

        query = f"SELECT {col_str} FROM {table}"

        if where:
            where_parts = []
            for key, value in where.items():
                where_parts.append(f"{key}='{value}'")
            query += " WHERE " + " AND ".join(where_parts)

        return query

    @staticmethod
    def insert(table, data):
        keys = []
        values = []
        for key, value in data.items():
            keys.append(key)
            values.append(f"'{value}'")

        return f"INSERT INTO {table} ({', '.join(keys)}) VALUES ({', '.join(values)})"

    @staticmethod
    def delete(table, where=None):
        query = f"DELETE FROM {table}"

        if where:
            where_parts = []
            for key, value in where.items():
                where_parts.append(f"{key}='{value}'")
            query += " WHERE " + " AND ".join(where_parts)

        return query

    @staticmethod
    def update(table, data, where=None):
        set_parts = []
        for key, value in data.items():
            set_parts.append(f"{key}='{value}'")

        query = f"UPDATE {table} SET {', '.join(set_parts)}"

        if where:
            where_parts = []
            for key, value in where.items():
                where_parts.append(f"{key}='{value}'")
            query += " WHERE " + " AND ".join(where_parts)

        return query