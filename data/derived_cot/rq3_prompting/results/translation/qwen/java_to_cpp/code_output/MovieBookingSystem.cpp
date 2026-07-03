#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

struct LocalTime {
    int hour;
    int minute;
    int second;
};

// Helper function to parse time string into LocalTime
LocalTime parseTime(const std::string& timeStr) {
    LocalTime t;
    std::vector<int> parts;
    std::stringstream ss(timeStr);
    std::string part;
    while (std::getline(ss, part, ':')) {
        parts.push_back(std::stoi(part));
    }
    if (parts.size() == 1) {
        t.hour = parts[0];
        t.minute = 0;
        t.second = 0;
    } else if (parts.size() == 2) {
        t.hour = parts[0];
        t.minute = parts[1];
        t.second = 0;
    } else if (parts.size() == 3) {
        t.hour = parts[0];
        t.minute = parts[1];
        t.second = parts[2];
    }
    return t;
}

// Helper function to compare two LocalTime objects
bool isBefore(const LocalTime& t1, const LocalTime& t2) {
    if (t1.hour != t2.hour) return t1.hour < t2.hour;
    if (t1.minute != t2.minute) return t1.minute < t2.minute;
    return t1.second < t2.second;
}

bool isAfter(const LocalTime& t1, const LocalTime& t2) {
    return isBefore(t2, t1);
}

class MovieBookingSystem {
private:
    struct Movie {
        std::string name;
        double price;
        LocalTime start_time;
        LocalTime end_time;
        std::vector<std::vector<int>> seats;
    };

    std::vector<Movie> movies;

public:
    MovieBookingSystem() = default;

    void addMovie(const std::string& name, double price, const std::string& startTime, const std::string& endTime, int n) {
        Movie movie;
        movie.name = name;
        movie.price = price;
        movie.start_time = parseTime(startTime);
        movie.end_time = parseTime(endTime);
        movie.seats = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
        movies.push_back(movie);
    }

    std::string bookTicket(const std::string& name, const std::vector<std::vector<int>>& seatsToBook) {
        for (auto& movie : movies) {
            if (movie.name == name) {
                auto& seats = movie.seats;
                for (const auto& row : seatsToBook) {
                    int rowIdx = row[0];
                    int colIdx = row[1];
                    if (rowIdx < 0 || rowIdx >= seats.size() || colIdx < 0 || colIdx >= seats[rowIdx].size()) {
                        return "Booking failed.";
                    }
                    if (seats[rowIdx][colIdx] == 0) {
                        seats[rowIdx][colIdx] = 1;
                    } else {
                        return "Booking failed.";
                    }
                }
                return "Booking success.";
            }
        }
        return "Movie not found.";
    }

    std::vector<std::string> availableMovies(const std::string& startTime, const std::string& endTime) {
        LocalTime start = parseTime(startTime);
        LocalTime end = parseTime(endTime);

        std::vector<std::string> available;
        for (const auto& movie : movies) {
            if (!isBefore(movie.start_time, start) && !isAfter(movie.end_time, end)) {
                available.push_back(movie.name);
            }
        }
        return available;
    }

    std::vector<Movie> getMovies() const {
        return movies;
    }
};