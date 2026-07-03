import re

class SQLQueryBuilder:

    @staticmethod
    def select(table, columns=None, where=None):
        if columns is None:
            columns = "*"
        else:
            columns = re.split(r',\s*', columns)
        if isinstance(columns, list):
            if columns:
                query = "SELECT " + ", ".join(columns) + " FROM "
            else:
                query = "SELECT * FROM "
        else:
            query = "SELECT " + columns + " FROM "
        query += table
        if where is not None:
            if len(where) > 0:
                first = True
                for key, value in where.items():
                    if not first:
                        query += " AND "
                    query += f"{key}='{value}'"
                    first = False
        return query

    @staticmethod
    def insert(table, data=None):
        if data is None:
            raise TypeError("data cannot be None")
        query = "INSERT INTO " + table + " ("
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
        values += ")"
        return query + values

    @staticmethod
    def delete(table, where=None):
        query = "DELETE FROM " + table
        if where is not None:
            if len(where) > 0:
                query += " WHERE "
                first = True
                for key, value in where.items():
                    if not first:
                        query += " AND "
                    query += f"{key}='{value}'"
                    first = False
        return query

    @staticmethod
    def update(table, data=None, where=None):
        if data is None:
            raise TypeError("data cannot be None")
        query = "UPDATE " + table + " SET "
        first = True
        for key, value in data.items():
            if not first:
                query += ", "
            query += f"{key}='{value}'"
            first = False
        if where is not None:
            if len(where) > 0:
                query += " WHERE "
                first = True
                for key, value in where.items():
                    if not first:
                        query += " AND "
                    query += f"{key}='{value}'"
                    first = False
        return query