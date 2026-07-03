#include <string>
#include <vector>
#include <optional>
#include <chrono>
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

    EmailClient(const std::string& addr, double capacity)
        : addr(addr), capacity(capacity) {}

    bool send_to(EmailClient& recv, const std::string& content, double size) {
        if (!recv.is_full_with_one_more_email(size)) {
            auto now = std::chrono::system_clock::now();
            std::time_t t = std::chrono::system_clock::to_time_t(now);
            char buf[100];
            std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
            std::string timestamp(buf);

            Email email;
            email.sender = this->addr;
            email.receiver = recv.addr;
            email.content = content;
            email.size = size;
            email.time = timestamp;
            email.state = "unread";

            recv.inbox.push_back(std::move(email));
            return true;
        } else {
            this->clear_inbox(size);
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
        double occupied = get_occupied_size();
        return (occupied + size) > capacity;
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
            inbox.erase(inbox.begin());
        }
    }
};