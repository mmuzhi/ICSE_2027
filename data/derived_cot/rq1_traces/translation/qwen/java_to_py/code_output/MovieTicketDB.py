import sqlite3
from typing import List


class MovieTicketDB:
    def __init__(self, db_name: str):
        self.connection = None
        try:
            self.connection = sqlite3.connect(db_name)
            self.create_table()
        except sqlite3.Error as e:
            print(f"Database error: {e}")

    def create_table(self):
        create_table_query = """
        CREATE TABLE IF NOT EXISTS tickets (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            movie_name TEXT,
            theater_name TEXT,
            seat_number TEXT,
            customer_name TEXT
        )
        """
        try:
            with self.connection if self.connection else sqlite3.connect(':memory:') as conn:
                cursor = conn.cursor()
                cursor.execute(create_table_query)
                conn.commit()
        except sqlite3.Error as e:
            print(f"Table creation error: {e}")

    def insert_ticket(self, movie_name: str, theater_name: str, seat_number: str, customer_name: str):
        insert_query = """
        INSERT INTO tickets 
        (movie_name, theater_name, seat_number, customer_name) 
        VALUES (?, ?, ?, ?)
        """
        try:
            with self.connection if self.connection else sqlite3.connect(':memory:') as conn:
                cursor = conn.cursor()
                cursor.execute(insert_query, (movie_name, theater_name, seat_number, customer_name))
                conn.commit()
        except sqlite3.Error as e:
            print(f"Insert error: {e}")

    def search_tickets_by_customer(self, customer_name: str) -> List['Ticket']:
        select_query = "SELECT * FROM tickets WHERE customer_name = ?"
        tickets = []
        try:
            with self.connection if self.connection else sqlite3.connect(':memory:') as conn:
                cursor = conn.cursor()
                cursor.execute(select_query, (customer_name,))
                for row in cursor.fetchall():
                    tickets.append(Ticket(*row))
        except sqlite3.Error as e:
            print(f"Search error: {e}")
        return tickets

    def delete_ticket(self, ticket_id: int):
        delete_query = "DELETE FROM tickets WHERE id = ?"
        try:
            with self.connection if self.connection else sqlite3.connect(':memory:') as conn:
                cursor = conn.cursor()
                cursor.execute(delete_query, (ticket_id,))
                conn.commit()
        except sqlite3.Error as e:
            print(f"Delete error: {e}")

    def close(self):
        if self.connection:
            try:
                self.connection.close()
            except sqlite3.Error as e:
                print(f"Close error: {e}")

    class Ticket:
        def __init__(self, id: int, movie_name: str, theater_name: str, seat_number: str, customer_name: str):
            self.id = id
            self.movie_name = movie_name
            self.theater_name = theater_name
            self.seat_number = seat_number
            self.customer_name = customer_name

        def __repr__(self):
            return (f"Ticket(id={self.id}, movie_name='{self.movie_name}', "
                    f"theater_name='{self.theater_name}', seat_number='{self.seat_number}', "
                    f"customer_name='{self.customer_name}')")