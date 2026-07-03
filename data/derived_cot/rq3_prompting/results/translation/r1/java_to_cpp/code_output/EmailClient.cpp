#include <string>
#include <vector>
#include <unordered_map>
#include <any>
#include <ctime>
#include <chrono>
#include <sstream>
#include <iomanip>

class EmailClient {
private:
    std::string addr;
    double capacity;
    std::vector<std::unordered_map<std::string, std::any>> inbox;

    std::string getCurrentTimestamp() {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm* tm = std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

public:
    EmailClient(const std::string& addr, double capacity)
        : addr(addr), capacity(capacity) {}

    bool sendTo(EmailClient& recv, const std::string& content, double size) {
        if (!recv.isFullWithOneMoreEmail(size)) {
            std::unordered_map<std::string, std::any> email;
            email["sender"] = this->addr;
            email["receiver"] = recv.addr;
            email["content"] = content;
            email["size"] = size;
            email["time"] = getCurrentTimestamp();
            email["state"] = std::string("unread");
            recv.inbox.push_back(std::move(email));
            return true;
        } else {
            this->clearInbox(size);
            if (recv.isFullWithOneMoreEmail(size)) {
                return false;
            }
            return sendTo(recv, content, size);
        }
    }

    std::unordered_map<std::string, std::any>* fetch() {
        if (this->inbox.empty()) {
            return nullptr;
        }
        for (auto& email : this->inbox) {
            auto it = email.find("state");
            if (it != email.end() && std::any_cast<std::string>(it->second) == "unread") {
                it->second = std::string("read");
                return &email;
            }
        }
        return nullptr;
    }

    bool isFullWithOneMoreEmail(double size) const {
        double occupiedSize = this->getOccupiedSize();
        return occupiedSize + size > this->capacity;
    }

    double getOccupiedSize() const {
        double occupiedSize = 0;
        for (const auto& email : this->inbox) {
            auto it = email.find("size");
            if (it != email.end()) {
                occupiedSize += std::any_cast<double>(it->second);
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
            auto email = std::move(this->inbox.front());
            this->inbox.erase(this->inbox.begin());
            auto it = email.find("size");
            if (it != email.end()) {
                freedSpace += std::any_cast<double>(it->second);
            }
        }
    }

    std::vector<std::unordered_map<std::string, std::any>>& getInbox() {
        return this->inbox;
    }

    void setInbox(std::vector<std::unordered_map<std::string, std::any>> inbox) {
        this->inbox = std::move(inbox);
    }
};