class MovieBookingSystem:
    def __init__(self):
        self.movies = []  # each movie: dict with name, price, start_time, end_time, seats

    def parse_time(self, time_str):
        """Parse "HH:MM" string into (hour, minute) tuple."""
        parts = time_str.split(':')
        if len(parts) != 2:
            raise RuntimeError("Failed to parse time")
        try:
            h, m = int(parts[0]), int(parts[1])
        except ValueError:
            raise RuntimeError("Failed to parse time")
        return (h, m)

    def is_time_in_range(self, start, end, check):
        """Check if time `check` is within [start, end] inclusive (based on seconds since midnight)."""
        def to_seconds(t):
            return t[0] * 3600 + t[1] * 60
        return to_seconds(start) <= to_seconds(check) <= to_seconds(end)

    def add_movie(self, name, price, start_time, end_time, n):
        """Add a movie with given details and an n x n seat grid (all seats initially free)."""
        movie = {
            'name': name,
            'price': price,
            'start_time': self.parse_time(start_time),
            'end_time': self.parse_time(end_time),
            'seats': [[0] * n for _ in range(n)]
        }
        self.movies.append(movie)

    def book_ticket(self, name, seats):
        """
        Attempt to book a list of seats (row, col) for the movie with the given name.
        Returns "Booking success." or an appropriate failure message.
        """
        for movie in self.movies:
            if movie['name'] == name:
                for row, col in seats:
                    if not (0 <= row < len(movie['seats']) and 0 <= col < len(movie['seats'][row])):
                        return "Booking failed."
                    if movie['seats'][row][col] == 0:
                        movie['seats'][row][col] = 1
                    else:
                        return "Booking failed."
                return "Booking success."
        return "Movie not found."

    def available_movies(self, start_time, end_time):
        """
        Return list of movie names that run entirely within the given time interval.
        Both movie start_time and end_time must lie in [start_time, end_time].
        """
        start = self.parse_time(start_time)
        end = self.parse_time(end_time)
        available = []
        for movie in self.movies:
            if (self.is_time_in_range(start, end, movie['start_time']) and
                self.is_time_in_range(start, end, movie['end_time'])):
                available.append(movie['name'])
        return available