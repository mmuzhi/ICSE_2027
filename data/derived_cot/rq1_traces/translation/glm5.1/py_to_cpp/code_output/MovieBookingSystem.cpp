#include <string>
#include <vector>
#include <ctime>
#include <sstream>

struct Movie {
    std::string name;
    double price;
    std::tm start_time;
    std::tm end_time;
    std::vector<std::vector<double>> seats;
};

class MovieBookingSystem {
private:
    std::vector<Movie> movies;

    static std::tm parseTime(const std::string& time_str) {
        std::tm tm = {};
        tm.tm_year = 0;   // 1900
        tm.tm_mon = 0;    // January
        tm.tm_mday = 1;   // 1st
        int hour, minute;
        char colon;
        std::istringstream iss(time_str);
        iss >> hour >> colon >> minute;
        tm.tm_hour = hour;
        tm.tm_min = minute;
        return tm;
    }

    static int toMinutes(const std::tm& t) {
        return t.tm_hour * 60 + t.tm_min;
    }

public:
    MovieBookingSystem() = default;

    void add_movie(const std::string& name, double price,
                   const std::string& start_time, const std::string& end_time, int n) {
        Movie movie;
        movie.name = name;
        movie.price = price;
        movie.start_time = parseTime(start_time);
        movie.end_time = parseTime(end_time);
        movie.seats.assign(n, std::vector<double>(n, 0.0));
        movies.push_back(movie);
    }

    std::string book_ticket(const std::string& name,
                            const std::vector<std::pair<int, int>>& seats_to_book) {
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

    std::vector<std::string> available_movies(const std::string& start_time,
                                               const std::string& end_time) {
        std::tm start = parseTime(start_time);
        std::tm end = parseTime(end_time);

        std::vector<std::string> available;
        for (const auto& movie : movies) {
            if (toMinutes(start) <= toMinutes(movie.start_time) &&
                toMinutes(movie.end_time) <= toMinutes(end)) {
                available.push_back(movie.name);
            }
        }
        return available;
    }
};