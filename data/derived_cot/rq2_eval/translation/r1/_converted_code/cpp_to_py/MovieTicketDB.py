import sqlite3
import os

class MovieTicketDB:
    def __init__(self, dbName):
        self.dbName = dbName
        try:
            self.db = sqlite3.connect(dbName)
        except sqlite3.Error as e:
            raise RuntimeError(f"Unable to open database: {str(e)}")
        self.create_table()

    def __del__(self):
        self.close_connection()

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
            cursor = self.db.cursor()
            cursor.execute(create_table_sql)
            self.db.commit()
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to create table: {str(e)}")

    def insert_ticket(self, movieName, theaterName, seatNumber, customerName):
        insert_sql = """
        INSERT INTO tickets (movie_name, theater_name, seat_number, customer_name)
        VALUES (?, ?, ?, ?)
        """
        try:
            cursor = self.db.cursor()
            cursor.execute(insert_sql, (movieName, theaterName, seatNumber, customerName))
            self.db.commit()
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to insert ticket: {str(e)}")

    def search_tickets_by_customer(self, customerName):
        search_sql = """
        SELECT * FROM tickets WHERE customer_name = ?
        """
        try:
            cursor = self.db.cursor()
            cursor.execute(search_sql, (customerName,))
            rows = cursor.fetchall()
            results = []
            for row in rows:
                results.append([str(item) for item in row])
            return results
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to search tickets: {str(e)}")

    def delete_ticket(self, ticketId):
        delete_sql = """
        DELETE FROM tickets WHERE id = ?
        """
        try:
            cursor = self.db.cursor()
            cursor.execute(delete_sql, (ticketId,))
            self.db.commit()
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to delete ticket: {str(e)}")

    def close_connection(self):
        if hasattr(self, 'db') and self.db:
            self.db.close()
            self.db = None