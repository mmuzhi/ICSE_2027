import datetime

class MovieBookingSystem:

    def __init__(self):
        self.movies = []

    def add_movie(self, name, price, start_time, end_time, n):
        movie = {
            "name": name,
            "price": price,
            "start_time": datetime.time.fromisoformat(start_time),
            "end_time": datetime.time.fromisoformat(end_time),
            "seats": [[0] * n for _ in range(n)]
        }
        self.movies.append(movie)

    def book_ticket(self, name, seats_to_book):
        for movie in self.movies:
            if movie.get("name") == name:
                seats = movie["seats"]
                for seat in seats_to_book:
                    row = seat[0]
                    col = seat[1]
                    if seats[row][col] == 0:
                        seats[row][col] = 1
                    else:
                        return "Booking failed."
                return "Booking success."
        return "Movie not found."

    def available_movies(self, start_time, end_time):
        start = datetime.time.fromisoformat(start_time)
        end = datetime.time.fromisoformat(end_time)
        
        result = []
        for movie in self.movies:
            movie_start = movie["start_time"]
            movie_end = movie["end_time"]
            # !movieStart.isBefore(start) -> movieStart >= start
            # !movieEnd.isAfter(end) -> movieEnd <= end
            if movie_start >= start and movie_end <= end:
                result.append(movie["name"])
        return result

    def get_movies(self):
        return self.movies