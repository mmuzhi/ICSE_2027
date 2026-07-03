import datetime

class MovieBookingSystem:
    def __init__(self):
        self.movies = []

    def add_movie(self, name, price, start_time, end_time, n):
        start_time_obj = self.parse_time(start_time)
        end_time_obj = self.parse_time(end_time)
        movie = {
            'name': name,
            'price': price,
            'start_time': start_time_obj,
            'end_time': end_time_obj,
            'seats': [[0] * n for _ in range(n)]
        }
        self.movies.append(movie)

    @staticmethod
    def parse_time(time_str):
        return datetime.datetime.strptime(time_str, "%H:%M").time()

    def is_time_in_range(self, start, end, check):
        def time_to_seconds(t):
            return t.hour * 3600 + t.minute * 60
        
        start_seconds = time_to_seconds(start)
        end_seconds = time_to_seconds(end)
        check_seconds = time_to_seconds(check)
        
        return start_seconds <= check_seconds <= end_seconds

    def book_ticket(self, name, seats_to_book):
        for movie in self.movies:
            if movie['name'] == name:
                for seat in seats_to_book:
                    row, col = seat
                    if not (0 <= row < len(movie['seats']) and 0 <= col < len(movie['seats'][0])):
                        return "Booking failed."
                    if movie['seats'][row][col] == 0:
                        movie['seats'][row][col] = 1
                    else:
                        return "Booking failed."
                return "Booking success."
        return "Movie not found."

    def available_movies(self, start_time, end_time):
        start_obj = self.parse_time(start_time)
        end_obj = self.parse_time(end_time)
        available = []
        for movie in self.movies:
            if self.is_time_in_range(start_obj, end_obj, movie['start_time']) and self.is_time_in_range(start_obj, end_obj, movie['end_time']):
                available.append(movie['name'])
        return available