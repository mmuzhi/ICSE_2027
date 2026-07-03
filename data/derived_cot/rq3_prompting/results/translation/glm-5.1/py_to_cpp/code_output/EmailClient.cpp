#include <string>
#include <vector>
#include <optional>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

struct Email {
    std::string sender;
    std::string receiver;
    std::string content;
    double size;
    std::string time;
    std::string state;
};

class EmailClient {
public:
    std::string addr;
    double capacity;
    std::vector<Email> inbox;

    EmailClient(std::string addr, double capacity)
        : addr(std::move(addr)), capacity(capacity) {}

    bool send_to(EmailClient& recv, const std::string& content, double size) {
        if (!recv.is_full_with_one_more_email(size)) {
            auto now = std::chrono::system_clock::now();
            auto time_t_val = std::chrono::system_clock::to_time_t(now);
            std::ostringstream oss;
            oss << std::put_time(std::localtime(&time_t_val), "%Y-%m-%d %H:%M:%S");

            Email email;
            email.sender = this->addr;
            email.receiver = recv.addr;
            email.content = content;
            email.size = size;
            email.time = oss.str();
            email.state = "unread";

            recv.inbox.push_back(email);
            return true;
        } else {
            this->clear_inbox(size);
            return false;
        }
    }

    std::optional<Email> fetch() {
        if (inbox.empty()) {
            return std::nullopt;
        }
        for (size_t i = 0; i < inbox.size(); ++i) {
            if (inbox[i].state == "unread") {
                inbox[i].state = "read";
                return inbox[i];
            }
        }
        return std::nullopt;
    }

    bool is_full_with_one_more_email(double size) {
        double occupied_size = get_occupied_size();
        return occupied_size + size > capacity;
    }

    double get_occupied_size() {
        double occupied_size = 0;
        for (const auto& email : inbox) {
            occupied_size += email.size;
        }
        return occupied_size;
    }

    void clear_inbox(double size) {
        if (addr.empty()) {
            return;
        }
        double freed_space = 0;
        while (freed_space < size && !inbox.empty()) {
            freed_space += inbox[0].size;
            inbox.erase(inbox.begin());
        }
    }
};