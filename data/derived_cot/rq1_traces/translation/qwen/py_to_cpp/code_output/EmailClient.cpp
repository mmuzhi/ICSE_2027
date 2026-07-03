#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>

struct Email {
    std::string sender;
    std::string receiver;
    std::string content;
    double size;
    std::string time;
    std::string state;
};

class EmailClient {
private:
    std::string addr;
    double capacity;
    std::vector<Email> inbox;

    std::string getCurrentTime() {
        std::time_t now = std::time(nullptr);
        std::tm utc_tm = *std::gmtime(&now);
        char buffer[100];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &utc_tm);
        return std::string(buffer);
    }

public:
    EmailClient(const std::string& addr, double capacity) : addr(addr), capacity(capacity) {}

    bool send_to(EmailClient& recv, const std::string& content, double size) {
        if (!recv.is_full_with_one_more_email(size)) {
            Email email;
            email.sender = this->addr;
            email.receiver = recv.addr;
            email.content = content;
            email.size = size;
            email.time = getCurrentTime();
            email.state = "unread";
            recv.inbox.push_back(email);
            return true;
        } else {
            this->clear_inbox(size);
            return false;
        }
    }

    Email* fetch() {
        if (this->inbox.empty()) {
            return nullptr;
        }
        for (auto it = this->inbox.begin(); it != this->inbox.end(); ++it) {
            if (it->state == "unread") {
                it->state = "read";
                return &(*it);
            }
        }
        return nullptr;
    }

    bool is_full_with_one_more_email(double size) {
        double occupied_size = this->get_occupied_size();
        return (occupied_size + size > this->capacity);
    }

    double get_occupied_size() {
        double total = 0;
        for (const auto& email : this->inbox) {
            total += email.size;
        }
        return total;
    }

    void clear_inbox(double size) {
        if (this->addr.empty()) {
            return;
        }
        double freed_space = 0;
        while (freed_space < size && !this->inbox.empty()) {
            Email email = this->inbox[0];
            freed_space += email.size;
            this->inbox.erase(this->inbox.begin());
        }
    }
};