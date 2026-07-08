#ifndef CHAT_H
#define CHAT_H

#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class Chat {
public:
    class Message {
    private:
        std::string sender;
        std::string receiver;
        std::string message;
        std::string timestamp;

        static int stringHashCode(const std::string& s) {
            int h = 0;
            for (char c : s) {
                h = 31 * h + static_cast<int>(c);
            }
            return h;
        }

    public:
        Message(const std::string& sender, const std::string& receiver,
                const std::string& message, const std::string& timestamp)
            : sender(sender), receiver(receiver), message(message), timestamp(timestamp) {}

        const std::string& getSender() const { return sender; }
        const std::string& getReceiver() const { return receiver; }
        const std::string& getMessage() const { return message; }
        const std::string& getTimestamp() const { return timestamp; }

        bool operator==(const Message& other) const {
            return sender == other.sender &&
                   receiver == other.receiver &&
                   message == other.message &&
                   timestamp == other.timestamp;
        }

        bool operator!=(const Message& other) const {
            return !(*this == other);
        }

        // Replicates Java's Objects.hash(sender, receiver, message, timestamp)
        int hashCode() const {
            int result = 1;
            result = 31 * result + stringHashCode(sender);
            result = 31 * result + stringHashCode(receiver);
            result = 31 * result + stringHashCode(message);
            result = 31 * result + stringHashCode(timestamp);
            return result;
        }

        std::string toString() const {
            std::ostringstream oss;
            oss << "Message{sender='" << sender << "', receiver='" << receiver
                << "', message='" << message << "', timestamp='" << timestamp << "'}";
            return oss.str();
        }
    };

private:
    std::unordered_map<std::string, std::vector<Message>> users;

public:
    Chat() : users() {}

    bool addUser(const std::string& username) {
        if (users.find(username) != users.end()) {
            return false;
        }
        users[username] = std::vector<Message>();
        return true;
    }

    bool removeUser(const std::string& username) {
        auto it = users.find(username);
        if (it != users.end()) {
            users.erase(it);
            return true;
        }
        return false;
    }

    bool sendMessage(const std::string& sender, const std::string& receiver,
                     const std::string& message) {
        if (users.find(sender) == users.end() || users.find(receiver) == users.end()) {
            return false;
        }

        // Format current time as "yyyy-MM-dd HH:mm:ss"
        std::time_t now = std::time(nullptr);
        std::tm* tm = std::localtime(&now);
        std::ostringstream oss;
        oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
        std::string timestamp = oss.str();

        Message messageInfo(sender, receiver, message, timestamp);

        users[sender].push_back(messageInfo);
        users[receiver].push_back(messageInfo);
        return true;
    }

    std::vector<Message> getMessages(const std::string& username) {
        auto it = users.find(username);
        if (it == users.end()) {
            return std::vector<Message>();
        }
        return it->second;
    }

    std::unordered_map<std::string, std::vector<Message>>& getUsers() {
        return users;
    }
};

#endif