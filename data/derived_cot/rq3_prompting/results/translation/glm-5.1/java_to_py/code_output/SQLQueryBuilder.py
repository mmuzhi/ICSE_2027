import re
from typing import Dict, List, Optional, Union


class SQLQueryBuilder:

    @staticmethod
    def select(table: str, columns: Union[str, List[str]], where: Optional[Dict[str, str]]) -> str:
        if isinstance(columns, str):
            columns = re.split(r',\s*', columns) if columns else []
        query = "SELECT "
        if columns:
            query += ", ".join(columns)
        else:
            query += "*"
        query += f" FROM {table}"

        if where:
            conditions = [f"{k}='{v}'" for k, v in where.items()]
            query += " WHERE " + " AND ".join(conditions)
        return query

    @staticmethod
    def insert(table: str, data: Dict[str, str]) -> str:
        keys = ", ".join(data.keys())
        values = ", ".join(f"'{v}'" for v in data.values())
        return f"INSERT INTO {table} ({keys}) VALUES ({values})"

    @staticmethod
    def delete(table: str, where: Optional[Dict[str, str]]) -> str:
        query = f"DELETE FROM {table}"
        if where:
            conditions = [f"{k}='{v}'" for k, v in where.items()]
            query += " WHERE " + " AND ".join(conditions)
        return query

    @staticmethod
    def update(table: str, data: Dict[str, str], where: Optional[Dict[str, str]]) -> str:
        set_clause = ", ".join(f"{k}='{v}'" for k, v in data.items())
        query = f"UPDATE {table} SET {set_clause}"
        if where:
            conditions = [f"{k}='{v}'" for k, v in where.items()]
            query += " WHERE " + " AND ".join(conditions)
        return query