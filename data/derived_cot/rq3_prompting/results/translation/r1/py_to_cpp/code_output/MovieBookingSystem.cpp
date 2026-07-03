#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>

class MovieBookingSystem {
public:
    struct Movie {
        std::string name;
        double price;
        int startMin;  // minutes since midnight
        int endMin;
        std::vector<std::vector<int>> seats;
    };

    std::vector<Movie> movies;

    // Helper: parse "HH:MM" to minutes since midnight
    static int parseTime(const std::string& timeStr) {
        int hour, minute;
        char colon;
        std::stringstream ss(timeStr);
        ss >> hour >> colon >> minute;
        return hour * 60 + minute;
    }

    void add_movie(const std::string& name, double price,
                   const std::string& start_time, const std::string& end_time,
                   int n) {
        Movie movie;
        movie.name = name;
        movie.price = price;
        movie.startMin = parseTime(start_time);
        movie.endMin = parseTime(end_time);
        movie.seats.assign(n, std::vector<int>(n, 0));
        movies.push_back(std::move(movie));
    }

    std::string book_ticket(const std::string& name,
                            const std::vector<std::pair<int,int>>& seats_to_book) {
        for (auto& movie : movies) {
            if (movie.name == name) {
                for (const auto& seat : seats_to_book) {
                    int r = seat.first;
                    int c = seat.second;
                    if (r < 0 || r >= (int)movie.seats.size() ||
                        c < 0 || c >= (int)movie.seats[0].size()) {
                        return "Booking failed.";
                    }
                    if (movie.seats[r][c] == 0) {
                        movie.seats[r][c] = 1;
                    } else {
                        return "Booking failed.";
                    }
                }
                return "Booking success.";
            }
        }
        return "Movie not found.";
    }

    std::vector<std::string> available_movies(const std::string& start_time,
                                               const std::string& end_time) {
        int startMin = parseTime(start_time);
        int endMin = parseTime(end_time);
        std::vector<std::string> result;
        for (const auto& movie : movies) {
            if (startMin <= movie.startMin && movie.endMin <= endMin) {
                result.push_back(movie.name);
            }
        }
        return result;
    }
};