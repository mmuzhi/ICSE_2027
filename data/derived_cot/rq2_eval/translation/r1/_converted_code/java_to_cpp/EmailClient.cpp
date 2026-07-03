#include <deque>
#include <unordered_map>
#include <string>
#include <any>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iostream>
#include <iomanip>

#if defined(_WIN32)
#define NOMINMAX
#include <Windows.h>
#endif

std::string getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
#if defined(_WIN32)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
    return std::string(buffer);
}

class EmailClient {
private:
    std::string addr;
    double capacity;
    std::deque<std::unordered_map<std::string, std::any>> inbox;

public:
    EmailClient(const std::string& addr, double capacity) : addr(addr), capacity(capacity), inbox() {}

    bool send_to(EmailClient& recv, const std::string& content, double size) {
        if (!recv.is_full_with_one_more_email(size)) {
            std::string timestamp = getCurrentTimestamp();
            std::unordered_map<std::string, std::any> email;
            email["sender"] = this->addr;
            email["receiver"] = recv.addr;
            email["content"] = content;
            email["size"] = size;
            email["time"] = timestamp;
            email["state"] = std::string("unread");
            recv.inbox.push_back(email);
            return true;
        } else {
            this->clear_inbox(size);
            if (recv.is_full_with_one_more_email(size)) {
                return false;
            }
            return send_to(recv, content, size);
        }
    }

    std::unordered_map<std::string, std::any>* fetch() {
        if (inbox.empty()) {
            return nullptr;
        }
        for (auto& email : inbox) {
            auto stateIt = email.find("state");
            if (stateIt != email.end()) {
                try {
                    std::string state = std::any_cast<std::string>(stateIt->second);
                    if (state == "unread") {
                        email["state"] = std::string("read");
                        return &email;
                    }
                } catch (const std::bad_any_cast&) {
                    continue;
                }
            }
        }
        return nullptr;
    }

    bool is_full_with_one_more_email(double size) {
        double occupiedSize = get_occupied_size();
        return occupiedSize + size > capacity;
    }

    double get_occupied_size() {
        double occupiedSize = 0;
        for (const auto& email : inbox) {
            auto it = email.find("size");
            if (it != email.end()) {
                try {
                    double emailSize = std::any_cast<double>(it->second);
                    occupiedSize += emailSize;
                } catch (const std::bad_any_cast&) {
                }
            }
        }
        return occupiedSize;
    }

    void clear_inbox(double size) {
        if (addr.empty()) {
            return;
        }
        double freedSpace = 0;
        while (freedSpace < size && !inbox.empty()) {
            auto email = inbox.front();
            inbox.pop_front();
            auto it = email.find("size");
            if (it != email.end()) {
                try {
                    double emailSize = std::any_cast<double>(it->second);
                    freedSpace += emailSize;
                } catch (const std::bad_any_cast&) {
                }
            }
        }
    }

    std::deque<std::unordered_map<std::string, std::any>>& getInbox() {
        return inbox;
    }

    void setInbox(const std::deque<std::unordered_map<std::string, std::any>>& newInbox) {
        inbox = newInbox;
    }
};