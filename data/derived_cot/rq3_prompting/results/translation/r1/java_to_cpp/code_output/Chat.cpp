#include <unordered_map>
#include <vector>
#include <memory>
#include <ctime>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <stdexcept>

class Chat {
public:
    class Message {
    public:
        Message(const std::string& sender, const std::string& receiver,
                const std::string& message, const std::string& timestamp)
            : sender_(sender), receiver_(receiver), message_(message), timestamp_(timestamp) {}

        const std::string& getSender() const { return sender_; }
        const std::string& getReceiver() const { return receiver_; }
        const std::string& getMessage() const { return message_; }
        const std::string& getTimestamp() const { return timestamp_; }

        bool operator==(const Message& other) const {
            return sender_ == other.sender_ &&
                   receiver_ == other.receiver_ &&
                   message_ == other.message_ &&
                   timestamp_ == other.timestamp_;
        }

        bool operator!=(const Message& other) const {
            return !(*this == other);
        }

        std::string toString() const {
            std::ostringstream oss;
            oss << "Message{sender='" << sender_ << "', receiver='" << receiver_
                << "', message='" << message_ << "', timestamp='" << timestamp_ << "'}";
            return oss.str();
        }

    private:
        std::string sender_;
        std::string receiver_;
        std::string message_;
        std::string timestamp_;
    };

    Chat() = default;

    bool addUser(const std::string& username) {
        if (users_.find(username) != users_.end()) {
            return false;
        }
        users_[username] = std::make_shared<std::vector<Message>>();
        return true;
    }

    bool removeUser(const std::string& username) {
        auto it = users_.find(username);
        if (it == users_.end()) {
            return false;
        }
        users_.erase(it);
        return true;
    }

    bool sendMessage(const std::string& sender, const std::string& receiver,
                     const std::string& message) {
        auto it_s = users_.find(sender);
        auto it_r = users_.find(receiver);
        if (it_s == users_.end() || it_r == users_.end()) {
            return false;
        }

        // Get current timestamp
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm* tm_ptr = std::localtime(&t);
        if (!tm_ptr) {
            throw std::runtime_error("Failed to get local time");
        }
        std::ostringstream oss;
        oss << std::put_time(tm_ptr, "%Y-%m-%d %H:%M:%S");
        std::string timestamp = oss.str();

        Message msg(sender, receiver, message, timestamp);
        it_s->second->push_back(msg);
        it_r->second->push_back(msg);
        return true;
    }

    std::shared_ptr<std::vector<Message>> getMessages(const std::string& username) {
        auto it = users_.find(username);
        if (it == users_.end()) {
            return std::make_shared<std::vector<Message>>();
        }
        return it->second;
    }

    // Return mutable reference to internal map (matches Java behavior)
    std::unordered_map<std::string, std::shared_ptr<std::vector<Message>>>& getUsers() {
        return users_;
    }

    // Const overload for convenience (not in Java, but safe to add)
    const std::unordered_map<std::string, std::shared_ptr<std::vector<Message>>>& getUsers() const {
        return users_;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<std::vector<Message>>> users_;
};