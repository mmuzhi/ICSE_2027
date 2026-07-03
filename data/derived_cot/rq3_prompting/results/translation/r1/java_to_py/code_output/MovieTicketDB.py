import sqlite3
import traceback


class MovieTicketDB:
    class Ticket:
        def __init__(self, id_: int, movie_name: str, theater_name: str, seat_number: str, customer_name: str):
            self.id = id_
            self.movie_name = movie_name
            self.theater_name = theater_name
            self.seat_number = seat_number
            self.customer_name = customer_name

        def get_id(self) -> int:
            return self.id

        def get_movie_name(self) -> str:
            return self.movie_name

        def get_theater_name(self) -> str:
            return self.theater_name

        def get_seat_number(self) -> str:
            return self.seat_number

        def get_customer_name(self) -> str:
            return self.customer_name

    def __init__(self, db_name: str):
        try:
            self.connection = sqlite3.connect(db_name)
            self._create_table()
        except sqlite3.Error:
            traceback.print_exc()
            self.connection = None

    def _create_table(self):
        sql = """CREATE TABLE IF NOT EXISTS tickets (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            movie_name TEXT,
            theater_name TEXT,
            seat_number TEXT,
            customer_name TEXT
        )"""
        try:
            with self.connection:
                self.connection.execute(sql)
        except sqlite3.Error:
            traceback.print_exc()

    def insert_ticket(self, movie_name: str, theater_name: str, seat_number: str, customer_name: str):
        sql = "INSERT INTO tickets (movie_name, theater_name, seat_number, customer_name) VALUES (?, ?, ?, ?)"
        try:
            with self.connection:
                self.connection.execute(sql, (movie_name, theater_name, seat_number, customer_name))
        except sqlite3.Error:
            traceback.print_exc()

    def search_tickets_by_customer(self, customer_name: str):
        sql = "SELECT * FROM tickets WHERE customer_name = ?"
        tickets = []
        try:
            with self.connection:
                cursor = self.connection.execute(sql, (customer_name,))
                for row in cursor:
                    ticket = self.Ticket(
                        id_=row[0],
                        movie_name=row[1],
                        theater_name=row[2],
                        seat_number=row[3],
                        customer_name=row[4]
                    )
                    tickets.append(ticket)
        except sqlite3.Error:
            traceback.print_exc()
        return tickets

    def delete_ticket(self, ticket_id: int):
        sql = "DELETE FROM tickets WHERE id = ?"
        try:
            with self.connection:
                self.connection.execute(sql, (ticket_id,))
        except sqlite3.Error:
            traceback.print_exc()

    def close(self):
        try:
            if self.connection is not None:
                self.connection.close()
        except sqlite3.Error:
            traceback.print_exc()