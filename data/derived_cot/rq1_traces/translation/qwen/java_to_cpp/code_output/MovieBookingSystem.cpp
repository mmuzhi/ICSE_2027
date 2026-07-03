#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <unordered_map>
#include <any>
#include <algorithm>

// Helper function to parse time string to total minutes.
int parseTime(const std::string& timeStr) {
    size_t pos = timeStr.find(':');
    if (pos == std::string::npos) {
        throw std::invalid_argument("Invalid time format. Expected format: HH:mm");
    }

    std::string hourStr = timeStr.substr(0, pos);
    std::string minStr = timeStr.substr(pos + 1);

    try {
        int hours = std::stoi(hourStr);
        int minutes = std::stoi(minStr);

        if (hours < 0 || hours >= 24 || minutes < 0 || minutes >= 60) {
            throw std::invalid_argument("Invalid time values.");
        }

        return hours * 60 + minutes;
    } catch (const std::exception& e) {
        throw std::invalid_argument("Invalid time format. Could not convert to integer.");
    }
}

class MovieBookingSystem {
private:
    std::vector<std::unordered_map<std::string, std::any>> movies;

public:
    MovieBookingSystem() {}

    void addMovie(std::string name, double price, std::string startTime, std::string endTime, int n) {
        int startMinutes = parseTime(startTime);
        int endMinutes = parseTime(endTime);

        if (startMinutes > endMinutes) {
            throw std::invalid_argument("Invalid movie time range. Start time must be before or equal to end time.");
        }

        std::unordered_map<std::string, std::any> movie;
        movie["name"] = std::move(name);
        movie["price"] = price;
        movie["start_time"] = startMinutes;
        movie["end_time"] = endMinutes;
        movie["seats"] = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
        movies.push_back(movie);
    }

    std::string bookTicket(std::string name, std::vector<std::vector<int>> seatsToBook) {
        for (const auto& movie : movies) {
            if (movie.at("name").get<std::string>() == name) {
                auto seats = movie.at("seats").get<std::vector<std::vector<int>>>();
                for (const auto& row : seatsToBook) {
                    int rowIdx = row[0];
                    int colIdx = row[1];
                    if (rowIdx < 0 || rowIdx >= seats.size() || colIdx < 0 || colIdx >= seats[0].size()) {
                        throw std::out_of_range("Row or column index out of bounds.");
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

    std::vector<std::string> availableMovies(std::string startTime, std::string endTime) {
        int startMinutes = parseTime(startTime);
        int endMinutes = parseTime(endTime);

        std::vector<std::string> available;
        for (const auto& movie : movies) {
            auto start = movie.at("start_time").get<int>();
            auto end = movie.at("end_time").get<int>();
            if (start >= startMinutes && end <= endMinutes) {
                available.push_back(movie.at("name").get<std::string>());
            }
        }
        return available;
    }

    std::vector<std::unordered_map<std::string, std::any>> getMovies() {
        return movies;
    }
};