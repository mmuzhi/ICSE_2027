from datetime import datetime, time

class Movie:
    def __init__(self, name, price, start_time, end_time, seats):
        self.name = name
        self.price = price
        self.start_time = start_time
        self.end_time = end_time
        self.seats = seats

class MovieBookingSystem:
    def __init__(self):
        self.movies = []

    def add_movie(self, name, price, start_time_str, end_time_str, n):
        start_time = time.fromisoformat(start_time_str)
        end_time = time.fromisoformat(end_time_str)
        seats = [[0] * n for _ in range(n)]
        movie = Movie(name, price, start_time, end_time, seats)
        self.movies.append(movie)

    def book_ticket(self, name, seats_to_book):
        for movie in self.movies:
            if movie.name == name:
                seats = movie.seats
                for row, col in seats_to_book:
                    if 0 <= row < len(seats) and 0 <= col < len(seats[row]):
                        if seats[row][col] == 0:
                            seats[row][col] = 1
                        else:
                            return "Booking failed."
                return "Booking success."
        return "Movie not found."

    def available_movies(self, start_time_str, end_time_str):
        start_time = time.fromisoformat(start_time_str)
        end_time = time.fromisoformat(end_time_str)
        available = []
        for movie in self.movies:
            if not movie.start_time < start_time and not movie.end_time > end_time:
                available.append(movie.name)
        return available

    def get_movies(self):
        return self.movies