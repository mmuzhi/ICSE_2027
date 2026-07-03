#include <string>
#include <vector>
#include <map>
#include <any>
#include <sstream>

class MovieBookingSystem {
private:
    struct LocalTime {
        int seconds; // since midnight
        bool isBefore(const LocalTime& other) const { return seconds < other.seconds; }
        bool isAfter(const LocalTime& other) const { return seconds > other.seconds; }
    };

    static LocalTime parseTime(const std::string& time) {
        int h = 0, m = 0, s = 0;
        char c;
        std::istringstream iss(time);
        iss >> h >> c >> m;
        if (iss >> c >> s) {}
        return {h * 3600 + m * 60 + s};
    }

    std::vector<std::map<std::string, std::any>> movies;

public:
    MovieBookingSystem() = default;

    void addMovie(const std::string& name, double price, const std::string& startTime, const std::string& endTime, int n) {
        std::map<std::string, std::any> movie;
        movie["name"] = name;
        movie["price"] = price;
        movie["start_time"] = parseTime(startTime);
        movie["end_time"] = parseTime(endTime);
        movie["seats"] = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
        movies.push_back(std::move(movie));
    }

    std::string bookTicket(const std::string& name, const std::vector<std::vector<int>>& seatsToBook) {
        for (auto& movie : movies) {
            if (std::any_cast<const std::string&>(movie.at("name")) == name) {
                auto& seats = std::any_cast<std::vector<std::vector<int>>&>(movie.at("seats"));
                for (const auto& seat : seatsToBook) {
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

    std::vector<std::string> availableMovies(const std::string& startTime, const std::string& endTime) {
        LocalTime start = parseTime(startTime);
        LocalTime end = parseTime(endTime);

        std::vector<std::string> result;
        for (const auto& movie : movies) {
            LocalTime movieStart = std::any_cast<LocalTime>(movie.at("start_time"));
            LocalTime movieEnd = std::any_cast<LocalTime>(movie.at("end_time"));
            if (!movieStart.isBefore(start) && !movieEnd.isAfter(end)) {
                result.push_back(std::any_cast<const std::string&>(movie.at("name")));
            }
        }
        return result;
    }

    std::vector<std::map<std::string, std::any>>& getMovies() {
        return movies;
    }
};