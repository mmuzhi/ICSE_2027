#include <vector>
#include <string>
#include <cstdio>
#include <utility>
#include <algorithm>

struct Movie {
    std::string name;
    double price;
    int start_time_minutes;
    int end_time_minutes;
    std::vector<std::vector<int>> seats;
};

class MovieBookingSystem {
private:
    std::vector<Movie> movies;

    int string_to_minutes(const std::string& time_str) {
        int hours, minutes;
        char colon;
        if (std::sscanf(time_str.c_str(), "%d:%d", &hours, &minutes) != 2) {
            return -1;
        }
        return hours * 60 + minutes;
    }

public:
    MovieBookingSystem() {}

    void add_movie(const std::string& name, double price, const std::string& start_time, const std::string& end_time, int n) {
        int start_minutes = string_to_minutes(start_time);
        int end_minutes = string_to_minutes(end_time);

        Movie movie;
        movie.name = name;
        movie.price = price;
        movie.start_time_minutes = start_minutes;
        movie.end_time_minutes = end_minutes;
        movie.seats = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
        movies.push_back(movie);
    }

    std::string book_ticket(const std::string& name, const std::vector<std::pair<int, int>>& seats_to_book) {
        for (auto& movie : movies) {
            if (movie.name == name) {
                for (const auto& seat : seats_to_book) {
                    int row = seat.first;
                    int col = seat.second;
                    if (movie.seats[row][col] == 0) {
                        movie.seats[row][col] = 1;
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
        int start_min = string_to_minutes(start_time);
        int end_min = string_to_minutes(end_time);

        std::vector<std::string> available;
        for (const auto& movie : movies) {
            if (start_min <= movie.start_time_minutes && movie.end_time_minutes <= end_min) {
                available.push_back(movie.name);
            }
        }
        return available;
    }
};