import datetime

class MovieBookingSystem:
    def __init__(self):
        self.movies = []

    def addMovie(self, name, price, startTime, endTime, n):
        movie = {
            "name": name,
            "price": price,
            "start_time": datetime.datetime.strptime(startTime, "%H:%M").time(),
            "end_time": datetime.datetime.strptime(endTime, "%H:%M").time(),
            "seats": [[0] * n for _ in range(n)]
        }
        self.movies.append(movie)

    def bookTicket(self, name, seatsToBook):
        for movie in self.movies:
            if movie["name"] == name:
                seats = movie["seats"]
                for seat in seatsToBook:
                    row, col = seat
                    if seats[row][col] == 0:
                        seats[row][col] = 1
                    else:
                        return "Booking failed."
                return "Booking success."
        return "Movie not found."

    def availableMovies(self, startTime, endTime):
        start = datetime.datetime.strptime(startTime, "%H:%M").time()
        end = datetime.datetime.strptime(endTime, "%H:%M").time()
        result = []
        for movie in self.movies:
            movie_start = movie["start_time"]
            movie_end = movie["end_time"]
            if movie_start >= start and movie_end <= end:
                result.append(movie["name"])
        return result

    def getMovies(self):
        return self.movies