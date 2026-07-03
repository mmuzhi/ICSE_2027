import sqlite3
import traceback
from typing import List, Optional


class MovieTicketDB:
    class Ticket:
        __slots__ = ("id", "movie_name", "theater_name", "seat_number", "customer_name")

        def __init__(
            self,
            id: int,
            movie_name: str,
            theater_name: str,
            seat_number: str,
            customer_name: str,
        ):
            self.id = id
            self.movie_name = movie_name
            self.theater_name = theater_name
            self.seat_number = seat_number
            self.customer_name = customer_name

        @property
        def get_id(self) -> int:
            return self.id

        @property
        def get_movie_name(self) -> str:
            return self.movie_name

        @property
        def get_theater_name(self) -> str:
            return self.theater_name

        @property
        def get_seat_number(self) -> str:
            return self.seat_number

        @property
        def get_customer_name(self) -> str:
            return self.customer_name

    def __init__(self, db_name: str):
        self.connection: Optional[sqlite3.Connection] = None
        try:
            self.connection = sqlite3.connect(db_name)
            self._create_table()
        except sqlite3.Error:
            traceback.print_exc()

    def _create_table(self) -> None:
        sql = (
            "CREATE TABLE IF NOT EXISTS tickets ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "movie_name TEXT, "
            "theater_name TEXT, "
            "seat_number TEXT, "
            "customer_name TEXT)"
        )
        try:
            cursor = self.connection.cursor()
            cursor.execute(sql)
            self.connection.commit()
        except sqlite3.Error:
            traceback.print_exc()

    def insert_ticket(
        self,
        movie_name: str,
        theater_name: str,
        seat_number: str,
        customer_name: str,
    ) -> None:
        sql = "INSERT INTO tickets (movie_name, theater_name, seat_number, customer_name) VALUES (?, ?, ?, ?)"
        try:
            cursor = self.connection.cursor()
            cursor.execute(sql, (movie_name, theater_name, seat_number, customer_name))
            self.connection.commit()
        except sqlite3.Error:
            traceback.print_exc()

    def search_tickets_by_customer(self, customer_name: str) -> List["MovieTicketDB.Ticket"]:
        sql = "SELECT * FROM tickets WHERE customer_name = ?"
        tickets: List[MovieTicketDB.Ticket] = []
        try:
            cursor = self.connection.cursor()
            cursor.execute(sql, (customer_name,))
            for row in cursor.fetchall():
                ticket = MovieTicketDB.Ticket(
                    id=row[0],
                    movie_name=row[1],
                    theater_name=row[2],
                    seat_number=row[3],
                    customer_name=row[4],
                )
                tickets.append(ticket)
        except sqlite3.Error:
            traceback.print_exc()
        return tickets

    def delete_ticket(self, ticket_id: int) -> None:
        sql = "DELETE FROM tickets WHERE id = ?"
        try:
            cursor = self.connection.cursor()
            cursor.execute(sql, (ticket_id,))
            self.connection.commit()
        except sqlite3.Error:
            traceback.print_exc()

    def close(self) -> None:
        try:
            if self.connection is not None:
                self.connection.close()
        except sqlite3.Error:
            traceback.print_exc()