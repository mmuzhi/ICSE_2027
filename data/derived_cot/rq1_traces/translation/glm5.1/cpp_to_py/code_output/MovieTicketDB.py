import sqlite3


class MovieTicketDB:
    def __init__(self, db_name: str):
        self.db_name = db_name
        self.db = None
        try:
            self.db = sqlite3.connect(db_name)
        except sqlite3.Error:
            raise RuntimeError("Unable to open database")
        self._create_table()

    def __del__(self):
        self.close_connection()

    def _create_table(self):
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
            raise RuntimeError(f"Failed to create table: {e}")

    def insert_ticket(self, movie_name: str, theater_name: str,
                      seat_number: str, customer_name: str):
        insert_sql = """
            INSERT INTO tickets (movie_name, theater_name, seat_number, customer_name)
            VALUES (?, ?, ?, ?)
        """
        try:
            cursor = self.db.cursor()
            cursor.execute(insert_sql, (movie_name, theater_name, seat_number, customer_name))
            self.db.commit()
        except sqlite3.Error:
            raise RuntimeError("Failed to insert ticket")

    def search_tickets_by_customer(self, customer_name: str):
        search_sql = """
            SELECT * FROM tickets WHERE customer_name = ?
        """
        try:
            cursor = self.db.cursor()
            cursor.execute(search_sql, (customer_name,))
            results = []
            for row in cursor.fetchall():
                # sqlite3_column_text in C++ returns text for all columns;
                # convert all values to str to match that behavior
                results.append([str(val) for val in row])
            return results
        except sqlite3.Error:
            raise RuntimeError("Failed to prepare statement")

    def delete_ticket(self, ticket_id: str):
        delete_sql = """
            DELETE FROM tickets WHERE id = ?
        """
        try:
            cursor = self.db.cursor()
            cursor.execute(delete_sql, (ticket_id,))
            self.db.commit()
        except sqlite3.Error:
            raise RuntimeError("Failed to delete ticket")

    def close_connection(self):
        if self.db is not None:
            self.db.close()
            self.db = None