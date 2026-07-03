#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <any>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <typeinfo>
#include <optional>

class EmailClient {
private:
    std::string addr;
    double capacity;
    std::vector<std::map<std::string, std::any>> inbox;

    static bool tryGetDouble(const std::any& a, double& result) {
        if (a.type() == typeid(double)) {
            result = std::any_cast<double>(a);
            return true;
        } else if (a.type() == typeid(int)) {
            result = static_cast<double>(std::any_cast<int>(a));
            return true;
        } else if (a.type() == typeid(long)) {
            result = static_cast<double>(std::any_cast<long>(a));
            return true;
        } else if (a.type() == typeid(float)) {
            result = std::any_cast<float>(a);
            return true;
        }
        return false;
    }

    double getOccupiedSize() const {
        double occupiedSize = 0;
        for (const auto& email : inbox) {
            const auto& sizeAny = email.at("size");
            double size;
            if (tryGetDouble(sizeAny, size)) {
                occupiedSize += size;
            }
        }
        return occupiedSize;
    }

public:
    explicit EmailClient(const std::string& addr, double capacity) : addr(addr), capacity(capacity) {}

    bool sendTo(EmailClient& recv, const std::string& content, double size) {
        if (!recv.isFullWithOneMoreEmail(size)) {
            auto timestamp = getCurrentTimestamp();
            std::map<std::string, std::any> email;
            email["sender"] = addr;
            email["receiver"] = recv.addr;
            email["content"] = content;
            email["size"] = size;
            email["time"] = timestamp;
            email["state"] = "unread";
            recv.inbox.push_back(email);
            return true;
        } else {
            this->clearInbox(size);
            if (recv.isFullWithOneMoreEmail(size)) {
                return false;
            }
            return this->sendTo(recv, content, size);
        }
    }

    std::optional<std::map<std::string, std::any>> fetch() {
        if (inbox.empty()) {
            return std::nullopt;
        }
        for (auto& email : inbox) {
            if (std::string("unread") == std::any_cast<std::string>(email.at("state"))) {
                email["state"] = "read";
                return email;
            }
        }
        return std::nullopt;
    }

    bool isFullWithOneMoreEmail(double size) const {
        double occupiedSize = this->getOccupiedSize();
        return occupiedSize + size > this->capacity;
    }

    void clearInbox(double size) {
        if (addr.empty()) {
            return;
        }
        double freedSpace = 0;
        while (freedSpace < size && !inbox.empty()) {
            auto email = inbox.front();
            inbox.erase(inbox.begin());
            const auto& sizeAny = email.at("size");
            double emailSize;
            if (tryGetDouble(sizeAny, emailSize)) {
                freedSpace += emailSize;
            }
        }
    }

    std::vector<std::map<std::string, std::any>> getInbox() const {
        return inbox;
    }

    void setInbox(const std::vector<std::map<std::string, std::any>>& inbox) {
        this->inbox = inbox;
    }

private:
    std::string getCurrentTimestamp() const {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
};

int main() {
    // Example usage
    EmailClient client1("user@example.com", 100.0);
    EmailClient client2("another@example.com", 100.0);

    client1.sendTo(client2, "Hello", 5.0);
    auto email = client2.fetch();
    if (email) {
        std::cout << "Fetched email: " << std::any_cast<std::string>((*email)["content"]) << std::endl;
    }

    return 0;
}