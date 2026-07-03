class SQLQueryBuilder:
    @staticmethod
    def select(table, columns=None, where=None):
        if columns is None:
            columns = ["*"]
        if where is None:
            where = []
        parts = []
        if columns == ["*"]:
            parts.append("SELECT *")
        else:
            parts.append("SELECT " + ", ".join(columns))
        parts.append(" FROM " + table)
        if where:
            condition_parts = [f"{k}='{v}'" for k, v in where]
            parts.append("WHERE " + " AND ".join(condition_parts))
        return " ".join(parts)
    
    @staticmethod
    def insert(table, data):
        if not data:
            return f"INSERT INTO {table} () VALUES ()"
        keys = [k for k, v in data]
        values = [f"'{v}'" for k, v in data]
        return f"INSERT INTO {table} ({', '.join(keys)}) VALUES ({', '.join(values)})".strip()
    
    @staticmethod
    def delete_(table, where=None):
        if where is None:
            where = []
        parts = [f"DELETE FROM {table}"]
        if where:
            condition_parts = [f"{k}='{v}'" for k, v in where]
            parts.append("WHERE " + " AND ".join(condition_parts))
        return " ".join(parts)
    
    @staticmethod
    def update(table, data, where=None):
        if where is None:
            where = []
        parts = [f"UPDATE {table} SET"]
        set_parts = []
        for k, v in data:
            set_parts.append(f"{k}='{v}'")
        if set_parts:
            parts.append(", ".join(set_parts))
        if where:
            condition_parts = [f"{k}='{v}'" for k, v in where]
            parts.append("WHERE " + " AND ".join(condition_parts))
        return " ".join(parts)