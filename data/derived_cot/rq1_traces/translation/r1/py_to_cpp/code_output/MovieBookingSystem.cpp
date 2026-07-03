#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>

class MovieBookingSystem {
public:
    MovieBookingSystem() = default;

    void add_movie(const std::string& name, float price, const std::string& start_time, const std::string& end_time, int n) {
        int start_minutes = timeStrToMinutes(start_time);
        int end_minutes = timeStrToMinutes(end_time);
        std::vector<std::vector<int>> seats(n, std::vector<int>(n, 0));
        movies.push_back({name, price, start_minutes, end_minutes, seats});
    }

    std::string book_ticket(const std::string& name, const std::vector<std::pair<int, int>>& seats_to_book) {
        for (auto& movie : movies) {
            if (movie.name == name) {
                for (const auto& seat : seats_to_book) {
                    int row = seat.first;
                    int col = seat.second;
                    if (row < 0 || row >= movie.seats.size() || col < 0 || col >= movie.seats[0].size()) {
                        return "Booking failed.";
                    }
                    if (movie.seats[row][col] != 0) {
                        return "Booking failed.";
                    }
                    movie.seats[row][col] = 1;
                }
                return "Booking success.";
            }
        }
        return "Movie not found.";
    }

    std::vector<std::string> available_movies(const std::string& start_time, const std::string& end_time) {
        int start_minutes = timeStrToMinutes(start_time);
        int end_minutes = timeStrToMinutes(end_time);
        std::vector<std::string> result;
        for (const auto& movie : movies) {
            if (start_minutes <= movie.start_time && movie.end_time <= end_minutes) {
                result.push_back(movie.name);
            }
        }
        return result;
    }

private:
    struct Movie {
        std::string name;
        float price;
        int start_time; // minutes since midnight
        int end_time;   // minutes since midnight
        std::vector<std::vector<int>> seats; // 0 for available, 1 for booked
    };

    std::vector<Movie> movies;

    int timeStrToMinutes(const std::string& timeStr) {
        std::istringstream iss(timeStr);
        int hours, minutes;
        char colon;
        iss >> hours >> colon >> minutes;
        return hours * 60 + minutes;
    }
};