import sqlite3
import traceback
from dataclasses import dataclass
from typing import List


class MovieTicketDB:
    @dataclass
    class Ticket:
        id: int
        movie_name: str
        theater_name: str
        seat_number: str
        customer_name: str

    def __init__(self, db_name: str):
        self.connection = None
        self._is_closed = False
        try:
            # isolation_level=None mimics JDBC's auto-commit default behavior
            self.connection = sqlite3.connect(db_name, isolation_level=None)
            self._create_table()
        except sqlite3.Error:
            traceback.print_exc()

    def _create_table(self):
        sql = """CREATE TABLE IF NOT EXISTS tickets (
                id INTEGER PRIMARY KEY AUTOINCREMENT, 
                movie_name TEXT, 
                theater_name TEXT, 
                seat_number TEXT, 
                customer_name TEXT)"""
        try:
            cursor = self.connection.cursor()
            cursor.execute(sql)
            cursor.close()
        except sqlite3.Error:
            traceback.print_exc()

    # Method names are kept in camelCase to preserve the exact API contract 
    # (identical behavior for a caller), while parameters use snake_case.
    def insertTicket(self, movie_name: str, theater_name: str, seat_number: str, customer_name: str):
        sql = "INSERT INTO tickets (movie_name, theater_name, seat_number, customer_name) VALUES (?, ?, ?, ?)"
        try:
            cursor = self.connection.cursor()
            cursor.execute(sql, (movie_name, theater_name, seat_number, customer_name))
            cursor.close()
        except sqlite3.Error:
            traceback.print_exc()

    def searchTicketsByCustomer(self, customer_name: str) -> List[Ticket]:
        sql = "SELECT * FROM tickets WHERE customer_name = ?"
        tickets = []
        try:
            cursor = self.connection.cursor()
            cursor.execute(sql, (customer_name,))
            for row in cursor:
                ticket = self.Ticket(
                    id=row[0],
                    movie_name=row[1],
                    theater_name=row[2],
                    seat_number=row[3],
                    customer_name=row[4]
                )
                tickets.append(ticket)
            cursor.close()
        except sqlite3.Error:
            traceback.print_exc()
        return tickets

    def deleteTicket(self, ticket_id: int):
        sql = "DELETE FROM tickets WHERE id = ?"
        try:
            cursor = self.connection.cursor()
            cursor.execute(sql, (ticket_id,))
            cursor.close()
        except sqlite3.Error:
            traceback.print_exc()

    def close(self):
        try:
            # Mimics the `connection != null && !connection.isClosed()` check in Java
            if self.connection is not None and not self._is_closed:
                self.connection.close()
                self._is_closed = True
        except sqlite3.Error:
            traceback.print_exc()