from typing import List, Tuple, Optional

class SQLQueryBuilder:
    @staticmethod
    def select(
        table: str,
        columns: Optional[List[str]] = None,
        where: Optional[List[Tuple[str, str]]] = None
    ) -> str:
        if columns is None:
            columns = ["*"]
        if where is None:
            where = []

        if len(columns) == 1 and columns[0] == "*":
            query = "SELECT *"
        else:
            query = "SELECT " + ", ".join(columns)

        query += f" FROM {table}"

        if where:
            conditions = " AND ".join(f"{k}='{v}'" for k, v in where)
            query += f" WHERE {conditions}"

        return query

    @staticmethod
    def insert(
        table: str,
        data: List[Tuple[str, str]]
    ) -> str:
        columns = ", ".join(k for k, v in data)
        values = ", ".join(f"'{v}'" for k, v in data)
        return f"INSERT INTO {table} ({columns}) VALUES ({values})"

    @staticmethod
    def delete_(
        table: str,
        where: Optional[List[Tuple[str, str]]] = None
    ) -> str:
        if where is None:
            where = []

        query = f"DELETE FROM {table}"
        if where:
            conditions = " AND ".join(f"{k}='{v}'" for k, v in where)
            query += f" WHERE {conditions}"

        return query

    @staticmethod
    def update(
        table: str,
        data: List[Tuple[str, str]],
        where: Optional[List[Tuple[str, str]]] = None
    ) -> str:
        if where is None:
            where = []

        set_clause = ", ".join(f"{k}='{v}'" for k, v in data)
        query = f"UPDATE {table} SET {set_clause}"
        if where:
            conditions = " AND ".join(f"{k}='{v}'" for k, v in where)
            query += f" WHERE {conditions}"

        return query