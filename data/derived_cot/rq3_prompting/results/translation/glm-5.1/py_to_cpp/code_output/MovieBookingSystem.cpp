#include <vector>
#include <string>
#include <utility>

class MovieBookingSystem {
private:
    struct Movie {
        std::string name;
        double price;
        int start_time; // stored as minutes since midnight
        int end_time;   // stored as minutes since midnight
        std::vector<std::vector<double>> seats;
    };

    std::vector<Movie> movies;

    int parse_time(const std::string& time_str) {
        int hh = std::stoi(time_str.substr(0, 2));
        int mm = std::stoi(time_str.substr(3, 2));
        return hh * 60 + mm;
    }

public:
    MovieBookingSystem() = default;

    void add_movie(const std::string& name, double price, const std::string& start_time, const std::string& end_time, int n) {
        Movie movie;
        movie.name = name;
        movie.price = price;
        movie.start_time = parse_time(start_time);
        movie.end_time = parse_time(end_time);
        movie.seats = std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));
        movies.push_back(movie);
    }

    std::string book_ticket(const std::string& name, const std::vector<std::pair<int, int>>& seats_to_book) {
        for (auto& movie : movies) {
            if (movie.name == name) {
                for (const auto& seat : seats_to_book) {
                    if (movie.seats[seat.first][seat.second] == 0.0) {
                        movie.seats[seat.first][seat.second] = 1.0;
                    } else {
                        return "Booking failed.";
                    }
                }
                return "Booking success.";
            }
        }
        return "Movie not found.";
    }

    std::vector<std::string> available_movies(const std::string& start_time, const std::string& end_time) {
        int st = parse_time(start_time);
        int et = parse_time(end_time);

        std::vector<std::string> available;
        for (const auto& movie : movies) {
            if (st <= movie.start_time && movie.end_time <= et) {
                available.push_back(movie.name);
            }
        }
        return available;
    }
};