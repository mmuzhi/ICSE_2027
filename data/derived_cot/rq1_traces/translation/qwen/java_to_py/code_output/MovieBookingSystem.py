from datetime import datetime, time

def parse_time_str(time_str):
    for fmt in ("%H:%M:%S", "%H:%M"):
        try:
            t = datetime.strptime(time_str, fmt).time()
            return t
        except ValueError:
            continue
    raise ValueError(f"Time format not recognized: {time_str}")

class MovieBookingSystem:
    def __init__(self):
        self.movies = []

    def addMovie(self, name, price, start_time_str, end_time_str, n):
        start_time = parse_time_str(start_time_str)
        end_time = parse_time_str(end_time_str)
        movie = {
            "name": name,
            "price": price,
            "start_time": start_time,
            "end_time": end_time,
            "seats": [[0] * n for _ in range(n)]
        }
        self.movies.append(movie)

    def bookTicket(self, name, seats_to_book):
        for movie in self.movies:
            if movie["name"] == name:
                seats = movie["seats"]
                for seat in seats_to_book:
                    row, col = seat
                    if row < 0 or row >= len(seats) or col < 0 or col >= len(seats[row]):
                        return "Invalid seat."
                    if seats[row][col] == 0:
                        seats[row][col] = 1
                    else:
                        return "Booking failed."
                return "Booking success."
        return "Movie not found."

    def availableMovies(self, start_time_str, end_time_str):
        start_time = parse_time_str(start_time_str)
        end_time = parse_time_str(end_time_str)
        available = []
        for movie in self.movies:
            movie_start = movie["start_time"]
            movie_end = movie["end_time"]
            if not movie_start.replace(microsecond=0) < start_time and \
               not movie_end.replace(microsecond=0) > end_time:
                available.append(movie["name"])
        return available

    def getMovies(self):
        return self.movies