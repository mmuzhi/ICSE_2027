#include <vector>
#include <string>
#include <ctime>
#include <chrono>
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

std::string get_current_time() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = {};
    localtime_s(&tm, &now_time_t);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
    return std::string(buffer);
}

class EmailClient {
private:
    std::string addr;
    double capacity;
    std::vector<Email> inbox;

public:
    EmailClient(const std::string& addr, double capacity) : addr(addr), capacity(capacity) {}

    bool send_to(const EmailClient& recv, const std::string& content, double size) {
        if (!recv.is_full_with_one_more_email(size)) {
            Email email;
            email.sender = this->addr;
            email.receiver = recv.addr;
            email.content = content;
            email.size = size;
            email.time = get_current_time();
            email.state = "unread";
            recv.inbox.push_back(email);
            return true;
        } else {
            this->clear_inbox(size);
            return false;
        }
    }

    Email* fetch() {
        if (inbox.empty()) {
            return nullptr;
        }
        for (auto& email : inbox) {
            if (email.state == "unread") {
                email.state = "read";
                return &email;
            }
        }
        return nullptr;
    }

    bool is_full_with_one_more_email(double size) const {
        double occupied_size = 0;
        for (const auto& email : inbox) {
            occupied_size += email.size;
        }
        return occupied_size + size > this->capacity;
    }

    double get_occupied_size() const {
        double occupied_size = 0;
        for (const auto& email : inbox) {
            occupied_size += email.size;
        }
        return occupied_size;
    }

    void clear_inbox(double size) {
        if (this->addr.empty()) {
            return;
        }
        double freed_space = 0;
        while (freed_space < size && !inbox.empty()) {
            Email& email = inbox[0];
            freed_space += email.size;
            inbox.erase(inbox.begin());
        }
    }
};