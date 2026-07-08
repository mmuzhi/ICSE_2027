from typing import List, Tuple, Optional

class SQLQueryBuilder:
    @staticmethod
    def select(table: str, columns: Optional[List[str]] = None, where: Optional[List[Tuple[str, str]]] = None) -> str:
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
            query += " WHERE " + " AND ".join(f"{key}='{value}'" for key, value in where)
            
        return query

    @staticmethod
    def insert(table: str, data: List[Tuple[str, str]]) -> str:
        cols = ", ".join(key for key, value in data)
        vals = ", ".join(f"'{value}'" for key, value in data)
        return f"INSERT INTO {table} ({cols}) VALUES ({vals})"

    @staticmethod
    def delete_(table: str, where: Optional[List[Tuple[str, str]]] = None) -> str:
        if where is None:
            where = []
        query = f"DELETE FROM {table}"
        if where:
            query += " WHERE " + " AND ".join(f"{key}='{value}'" for key, value in where)
        return query

    @staticmethod
    def update(table: str, data: List[Tuple[str, str]], where: Optional[List[Tuple[str, str]]] = None) -> str:
        if where is None:
            where = []
        query = f"UPDATE {table} SET " + ", ".join(f"{key}='{value}'" for key, value in data)
        if where:
            query += " WHERE " + " AND ".join(f"{key}='{value}'" for key, value in where)
        return query