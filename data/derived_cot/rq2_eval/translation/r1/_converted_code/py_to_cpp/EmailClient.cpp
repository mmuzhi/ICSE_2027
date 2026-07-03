#include <iostream>
#include <deque>
#include <string>
#include <optional>
#include <chrono>
#include <iomanip>
#include <sstream>

struct Email {
    std::string sender;
    std::string receiver;
    std::string content;
    double size;
    std::string time;
    std::string state; // "unread" or "read"
};

class EmailClient {
private:
    std::string addr;
    double capacity;
    std::deque<Email> inbox;

public:
    EmailClient(const std::string& addr, double capacity) 
        : addr(addr), capacity(capacity), inbox() {}

    bool send_to(EmailClient& recv, const std::string& content, double size) {
        if (!recv.is_full_with_one_more_email(size)) {
            auto now = std::chrono::system_clock::now();
            auto in_time_t = std::chrono::system_clock::to_time_t(now);
            std::stringstream ss;
            ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
            std::string timestamp = ss.str();

            Email email{
                this->addr,
                recv.addr,
                content,
                size,
                timestamp,
                "unread"
            };
            recv.inbox.push_back(email);
            return true;
        } else {
            clear_inbox(size);
            return false;
        }
    }

    std::optional<Email> fetch() {
        for (auto& email : inbox) {
            if (email.state == "unread") {
                email.state = "read";
                return email;
            }
        }
        return std::nullopt;
    }

    bool is_full_with_one_more_email(double size) const {
        double occupied_size = get_occupied_size();
        return (occupied_size + size) > capacity;
    }

    double get_occupied_size() const {
        double total = 0.0;
        for (const auto& email : inbox) {
            total += email.size;
        }
        return total;
    }

    void clear_inbox(double size) {
        if (addr.empty()) {
            return;
        }
        double freed_space = 0.0;
        while (freed_space < size && !inbox.empty()) {
            freed_space += inbox.front().size;
            inbox.pop_front();
        }
    }
};