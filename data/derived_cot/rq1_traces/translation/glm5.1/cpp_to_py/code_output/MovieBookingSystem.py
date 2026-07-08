from datetime import datetime
from typing import List, Tuple

class MovieBookingSystem:
    class Movie:
        def __init__(self):
            self.name = ""
            self.price = 0.0
            self.start_time = None
            self.end_time = None
            self.seats = []

    def __init__(self):
        self.movies = []

    def parse_time(self, time_str: str):
        try:
            # datetime.strptime closely mirrors std::get_time behavior
            return datetime.strptime(time_str, "%H:%M").time()
        except ValueError:
            raise RuntimeError("Failed to parse time")

    def is_time_in_range(self, start, end, check) -> bool:
        def time_to_seconds(t):
            return t.hour * 3600 + t.minute * 60
        return time_to_seconds(start) <= time_to_seconds(check) <= time_to_seconds(end)

    def add_movie(self, name: str, price: float, start_time: str, end_time: str, n: int) -> None:
        movie = self.Movie()
        movie.name = name
        movie.price = price
        movie.start_time = self.parse_time(start_time)
        movie.end_time = self.parse_time(end_time)
        movie.seats = [[0] * n for _ in range(n)]
        self.movies.append(movie)

    def book_ticket(self, name: str, seats_to_book: List[Tuple[int, int]]) -> str:
        for movie in self.movies:
            if movie.name == name:
                for row, col in seats_to_book:
                    if 0 <= row < len(movie.seats) and 0 <= col < len(movie.seats[row]):
                        if movie.seats[row][col] == 0:
                            movie.seats[row][col] = 1
                        else:
                            return "Booking failed."
                    else:
                        return "Booking failed."
                return "Booking success."
        return "Movie not found."

    def available_movies(self, start_time: str, end_time: str) -> List[str]:
        start = self.parse_time(start_time)
        end = self.parse_time(end_time)
        
        available = []
        for movie in self.movies:
            if self.is_time_in_range(start, end, movie.start_time) and \
               self.is_time_in_range(start, end, movie.end_time):
                available.append(movie.name)
        return available