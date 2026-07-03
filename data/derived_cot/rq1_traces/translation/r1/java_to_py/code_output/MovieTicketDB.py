import sqlite3
import traceback

class MovieTicketDB:
    class Ticket:
        def __init__(self, id, movie_name, theater_name, seat_number, customer_name):
            self.id = id
            self.movie_name = movie_name
            self.theater_name = theater_name
            self.seat_number = seat_number
            self.customer_name = customer_name
        
        def getId(self):
            return self.id
        
        def getMovieName(self):
            return self.movie_name
        
        def getTheaterName(self):
            return self.theater_name
        
        def getSeatNumber(self):
            return self.seat_number
        
        def getCustomerName(self):
            return self.customer_name

    def __init__(self, dbName):
        self.connection = None
        try:
            self.connection = sqlite3.connect(dbName, isolation_level=None)
            self.createTable()
        except sqlite3.Error as e:
            traceback.print_exc()

    def createTable(self):
        sql = """CREATE TABLE IF NOT EXISTS tickets (
                 id INTEGER PRIMARY KEY AUTOINCREMENT,
                 movie_name TEXT,
                 theater_name TEXT,
                 seat_number TEXT,
                 customer_name TEXT)"""
        try:
            self.connection.execute(sql)
        except sqlite3.Error as e:
            traceback.print_exc()

    def insertTicket(self, movieName, theaterName, seatNumber, customerName):
        sql = "INSERT INTO tickets (movie_name, theater_name, seat_number, customer_name) VALUES (?, ?, ?, ?)"
        try:
            self.connection.execute(sql, (movieName, theaterName, seatNumber, customerName))
        except sqlite3.Error as e:
            traceback.print_exc()

    def searchTicketsByCustomer(self, customerName):
        sql = "SELECT * FROM tickets WHERE customer_name = ?"
        tickets = []
        cursor = None
        try:
            cursor = self.connection.execute(sql, (customerName,))
            rows = cursor.fetchall()
            for row in rows:
                ticket = self.Ticket(row[0], row[1], row[2], row[3], row[4])
                tickets.append(ticket)
        except sqlite3.Error as e:
            traceback.print_exc()
        finally:
            if cursor:
                cursor.close()
        return tickets

    def deleteTicket(self, ticketId):
        sql = "DELETE FROM tickets WHERE id = ?"
        try:
            self.connection.execute(sql, (ticketId,))
        except sqlite3.Error as e:
            traceback.print_exc()

    def close(self):
        if self.connection is not None:
            try:
                self.connection.close()
            except sqlite3.Error as e:
                traceback.print_exc()