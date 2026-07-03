import datetime

class MovieBookingSystem:
    class Movie:
        __slots__ = ('name', 'price', 'start_seconds', 'end_seconds', 'seats')
        def __init__(self, name, price, start_seconds, end_seconds, n):
            self.name = name
            self.price = price
            self.start_seconds = start_seconds
            self.end_seconds = end_seconds
            self.seats = [[0] * n for _ in range(n)]
    
    def __init__(self):
        self.movies = []
    
    def parse_time(self, time_str):
        try:
            dt = datetime.datetime.strptime(time_str, "%H:%M")
            return dt.hour * 3600 + dt.minute * 60
        except ValueError:
            raise RuntimeError("Failed to parse time")
    
    def is_time_in_range(self, start_seconds, end_seconds, check_seconds):
        return start_seconds <= check_seconds <= end_seconds
    
    def add_movie(self, name, price, start_time, end_time, n):
        start_seconds = self.parse_time(start_time)
        end_seconds = self.parse_time(end_time)
        movie = self.Movie(name, price, start_seconds, end_seconds, n)
        self.movies.append(movie)
    
    def book_ticket(self, name, seats_to_book):
        for movie in self.movies:
            if movie.name == name:
                n_rows = len(movie.seats)
                n_cols = len(movie.seats[0]) if n_rows > 0 else 0
                for (row, col) in seats_to_book:
                    if row < 0 or row >= n_rows or col < 0 or col >= n_cols:
                        return "Booking failed."
                    if movie.seats[row][col] != 0:
                        return "Booking failed."
                for (row, col) in seats_to_book:
                    movie.seats[row][col] = 1
                return "Booking success."
        return "Movie not found."
    
    def available_movies(self, start_time, end_time):
        start_seconds = self.parse_time(start_time)
        end_seconds = self.parse_time(end_time)
        available = []
        for movie in self.movies:
            if self.is_time_in_range(start_seconds, end_seconds, movie.start_seconds) and \
               self.is_time_in_range(start_seconds, end_seconds, movie.end_seconds):
                available.append(movie.name)
        return available