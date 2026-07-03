import datetime
from typing import List, Tuple, Optional

class MovieBookingSystem:
    class Movie:
        def __init__(self, name: str, price: float, start_time: str, end_time: str, n: int):
            self.name = name
            self.price = price
            self.start_time = start_time
            self.end_time = end_time
            self.seats = [[0] * n for _ in range(n)]
    
    def __init__(self):
        self.movies: List[MovieBookingSystem.Movie] = []
    
    def parse_time(self, time_str: str) -> datetime.time:
        try:
            return datetime.datetime.strptime(time_str, "%H:%M").time()
        except ValueError:
            raise ValueError("Failed to parse time")
    
    def is_time_in_range(self, start: datetime.time, end: datetime.time, check: datetime.time) -> bool:
        def to_seconds(time_obj: datetime.time) -> int:
            return time_obj.hour * 3600 + time_obj.minute * 60
        
        start_seconds = to_seconds(start)
        end_seconds = to_seconds(end)
        check_seconds = to_seconds(check)
        return start_seconds <= check_seconds <= end_seconds
    
    def add_movie(self, name: str, price: float, start_time: str, end_time: str, n: int) -> None:
        movie = MovieBookingSystem.Movie(name, price, start_time, end_time, n)
        self.movies.append(movie)
    
    def book_ticket(self, name: str, seats_to_book: List[Tuple[int, int]]) -> str:
        for movie in self.movies:
            if movie.name == name:
                for row, col in seats_to_book:
                    if row < 0 or row >= len(movie.seats) or col < 0 or col >= len(movie.seats[row]):
                        return "Booking failed."
                    if movie.seats[row][col] == 0:
                        movie.seats[row][col] = 1
                    else:
                        return "Booking failed."
                return "Booking success."
        return "Movie not found."
    
    def available_movies(self, start_time: str, end_time: str) -> List[str]:
        start = self.parse_time(start_time)
        end = self.parse_time(end_time)
        available = []
        for movie in self.movies:
            if self.is_time_in_range(start, end, movie.start_time) and self.is_time_in_range(start, end, movie.end_time):
                available.append(movie.name)
        return available