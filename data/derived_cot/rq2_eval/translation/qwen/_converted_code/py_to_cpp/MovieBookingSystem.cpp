#include <vector>
#include <string>
#include <iostream>
#include <cctype>
#include <algorithm>

struct Movie {
    std::string name;
    double price;
    int start_hour, start_minute;
    int end_hour, end_minute;
    std::vector<std::vector<int>> seats;
};

class MovieBookingSystem {
private:
    std::vector<Movie> movies;

    int parse_time(const std::string& time_str, bool& success) {
        if (time_str.size() != 5 || time_str[2] != ':') {
            success = false;
            return -1;
        }
        try {
            int hour = std::stoi(time_str.substr(0, 2));
            int minute = std::stoi(time_str.substr(3, 2));
            if (hour < 0 || hour >= 24 || minute < 0 || minute >= 60) {
                success = false;
                return -1;
            }
            return hour * 60 + minute;
        } catch (...) {
            success = false;
            return -1;
        }
    }

public:
    MovieBookingSystem() {}

    void add_movie(const std::string& name, double price, const std::string& start_time_str, const std::string& end_time_str, int n) {
        bool start_success = true;
        bool end_success = true;
        int start_minutes = parse_time(start_time_str, start_success);
        int end_minutes = parse_time(end_time_str, end_success);

        if (!start_success || !end_success) {
            std::cout << "Invalid time format. Use HH:MM." << std::endl;
            return;
        }

        Movie movie;
        movie.name = name;
        movie.price = price;
        movie.start_hour = start_minutes / 60;
        movie.start_minute = start_minutes % 60;
        movie.end_hour = end_minutes / 60;
        movie.end_minute = end_minutes % 60;

        movie.seats = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
        movies.push_back(movie);
    }

    std::string book_ticket(const std::string& name, const std::vector<std::pair<int, int>>& seats_to_book) {
        for (auto& movie : movies) {
            if (movie.name == name) {
                for (const auto& seat : seats_to_book) {
                    int row = seat.first;
                    int col = seat.second;
                    if (row < 0 || row >= movie.seats.size() || col < 0 || col >= movie.seats[row].size()) {
                        return "Booking failed.";
                    }
                    if (movie.seats[row][col] == 1) {
                        return "Booking failed.";
                    }
                    movie.seats[row][col] = 1;
                }
                return "Booking success.";
            }
        }
        return "Movie not found.";
    }

    std::vector<std::string> available_movies(const std::string& start_time_str, const std::string& end_time_str) {
        bool start_success = true;
        bool end_success = true;
        int start_minutes = parse_time(start_time_str, start_success);
        int end_minutes = parse_time(end_time_str, end_success);

        if (!start_success || !end_success) {
            std::cout << "Invalid time format. Use HH:MM." << std::endl;
            return {};
        }

        std::vector<std::string> available;
        for (const auto& movie : movies) {
            int movie_start_minutes = movie.start_hour * 60 + movie.start_minute;
            int movie_end_minutes = movie.end_hour * 60 + movie.end_minute;

            if (start_minutes <= movie_start_minutes && movie_end_minutes <= end_minutes) {
                available.push_back(movie.name);
            }
        }
        return available;
    }
};