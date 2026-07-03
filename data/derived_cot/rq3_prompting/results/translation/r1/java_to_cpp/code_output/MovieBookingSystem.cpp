#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <cctype>

class MovieBookingSystem {
public:
    MovieBookingSystem() = default;

    void addMovie(const std::string& name, double price,
                  const std::string& startTime, const std::string& endTime, int n) {
        int start = parseTime(startTime);
        int end = parseTime(endTime);
        if (end < start) {
            throw std::invalid_argument("endTime must be after startTime");
        }
        Movie movie;
        movie.name = name;
        movie.price = price;
        movie.startMinutes = start;
        movie.endMinutes = end;
        movie.seats = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
        movies.push_back(movie);
    }

    std::string bookTicket(const std::string& name,
                           const std::vector<std::vector<int>>& seatsToBook) {
        for (auto& movie : movies) {
            if (movie.name == name) {
                for (const auto& seat : seatsToBook) {
                    int row = seat[0];
                    int col = seat[1];
                    // Use at() to replicate Java's ArrayIndexOutOfBoundsException
                    if (movie.seats.at(row).at(col) == 0) {
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

    std::vector<std::string> availableMovies(const std::string& startTime,
                                              const std::string& endTime) {
        int start = parseTime(startTime);
        int end = parseTime(endTime);
        std::vector<std::string> result;
        for (const auto& movie : movies) {
            if (movie.startMinutes >= start && movie.endMinutes <= end) {
                result.push_back(movie.name);
            }
        }
        return result;
    }

    // Returns a mutable reference to the internal storage (like Java's getMovies)
    std::vector<Movie>& getMovies() {
        return movies;
    }

    const std::vector<Movie>& getMovies() const {
        return movies;
    }

private:
    struct Movie {
        std::string name;
        double price;
        int startMinutes; // minutes since midnight
        int endMinutes;
        std::vector<std::vector<int>> seats;
    };

    std::vector<Movie> movies;

    static int parseTime(const std::string& timeStr) {
        // Expect format "HH:MM"
        if (timeStr.length() != 5 || timeStr[2] != ':') {
            throw std::invalid_argument("Invalid time format: " + timeStr);
        }
        if (!std::isdigit(timeStr[0]) || !std::isdigit(timeStr[1]) ||
            !std::isdigit(timeStr[3]) || !std::isdigit(timeStr[4])) {
            throw std::invalid_argument("Invalid time format: " + timeStr);
        }
        int hours = std::stoi(timeStr.substr(0, 2));
        int minutes = std::stoi(timeStr.substr(3, 2));
        if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
            throw std::invalid_argument("Invalid time value: " + timeStr);
        }
        return hours * 60 + minutes;
    }
};