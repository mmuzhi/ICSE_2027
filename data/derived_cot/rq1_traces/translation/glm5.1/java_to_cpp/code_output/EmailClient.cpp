#include <string>
#include <vector>
#include <map>
#include <variant>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

class EmailClient {
public:
    using Email = std::map<std::string, std::variant<std::string, double>>;

private:
    std::string addr;
    double capacity;
    std::vector<Email> inbox;

    static std::string getCurrentTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);
        std::tm* tm_now = std::localtime(&time_t_now);
        std::ostringstream oss;
        oss << std::put_time(tm_now, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

public:
    EmailClient(const std::string& addr, double capacity)
        : addr(addr), capacity(capacity) {}

    bool sendTo(EmailClient& recv, const std::string& content, double size) {
        if (!recv.isFullWithOneMoreEmail(size)) {
            std::string timestamp = getCurrentTimestamp();
            Email email;
            email["sender"] = this->addr;
            email["receiver"] = recv.addr;
            email["content"] = content;
            email["size"] = size;
            email["time"] = timestamp;
            email["state"] = std::string("unread");
            recv.inbox.push_back(email);
            return true;
        }
        else {
            this->clearInbox(size);
            if (recv.isFullWithOneMoreEmail(size)) {
                return false;
            }
            return sendTo(recv, content, size); // Retry sending after clearing
        }
    }

    Email* fetch() {
        if (this->inbox.empty()) {
            return nullptr;
        }
        for (auto& email : this->inbox) {
            auto it = email.find("state");
            if (it != email.end()) {
                const std::string* state = std::get_if<std::string>(&it->second);
                if (state && *state == "unread") {
                    email["state"] = std::string("read");
                    return &email;
                }
            }
        }
        return nullptr;
    }

    bool isFullWithOneMoreEmail(double size) const {
        double occupiedSize = this->getOccupiedSize();
        return occupiedSize + size > this.capacity;
    }

    double getOccupiedSize() const {
        double occupiedSize = 0;
        for (const auto& email : this->inbox) {
            auto it = email.find("size");
            if (it != email.end()) {
                const double* sizePtr = std::get_if<double>(&it->second);
                if (sizePtr) {
                    occupiedSize += *sizePtr;
                }
            }
        }
        return occupiedSize;
    }

    void clearInbox(double size) {
        if (this->addr.empty()) {
            return;
        }
        double freedSpace = 0;
        while (freedSpace < size && !this->inbox.empty()) {
            Email email = this->inbox.front();
            this->inbox.erase(this->inbox.begin());
            auto it = email.find("size");
            if (it != email.end()) {
                const double* sizePtr = std::get_if<double>(&it->second);
                if (sizePtr) {
                    freedSpace += *sizePtr;
                }
            }
        }
    }

    std::vector<Email>& getInbox() {
        return this->inbox;
    }

    void setInbox(const std::vector<Email>& inbox) {
        this->inbox = inbox;
    }
};