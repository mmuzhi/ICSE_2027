#include <vector>
#include <unordered_map>
#include <string>
#include <any>
#include <optional>
#include <mutex>
#include <iostream>
#include <memory>

class EmailClient {
private:
    std::string addr;
    double capacity;
    std::vector<std::unique_ptr<std::unordered_map<std::string, std::any>>> inbox;
    mutable std::mutex mtx;

public:
    explicit EmailClient(const std::string& addr, double capacity)
        : addr(addr), capacity(capacity) {}

    bool send_to(EmailClient& recv, const std::string& content, double size) {
        std::lock_guard<std::mutex> lock(recv.mtx);
        if (!recv.is_full_with_one_more_email(size)) {
            std::unordered_map<std::string, std::any> emailMap;
            emailMap["sender"] = addr;
            emailMap["receiver"] = recv.addr;
            emailMap["content"] = content;
            emailMap["size"] = size;
            emailMap["time"] = get_current_time();
            emailMap["state"] = "unread";
            recv.inbox.push_back(std::make_unique<std::unordered_map<std::string, std::any>>(std::move(emailMap)));
            return true;
        } else {
            this->clear_inbox(size);
            std::lock_guard<std::mutex> lock2(mtx);
            if (recv.is_full_with_one_more_email(size)) {
                return false;
            }
            return send_to(recv, content, size);
        }
    }

    std::optional<std::unordered_map<std::string, std::any>> fetch() {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto& email : inbox) {
            if ("unread" == std::any_cast<std::string>(*email->find("state")->second)) {
                (*email)["state"] = "read";
                return *email;
            }
        }
        return std::nullopt;
    }

    bool is_full_with_one_more_email(double size) const {
        std::lock_guard<std::mutex> lock(mtx);
        double occupiedSize = get_occupied_size();
        return occupiedSize + size > capacity;
    }

    double get_occupied_size() const {
        std::lock_guard<std::mutex> lock(mtx);
        double occupiedSize = 0.0;
        for (const auto& email : inbox) {
            if (email->contains("size")) {
                auto sizeObj = email->at("size");
                if (std::any::type::hash()()(sizeObj.type()) == std::any_cast<std::nullptr_t>(nullptr)->hash()) {
                    continue;
                }
                try {
                    occupiedSize += std::any_cast<double>(sizeObj);
                } catch (const std::bad_any_cast&) {
                    // Handle non-double values if necessary
                }
            }
        }
        return occupiedSize;
    }

    void clear_inbox(double size) {
        std::lock_guard<std::mutex> lock(mtx);
        if (addr.empty()) {
            return;
        }
        double freedSpace = 0.0;
        while (freedSpace < size && !inbox.empty()) {
            auto email = std::move(inbox[0]);
            inbox.erase(inbox.begin());
            if (email->contains("size")) {
                auto sizeObj = email->at("size");
                try {
                    freedSpace += std::any_cast<double>(sizeObj);
                } catch (const std::bad_any_cast&) {
                    // Handle non-double values if necessary
                }
            }
        }
    }

    std::vector<std::unique_ptr<std::unordered_map<std::string, std::any>>> getInbox() const {
        std::lock_guard<std::mutex> lock(mtx);
        return inbox;
    }

    void setInbox(const std::vector<std::unique_ptr<std::unordered_map<std::string, std::any>>>& inbox) {
        std::lock_guard<std::mutex> lock(mtx);
        this->inbox = inbox;
    }

private:
    std::string get_current_time() {
        // Simple timestamp generation; adjust to match Java's format if needed
        return std::string(LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss")));
    }
};