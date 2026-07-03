import sqlite3
from typing import List

class MovieTicketDB:
    def __init__(self, dbName):
        self.connection = None
        try:
            self.connection = sqlite3.connect(dbName)
            self.createTable()
        except sqlite3.Error as e:
            print(f"Error connecting to database: {e}")

    def createTable(self):
        try:
            cursor = self.connection.cursor()
            cursor.execute('''
                CREATE TABLE IF NOT EXISTS tickets (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    movie_name TEXT,
                    theater_name TEXT,
                    seat_number TEXT,
                    customer_name TEXT
                )
            ''')
            self.connection.commit()
        except sqlite3.Error as e:
            print(f"Error creating table: {e}")

    def insertTicket(self, movieName, theaterName, seatNumber, customerName):
        try:
            cursor = self.connection.cursor()
            cursor.execute('''
                INSERT INTO tickets 
                (movie_name, theater_name, seat_number, customer_name) 
                VALUES (?, ?, ?, ?)
            ''', (movieName, theaterName, seatNumber, customerName))
            self.connection.commit()
        except sqlite3.Error as e:
            print(f"Error inserting ticket: {e}")

    def searchTicketsByCustomer(self, customerName):
        tickets = []
        try:
            cursor = self.connection.cursor()
            cursor.execute('SELECT * FROM tickets WHERE customer_name = ?', (customerName,))
            for row in cursor.fetchall():
                tickets.append(Ticket(
                    row[0],
                    row[1],
                    row[2],
                    row[3],
                    row[4]
                ))
        except sqlite3.Error as e:
            print(f"Error searching tickets: {e}")
        return tickets

    def deleteTicket(self, ticketId):
        try:
            cursor = self.connection.cursor()
            cursor.execute('DELETE FROM tickets WHERE id = ?', (ticketId,))
            self.connection.commit()
        except sqlite3.Error as e:
            print(f"Error deleting ticket: {e}")

    def close(self):
        try:
            if self.connection:
                self.connection.close()
        except sqlite3.Error as e:
            print(f"Error closing connection: {e}")

class Ticket:
    def __init__(self, id: int, movieName: str, theaterName: str, seatNumber: str, customerName: str):
        self.id = id
        self.movieName = movieName
        self.theaterName = theaterName
        self.seatNumber = seatNumber
        self.customerName = customerName

    def __repr__(self):
        return (f"Ticket(id={self.id}, movieName='{self.movieName}', theaterName='{self.theaterName}', "
                f"seatNumber='{self.seatNumber}', customerName='{self.customerName}')")

    def __eq__(self, other):
        if not isinstance(other, Ticket):
            return False
        return (self.id == other.id and
                self.movieName == other.movieName and
                self.theaterName == other.theaterName and
                self.seatNumber == other.seatNumber and
                self.customerName == other.customerName)