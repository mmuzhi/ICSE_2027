#include <vector>
#include <map>
#include <string>
#include <any>
#include <stdexcept>
#include <algorithm>

class Time {
private:
    int hour;
    int minute;
public:
    Time() : hour(0), minute(0) {}
    Time(int hour, int minute) : hour(hour), minute(minute) {}
    Time(const std::string& timeStr) {
        size_t pos = timeStr.find(':');
        if (pos == std::string::npos) {
            throw std::invalid_argument("Invalid time format");
        }
        hour = std::stoi(timeStr.substr(0, pos));
        minute = std::stoi(timeStr.substr(pos + 1));
        if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
            throw std::invalid_argument("Invalid time");
        }
    }

    bool operator<(const Time& other) const {
        if (hour < other.hour) return true;
        if (hour == other.hour && minute < other.minute) return true;
        return false;
    }

    bool operator<=(const Time& other) const {
        return *this < other || *this == other;
    }

    bool operator==(const Time& other) const {
        return hour == other.hour && minute == other.minute;
    }

    bool operator>(const Time& other) const {
        return other < *this;
    }

    bool operator>=(const Time& other) const {
        return !(*this < other);
    }
};

class MovieBookingSystem {
private:
    std::vector<std::map<std::string, std::any>> movies;

public:
    MovieBookingSystem() {}

    void add_movie(std::string name, double price, std::string startTime, std::string endTime, int n) {
        std::map<std::string, std::any> movie;
        movie["name"] = name;
        movie["price"] = price;
        movie["start_time"] = Time(startTime);
        movie["end_time"] = Time(endTime);
        movie["seats"] = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
        movies.push_back(movie);
    }

    std::string book_ticket(std::string name, std::vector<std::vector<int>> seatsToBook) {
        for (auto& movie : movies) {
            if (std::any_cast<std::string>(movie["name"]) == name) {
                auto& seats = std::any_cast<std::vector<std::vector<int>>&>(movie["seats"]);
                for (auto& seat : seatsToBook) {
                    if (seat.size() < 2) {
                        return "Booking failed.";
                    }
                    int row = seat[0];
                    int col = seat[1];
                    if (seats[row][col] == 0) {
                        seats[row][col] = 1;
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
        Time start(startTime);
        Time end(endTime);
        std::vector<std::string> result;
        for (auto& movie : movies) {
            Time movieStart = std::any_cast<Time>(movie["start_time"]);
            Time movieEnd = std::any_cast<Time>(movie["end_time"]);
            if (movieStart >= start && movieEnd <= end) {
                result.push_back(std::any_cast<std::string>(movie["name"]));
            }
        }
        return result;
    }

    std::vector<std::map<std::string, std::any>>& getMovies() {
        return movies;
    }
};