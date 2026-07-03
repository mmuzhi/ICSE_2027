import re
from typing import Dict, List, Optional, Union

def select(table: str, columns: Union[str, List[str]] = "*", where: Optional[Dict[str, str]] = None) -> str:
    if columns is None:
        columns = "*"
    if columns == "*":
        columns_list = []
    elif isinstance(columns, str):
        columns_list = re.split(r',\s*', columns)
    elif isinstance(columns, (list, tuple)):
        columns_list = list(columns)
    else:
        raise TypeError("columns must be a string or a list/tuple of strings")
    
    if not columns_list:
        cols_str = "*"
    else:
        cols_str = ", ".join(columns_list)
    
    query = f"SELECT {cols_str} FROM {table}"
    
    if where is not None and where:
        conditions = []
        for col, val in where.items():
            conditions.append(f"{col}='{val}'")
        query += " WHERE " + " AND ".join(conditions)
    
    return query

def insert(table: str, data: Dict[str, str]) -> str:
    if not data:
        return f"INSERT INTO {table} () VALUES ()"
    
    cols = []
    vals = []
    for col, val in data.items():
        cols.append(col)
        vals.append(f"'{val}'")
    
    cols_str = ", ".join(cols)
    vals_str = ", ".join(vals)
    
    return f"INSERT INTO {table} ({cols_str}) VALUES ({vals_str})"

def delete(table: str, where: Optional[Dict[str, str]] = None) -> str:
    query = f"DELETE FROM {table}"
    
    if where is not None and where:
        conditions = []
        for col, val in where.items():
            conditions.append(f"{col}='{val}'")
        query += " WHERE " + " AND ".join(conditions)
    
    return query

def update(table: str, data: Dict[str, str], where: Optional[Dict[str, str]] = None) -> str:
    set_parts = []
    for col, val in data.items():
        set_parts.append(f"{col}='{val}'")
    set_clause = ", ".join(set_parts)
    
    query = f"UPDATE {table} SET {set_clause}"
    
    if where is not None and where:
        conditions = []
        for col, val in where.items():
            conditions.append(f"{col}='{val}'")
        query += " WHERE " + " AND ".join(conditions)
    
    return query