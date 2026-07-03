import sqlite3
from typing import List, List, Any

class MovieTicketDB:
    def __init__(self, dbName: str):
        self.dbName = dbName
        self.conn = None
        self.create_connection()
        self.create_table()

    def create_connection(self):
        try:
            self.conn = sqlite3.connect(self.dbName)
        except sqlite3.Error as e:
            raise ValueError(f"Unable to open database: {e}")

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
            self.conn.execute(create_tableSQL)
        except sqlite3.Error as e:
            raise ValueError(f"Failed to create table: {e}")

    def insert_ticket(self, movieName: str, theaterName: str, seatNumber: str, customerName: str):
        insertSQL = """
            INSERT INTO tickets (movie_name, theater_name, seat_number, customer_name)
            VALUES (?, ?, ?, ?)
        """
        try:
            self.conn.execute(insertSQL, (movieName, theaterName, seatNumber, customerName))
        except sqlite3.Error as e:
            raise ValueError(f"Failed to insert ticket: {e}")

    def search_tickets_by_customer(self, customerName: str) -> List[List[str]]:
        searchSQL = """
            SELECT * FROM tickets WHERE customer_name = ?
        """
        try:
            cursor = self.conn.execute(searchSQL, (customerName,))
            return [list(row) for row in cursor.fetchall()]
        except sqlite3.Error as e:
            raise ValueError(f"Failed to search tickets: {e}")

    def delete_ticket(self, ticketId: str):
        deleteSQL = """
            DELETE FROM tickets WHERE id = ?
        """
        try:
            self.conn.execute(deleteSQL, (ticketId,))
        except sqlite3.Error as e:
            raise ValueError(f"Failed to delete ticket: {e}")

    def close_connection(self):
        if self.conn:
            self.conn.close()
            self.conn = None

    def __del__(self):
        self.close_connection()