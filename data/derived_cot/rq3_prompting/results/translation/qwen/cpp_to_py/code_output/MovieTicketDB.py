import sqlite3
from typing import List, Any

class MovieTicketDB:
    def __init__(self, dbName: str):
        self.dbName = dbName
        self._conn = None
        try:
            self._conn = sqlite3.connect(dbName)
            self.create_table()
        except sqlite3.Error as e:
            if self._conn:
                self._conn.close()
            raise RuntimeError(f"Unable to open database: {e}") from e

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        self.close()

    def close(self):
        if self._conn:
            self._conn.close()
            self._conn = None

    def create_table(self):
        create_tableSQL = """
            CREATE TABLE IF NOT EXISTS tickets (
                id INTEGER PRIMARY KEY,
                movie_name TEXT,
                theater_name TEXT,
                seat_number TEXT,
                customer_name TEXT
            )
        """
        try:
            self._conn.execute(create_tableSQL)
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to create table: {e}") from e

    def insert_ticket(self, movieName: str, theaterName: str, seatNumber: str, customerName: str):
        insertSQL = """
            INSERT INTO tickets (movie_name, theater_name, seat_number, customer_name)
            VALUES (?, ?, ?, ?)
        """
        try:
            cursor = self._conn.cursor()
            cursor.execute(insertSQL, (movieName, theaterName, seatNumber, customerName))
        except sqlite3.Error as e:
            raise RuntimeError("Failed to insert ticket") from e

    def search_tickets_by_customer(self, customerName: str) -> List[List[str]]:
        searchSQL = """
            SELECT * FROM tickets WHERE customer_name = ?
        """
        try:
            cursor = self._conn.cursor()
            cursor.execute(searchSQL, (customerName,))
            results = []
            for row in cursor.fetchall():
                # Convert each cell to string to match C++ behavior
                row_list = [str(cell) for cell in row]
                results.append(row_list)
            return results
        except sqlite3.Error as e:
            raise RuntimeError("Failed to search tickets") from e

    def delete_ticket(self, ticketId: str):
        deleteSQL = """
            DELETE FROM tickets WHERE id = ?
        """
        try:
            cursor = self._conn.cursor()
            cursor.execute(deleteSQL, (ticketId,))
        except sqlite3.Error as e:
            raise RuntimeError("Failed to delete ticket") from e