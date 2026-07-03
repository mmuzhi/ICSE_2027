import sqlite3
from typing import List


class MovieTicketDB:
    def __init__(self, db_name: str):
        self.db_name = db_name
        self.db: sqlite3.Connection | None = None
        # open database, exactly like C++ (no commit management change)
        try:
            self.db = sqlite3.connect(db_name)
            # enable autocommit to match C++ behaviour (no explicit commit)
            self.db.isolation_level = None
        except sqlite3.Error as e:
            raise RuntimeError("Unable to open database") from e
        # create table (throws on failure, mimicking C++ constructor behaviour)
        self.create_table()

    def __del__(self):
        self.close_connection()

    def close_connection(self):
        if self.db is not None:
            self.db.close()
            self.db = None

    def create_table(self):
        create_table_sql = """
            CREATE TABLE IF NOT EXISTS tickets (
                id INTEGER PRIMARY KEY,
                movie_name TEXT,
                theater_name TEXT,
                seat_number TEXT,
                customer_name TEXT
            )
        """
        try:
            self.db.executescript(create_table_sql)
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to create table: {str(e)}") from e

    def insert_ticket(self, movie_name: str, theater_name: str,
                      seat_number: str, customer_name: str):
        insert_sql = """
            INSERT INTO tickets (movie_name, theater_name, seat_number, customer_name)
            VALUES (?, ?, ?, ?)
        """
        try:
            self.db.execute(insert_sql, (movie_name, theater_name, seat_number, customer_name))
        except sqlite3.Error as e:
            raise RuntimeError("Failed to insert ticket") from e

    def search_tickets_by_customer(self, customer_name: str) -> List[List[str]]:
        search_sql = "SELECT * FROM tickets WHERE customer_name = ?"
        try:
            cursor = self.db.execute(search_sql, (customer_name,))
            rows = cursor.fetchall()
        except sqlite3.Error as e:
            raise RuntimeError("Failed to prepare statement") from e
        results: List[List[str]] = []
        for row in rows:
            # Convert every value to string, matching the C++ code which uses sqlite3_column_text.
            # Note: this will convert integers (like id) to their string representation, and None to 'None'.
            # The C++ code would crash on NULL pointers, but we assume no NULLs appear (schema ensures non‑NULL).
            results.append([str(value) for value in row])
        return results

    def delete_ticket(self, ticket_id: str):
        delete_sql = "DELETE FROM tickets WHERE id = ?"
        try:
            self.db.execute(delete_sql, (ticket_id,))
        except sqlite3.Error as e:
            raise RuntimeError("Failed to delete ticket") from e