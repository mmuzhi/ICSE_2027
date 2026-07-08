#ifndef MOVIE_TICKET_DB_H
#define MOVIE_TICKET_DB_H

#include <sqlite3.h>
#include <string>
#include <vector>

namespace org {
namespace example {

class MovieTicketDB {
public:
    class Ticket {
    private:
        int id_;
        std::string movieName_;
        std::string theaterName_;
        std::string seatNumber_;
        std::string customerName_;

    public:
        Ticket(int id, const std::string& movieName, const std::string& theaterName,
               const std::string& seatNumber, const std::string& customerName)
            : id_(id), movieName_(movieName), theaterName_(theaterName),
              seatNumber_(seatNumber), customerName_(customerName) {}

        int getId() const { return id_; }
        const std::string& getMovieName() const { return movieName_; }
        const std::string& getTheaterName() const { return theaterName_; }
        const std::string& getSeatNumber() const { return seatNumber_; }
        const std::string& getCustomerName() const { return customerName_; }
    };

    MovieTicketDB(const std::string& dbName);
    ~MovieTicketDB();

    MovieTicketDB(const MovieTicketDB&) = delete;
    MovieTicketDB& operator=(const MovieTicketDB&) = delete;

    void insertTicket(const std::string& movieName, const std::string& theaterName,
                      const std::string& seatNumber, const std::string& customerName);
    std::vector<Ticket> searchTicketsByCustomer(const std::string& customerName);
    void deleteTicket(int ticketId);
    void close();

private:
    void createTable();
    sqlite3* connection_;
};

} // namespace example
} // namespace org

#endif // MOVIE_TICKET_DB_H