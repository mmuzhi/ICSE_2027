#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <iomanip>
#include <sstream>

class Chat {
public:
    class Message {
    public:
        std::string sender;
        std::string receiver;
        std::string message;
        std::string timestamp;

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

        std::string toString() const {
            return "Message{sender='" + sender + "', receiver='" + receiver +
                   "', message='" + message + "', timestamp='" + timestamp + "'}";
        }
    };

private:
    std::unordered_map<std::string, std::vector<Message>> users;

public:
    Chat() = default;

    bool addUser(const std::string& username) {
        if (users.find(username) != users.end()) {
            return false;
        } else {
            users[username] = std::vector<Message>();
            return true;
        }
    }

    bool removeUser(const std::string& username) {
        auto it = users.find(username);
        if (it != users.end()) {
            users.erase(it);
            return true;
        } else {
            return false;
        }
    }

    bool sendMessage(const std::string& sender, const std::string& receiver,
                     const std::string& message) {
        if (users.find(sender) == users.end() || users.find(receiver) == users.end()) {
            return false;
        }

        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);
        std::ostringstream oss;
        oss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
        std::string timestamp = oss.str();

        Message messageInfo(sender, receiver, message, timestamp);

        users.at(sender).push_back(messageInfo);
        users.at(receiver).push_back(messageInfo);
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